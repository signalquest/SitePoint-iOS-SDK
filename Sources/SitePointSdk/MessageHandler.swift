import Foundation
import CoreBluetooth
import MapKit
import struct os.Logger
import SQSitePoint

public protocol MessageReceiverDelegate {
    func receive(status:Status)
    func receive(location:Location)
}

/// Handles message parsing for data sent and received over characteristics.
///
/// > Note: MessageHandler currently supports the handling of ``Status`` and ``Location`` data received over the ``messageCharacteristic``.
/// >
/// > Future releases will include reading and writing Configuration messages.
public class MessageHandler: NSObject {
    
    static let logger = Logger(
        subsystem: Bundle.main.bundleIdentifier!,
        category: String(describing: MessageHandler.self)
    )
    
    /// Reserved for future use. Will be used to write to characteristics.
    public var messageCharacteristic: CBCharacteristic?
    
    public var delegate:MessageReceiverDelegate?
    
    /// Parses ``Status`` and ``Location``  messages from the  results of `CBPeripheralDelegate.didUpdateValue` for the ``messageCharacteristic``.
    ///
    /// ### Example
    /// ```swift
    /// public func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic, error: Error?) {
    ///     if SitePointPeripheral.messageCharacteristicUuid == characteristic.uuid {
    ///         messageHandler.parse(data: characteristic.value)
    ///     }
    /// }
    /// ```
    public func parse(data:Data) throws {
        var arr = [UInt8](data)
        if arr.isEmpty {
            throw SdkError.unexpected("Bad array length \(arr.count)")
        }
        
        var reader = sqtpFrameReaderInitStruct(&arr, arr.count)
        
        while (reader.status == SqtpStatus_t.SQTP_STATUS_SUCCESS) {
            switch reader.subframe.id {
            case SqtpSubframeId_t.SQTP_ID_SITEPOINT_STATUS:
                let sitePointStatus = sqspStatusCopy(reader.subframe.payload)
                    delegate?.receive(status: Status(sitePointStatus))
            case SqtpSubframeId_t.SQTP_ID_SITEPOINT_LLA:
                let sitePointLla = sqspLlaCopy(reader.subframe.payload)
                    delegate?.receive(location: Location(sitePointLla))
            case SqtpSubframeId_t.SQTP_ID_SITEPOINT_LOCAL_BASE_CONFIG:
                    fallthrough
            case SqtpSubframeId_t.SQTP_ID_SITEPOINT_RELPOS:
                    break
                default:
                MessageHandler.logger.debug("Unsupported message type: '\(String(describing: reader.subframe.id))'")
            }
            reader = sqtpFrameReaderNextStruct(reader)
        }
        if (reader.status != SqtpStatus_t.SQTP_STATUS_FRAME_END) {
            let status_text = String( describing: reader.status )
            let detail = "\(status_text), frame index \(reader.index), subframe id \(reader.subframe.id), payload length \(reader.subframe.length)"
            throw SdkError.unexpected("Frame parsing error: \(detail)")
        }
    }
}

public enum SdkError: Error {
    case unexpected(String)
    case withFailureStatus(Int, String)
}

fileprivate func isCharging(_ systemPowerState:UInt8) -> Bool {
  let chargingBit = 6;
  return (systemPowerState & (1 << chargingBit)) != 0;
}

public struct ScanStatus {
    /// Whether SitePoint is currently connected to a device.
    public let connected:Bool
    /// Battery % remaining, 0-100.
    public let battery:UInt8
    /// Actively charging?
    public let charging:Bool
    /// Number of satellites used to calculate location solution.
    public let satellites:UInt8
    
    public init(_ advertisementData: NSData) {
        let rsp = sqspRspCCopy(advertisementData.bytes)
        connected = (rsp.mode.connected != 0)
        battery = rsp.batteryLevel
        satellites = rsp.satelliteCount
        charging = isCharging(rsp.systemPowerState)
    }
}

public struct Status {
    /// GPS time of week, in milliseconds.
    public let iTow:UInt32
    /// Unix time, in seconds.
    public let time:UInt32
    /// 0: Offline, 1: Acquiring, 2: 2d, 3: 3d, 4: RTK Float, 5: RTK Fixed, 6: Base Autosurvey, 7: Fixed Base.
    public let mode:UInt8
    /// Number of satellites used to calculate location solution.
    public let satellites:UInt8
    /// Battery % remaining, 0-100.
    public let battery:UInt8
    /// Actively charging?
    public let charging:Bool
    /// Whether each of the 8 latest RTCM messages were used.
    public let aidingQuality:[Bool]
    
    
    init(_ s:SqspStatus_t) {
        iTow = s.iTOW
        time = s.time
        mode = s.solType
        satellites = s.numSV
        battery = s.rsp.batteryLevel
        charging = isCharging(s.rsp.systemPowerState)
        aidingQuality = Status.getAidingQualityBins(s.rsp.aidingBins)
    }
    
    public init() {
        self.init(SqspStatus_t())
    }
    
    private static func getAidingQualityBins(_ aidingQuality:UInt8) -> [Bool] {
        var out = [Bool]()
        var values:UInt8 = aidingQuality
        for _ in 0..<8 {
            out.insert(values & 0x01 == 1, at: 0)
            values >>= 1
        }
        return out.reversed()
    }
    
    /// Label for Status.mode.
    public var modeLabel: String {
        get {
            let modePointer:UnsafePointer<UInt8>? = sqspSolutionTypeLabel(mode);
            if let p = modePointer {
                return String(cString: p)
            } else {
                return "Unknown"
            }
        }
    }
}

public struct Location {
    /// GPS time of week, in milliseconds.
    public let iTow:UInt32
    /// In decimal degrees (WGS 84).
    public let latitude:Double
    /// In decimal degrees (WGS 84).
    public let longitude:Double
    /// Meters above ellipsoid.
    public let height:Double
    /// In meters.
    public let horizontalAccuracy:Double
    /// In meters.
    public let verticalAccuracy:Double
    
    init(_ lla:SqspLla_t) {
        iTow = lla.iTOW
        latitude = lla.lat
        longitude = lla.lon
        height = lla.height
        horizontalAccuracy = lla.hAcc
        verticalAccuracy = lla.vAcc
    }
    
    public init() {
        self.init(SqspLla_t())
    }
}
