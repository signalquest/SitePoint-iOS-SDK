import Foundation
import struct os.Logger
import SQSitePoint

public typealias authorizedHandler = (Result<Void, AuthorizationFailure>) -> Void
public typealias rtcmHandler = (_ message: Data) -> Void

/// Parses NTRIP authorization and RTCM messages.
public struct NtripParser {
    
    /// Creates an NTRIP parser with the passed-in callbacks; the callbacks are necessary because it may take multiple streamed-in chunks to get results, or multiple RTCM messages from one chunk
    /// - Parameters:
    ///   - authorizedCallback: for authorization handling
    ///   - rtcmCallback: for RTCM data handling; data to be passed as-is to a SitePoint
    public init(_ authorizedCallback:@escaping authorizedHandler, _ rtcmCallback:@escaping rtcmHandler) {
        let ntripErrorCode = NTRIP_Parse_Init(parseContext, &parseBuffer, parseBuffer.count, nil);
        assert(NTRIP_SUCCESS == ntripErrorCode, "Ntrip parsing init error: \(ntripErrorCode)")
        self.authorizedCallback = authorizedCallback
        self.rtcmCallback = rtcmCallback
    }
    
    /// Parses aiding authorization request for the input stream.
    /// - Parameter stream: The InputStream from the connected NTRIP server.
    ///
    /// Call with the result of an aiding request that includes a basic authorization header.
    public func parseAuthorized(_ stream: InputStream) {
        var bytes = readBytes(stream)
        NtripParser.logger.trace("parseAuthorized w/ \(bytes.map { String(format: "%02hhX", $0)}.joined(separator: " "))")
        let parsed = NTRIP_Parse(parseContext, &bytes, bytes.count)
        if parsed.rawValue < NTRIP_SUCCESS.rawValue { // 0 is NTRIP_SUCCESS, negative values are errors
            NtripParser.logger.error("Error parsing authorization input stream: '\(String(describing: parsed))'")
            authorizedCallback(.failure(AuthorizationFailure(0, "Parsing failed", "Error parsing authorization input stream: '\(bytes)'")))
        }
        
        let header = parseContext.pointee.Header
        let status = Int(header.Error_Status.rawValue)
        let reason:String = String(cString: header.Short_Text)
        let description:String = String(cString: header.Description)
        let poll = parseContext.pointee.Poll
        NtripParser.logger.debug("parseAuthorized \(status): \(reason); status/type: \(poll.Status.rawValue)/\(poll.type.rawValue). From \(String(cString: header.First_HTTP_Reply))")
        let needMoreData = NTRIP_NO_MESSAGE_PENDING.rawValue == parsed.rawValue
        if (!needMoreData) {
            if (header.Authorized) {
                authorizedCallback(.success(()))
            } else {
                authorizedCallback(.failure(AuthorizationFailure(status, reason, description)))
            }
        }
    }
        
    /// Parses the RTCM messages from the InputStream.
    /// - Parameter stream: The InputStream from the connected NTRIP server.
    ///
    /// Call after authorization is established using ``parseAuthorized(_:)`` to start parsing RTCM messages.
    ///
    /// Results (0 or more messages per response) get sent to the ``rtcmHandler``.
    public func parseRtcm(_ stream: InputStream) {
        var bytes = readBytes(stream)
        //NtripParser.logger.trace("parseRtcm w/ \(bytes.map { String(format: "%02hhX", $0)}.joined(separator: " "))")
        var _ = NTRIP_Parse(parseContext, &bytes, bytes.count)
        handleRtcmResults()
    }
    
    private static let logger = Logger(
        subsystem: Bundle.main.bundleIdentifier!,
        category: String(describing: NtripParser.self)
    )
    
    /// Callback for receiving an RTCM message that can be written directly to a SitePoint for aiding.
    private var rtcmCallback:((_ message: Data) -> Void)
    private var authorizedCallback:((Result<Void, AuthorizationFailure>) -> Void)
    private var parseContext = UnsafeMutablePointer<NTRIP_Parse_Context_t>.allocate(capacity: 1)
    private var parseBuffer:[UInt8] = Array(repeating: 0, count: 8192)
    
