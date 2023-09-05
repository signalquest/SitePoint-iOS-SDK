# SitePoint Example App

Dive right into the Example App to learn how to use the SitePoint SDK.

## Source

Source code for a [SitePoint iOS Example App](https://github.com/signalquest/SitePoint-iOS-Example) is available which shows a minimal implementation using this SDK to interface with SitePoint devices.

This minimal implementation is focused on highlighting the important, required code, eschewing error handling and other best practices in favor of code clarity.

> Note: Additional documentation and inline comments are included in the example app. These are not generated in the documentation, but are recommended to review before developing an app as they contain helpful information.

### Example of commented code:

```swift
case Stream.Event.errorOccurred:
    if let anError = aStream.streamError {
        displayError("NTRIP input stream error occurred: \(anError.localizedDescription)")
        // Try to reconnect if we were disconnected while active
        if let disconnectedService = ntripService {
            disconnect()
            connect(service: disconnectedService)
        }
    }
```

## Start Developing

The <doc:B1_Implementation-Guide> has step-by-step instructions for interfacing with the SitePoint SDK.
