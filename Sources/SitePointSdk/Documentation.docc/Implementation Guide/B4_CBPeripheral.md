# CBPeripheral

Set up CBPeripheral to interface with a connected SitePoint Bluetooth device.

## Overview

The CBPeripheral handles reading and writing SignalQuest and RTCM messages with the connected SitePoint.

### Reference the example app

In the SitePoint iOS Example App, the `CBPeripheral` code is in `SitePoint.swift`.

This included SitePointPeripheral class conforms to `CBPeripheralDelegate` to attach to, read, and write Bluetooth characteristics.

> Tip: SitePointPeripheral uses message handling functions to interface with the SDK, covered later.

### Handle connection initiated by CBCentralManager

In <doc:B3_CBCentralManager>, the connection to a specific SitePoint peripheral was initiated.

The CBCenteralManagerDelegate, on receiving a SitePoint connection, calls SitePointPeripheral's' `didConnect` method, allowing it to set itself as the CBPeripheralDelegate for that SitePoint.

```swift
func didConnect(_ peripheral: CBPeripheral) {
    self.peripheral = peripheral
    name = peripheral.name
    peripheral.delegate = self
}
```

> Note: The SitePoint iOS Example app uses a delegate that conforms to CBPeripheralDelegate to handle callbacks.

As noted previosly, the <doc:B3_CBCentralManager> initiated a `discoverServices` call.

Because `self` is set as the CBPeripheral's delegate, the callback for `didDiscoverServices` will be called and returns the services discovered. 

To discover the characteristics within each service, iterate the services to find the one with `sitePointServiceUuid` (00000100-34ed-12ef-63f4-317792041d17), and pass it into a `peripheral.discoverCharacteristics` call.

These characteristics will then be available in the CBPeripheralDelegate's `didDiscoverCharacteristicsFor` method, and can be bound for future use.

### Receiving SitePoint location and status data

To receive the SitePoint's location and status data, parse the incoming messages from the message characteristic. This is handled in the `didUpdateValueFor` callback, which is called when the characteristic has received data.

The messages are sent to the `MessageHandler` in the SDK, and return structured ``Location`` and ``Status`` data.

<!--TODO: Add more info here-->

### Sending RTCM messages to the SitePoint

The `rtcmCharacteristic` is used to send RTCM messages from an NTRIP service to the SitePoint. This allows the SitePoint to get to near centimeter-level accuracy.

The next section will cover sending RTCM messages received from an NTRIP service to the SitePoint.

## Read Next

- <doc:B5_NTRIP>