    private var allowedMessageTypes = [ // SitePoint recognizes these
        1001, // L1 - only GPS RTK observables
        1002, // Extended L1 - only GPS RTK observables
        1003, // L1 / L2 GPS RTK observables
        1004, // Extended L1 / L2 GPS RTK observables
        1005, // Stationary RTK reference station ARP
        1006, // Stationary RTK reference station ARP with antenna height
        1007, // Antenna descriptor
        1009, // L1 - only GLONASS RTK observables
        1010, // Extended L1 - only GLONASS RTK observables
        1011, // L1 / L2 GLONASS RTK observables
        1012, // Extended L1 / L2 GLONASS RTK observables
        1033, // Receiver and Antenna Description
        1074, // GPS MSM4
        1075, // GPS MSM5
        1077, // GPS MSM7
        1084, // GLONASS MSM4
        1085, // GLONASS MSM5
        1087, // GLONASS MSM7
        1094, // Galileo MSM4
        1095, // Galileo MSM5
        1097, // Galileo MSM7
        1124, // BeiDou MSM4
        1125, // BeiDou MSM5
        1127, // BeiDou MSM7
        1230, // GLONASS code - phase biases
        4072, // u-Blox Proprietary , 4072.0 Reference st
    ];
    
    private func getRtcmId(_ buffer:UnsafeMutablePointer<UInt8>?, _ len:Int) -> UInt16? {
        // 3B header, 2B of RTCM id, 3B for CRC24Q
        if let b = buffer, (3 + 2 + 3) <= len && len < (3 + 1024 + 3)  {
            let a = UnsafeMutableBufferPointer(start: b, count: len)
            let id = (UInt16(a[3]) << 4) + (UInt16(a[4]) >> 4)
            NtripParser.logger.debug("getRtcmId (\(id))")
            return id
        } else {
            NtripParser.logger.warning("getRtcmId failed, bad buffer length \(len) or buffer nil \(buffer == nil)")
            return nil;
        }
    }

    private func handleRtcmResults() {
        let poll = parseContext.pointee.Poll
        let header = parseContext.pointee.Header
        let status = poll.Status
        let type = poll.type
        let httpStatus = header.Error_Status
        if 200 != httpStatus.rawValue {
            NtripParser.logger.warning("Unable to parse RTCM message \(String(cString: header.Short_Text)), \(String(cString: header.Description))")
            return
        }
        
        if NTRIP_MESSAGE_PENDING == status && NTRIP_RTCM_Message == type {
            let buffer = poll.Buffer
            let len = poll.Length
            let messageType = getRtcmId(buffer, len)
            if let msgType = messageType, allowedMessageTypes.contains(Int(msgType)) {
                let a = UnsafeMutableBufferPointer(start: buffer, count: len)
                rtcmCallback(Data(a))
                NtripParser.logger.debug("parsed RTCM message with id \(msgType)")
                NTRIP_Parse_Next_Message(parseContext)
                handleRtcmResults()
            }
        } else if (NTRIP_NO_MESSAGE_PENDING == status) {
            NtripParser.logger.debug("parseRtcm done, no message pending")
        } else {
            NtripParser.logger.warning("parseRtcm done with status \(String(describing: status)) and type \(String(describing: type))")
        }
    }
    
    private func readBytes(_ inputStream: InputStream, bufferSize: Int = 1024) -> [UInt8] {
        assert(inputStream.streamStatus == Stream.Status.open, "Expecting to read from an open stream")
        
        var array = [UInt8]()
        var buffer = [UInt8](repeating: 0, count: bufferSize)
        var bytesRead: Int
        
        while inputStream.hasBytesAvailable {
            bytesRead = inputStream.read(&buffer, maxLength: bufferSize)
            if bytesRead < 0 {
                NtripParser.logger.error("Error reading input stream \(inputStream.streamError.debugDescription)")
            }
            
            array.append(contentsOf: buffer.prefix(bytesRead))
        }
        return array;
    }
}

/// NTRIP authorization result.
public struct AuthorizationFailure:Error {
    /// HTTP status code of the authorization request. Returns 0 for a failure parsing results.
    public var status:Int
    /// Short description of return ``status``.
    public var reason:String
    /// Long description of return ``status``.
    public var description:String
    
    init(_ status:Int, _ reason:String, _ description:String) {
        self.status = status
        self.reason = reason
        self.description = description
    }
}

