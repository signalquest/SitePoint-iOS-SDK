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
        if arr.isEmpty || sizeof_COP_In < arr.count {
            throw SdkError.unexpected("Bad array length \(arr.count)")
        }
        
        var messages = SQ_CopProtocol_Parse_Frame(&arr, arr.count)
        let messageCount = Int(messages.Number_of_SubFrames)
        let maxMessages = SQ_COP_PROTOCOL_CONFIG_MAX_SUB_FRAMES
        if messageCount == 0 || maxMessages < messageCount {
            throw SdkError.unexpected("\(messageCount) subframes not in (0, \(maxMessages)]")
        }

        for i in 0..<messageCount {
            let message = reportAtIndex(&messages, Int64(i))
            if message.Payload == nil {
                let detail = "Frame \(messages), Number_of_SubFrames \(messages.Number_of_SubFrames), SubFrame_Type \(message.SubFrame_Type), Status \(message.Status), Length \(message.Length)"
                throw SdkError.unexpected("Missing payload in \(detail)")
            }
            
            if message.Status < SQ_CopProtocol_SUCCESS { // success is 0, negatives are errors
                let detail = "Frame \(messages), Number_of_SubFrames \(messages.Number_of_SubFrames), SubFrame_Type \(message.SubFrame_Type), Length \(message.Length), Payload \(String(describing: message.Payload))"
                throw SdkError.withFailureStatus(Int(message.Status), detail)
            }

            switch Int32(message.SubFrame_Type) {
                case COP_SF_STATUS_PORTABLE:
                    let sitePointStatus = Pointer_to_status(message.Payload).pointee
                    delegate?.receive(status: Status(sitePointStatus))
                case COP_SF_LLA_PORTABLE:
                    let sitePointLla = Pointer_to_lla(message.Payload).pointee
                    delegate?.receive(location: Location(sitePointLla))
                case COP_SF_MODE_PORTABLE:
                    fallthrough
                case COP_SF_RELPOS_PORTABLE:
                    break
                default:
                    MessageHandler.logger.debug("Unsupported message type: '\(String(describing: message.SubFrame_Type))'")
            }
        }
    }
}

public enum SdkError: Error {
    case unexpected(String)
    case withFailureStatus(Int, String)
}

public struct ScanStatus {
    /// Whether SitePoint is currently connected to a device.
    public let connected:Bool
    
    public init(_ advertisementData: NSData) {
        let rsp = Rsp_from_bytes(advertisementData.bytes)
        connected = (rsp.mode.flags & 4) == 1
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
    /// Whether each of the 8 latest RTCM messages were used.
    public let aidingQuality:[Bool]
    
    init(_ s:sqgps_status_Portable_t) {
        iTow = s.iTOW
        time = s.Time
        mode = s.mode
        satellites = s.numSV
        battery = s.RSP.battery_level
        aidingQuality = Status.getAidingQualityBins(s.RSP.SQ_Status)
    }
    
    public init() {
        self.init(sqgps_status_Portable_t())
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
            let modePointer:UnsafeMutablePointer<UInt8>? = MODE_lookup(mode);
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
    
    init(_ lla:sqgps_lla_Portable_t) {
        iTow = lla.iTOW
        latitude = lla.lat
        longitude = lla.lon
        height = lla.height
        horizontalAccuracy = lla.hAcc
        verticalAccuracy = lla.vAcc
    }
    
    public init() {
        self.init(sqgps_lla_Portable_t())
    }
}
