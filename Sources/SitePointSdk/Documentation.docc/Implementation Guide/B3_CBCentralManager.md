# CBCentralManager

Set up `CBCentralManager` to scan for and connect to SitePoint Bluetooth devices.

## Overview

The `CBCentralManager` handles accessing Bluetooth, discovering devices, and managing connections.

> Note: SitePoint devices are Bluetooth peripherals. In Bluetooth terms, this means they are connected from a Bluetooth central device — a mobile device running an app, in this case.

Once a SitePoint is connected, <doc:B4_CBPeripheral> accesses its SignalQuest services. 

### Reference the example app

In the SitePoint iOS Example App, the `CBCentralManager` code is in `Bluetooth.swift`.

This file also creates a delegate extension that conforms to  `CBCentralManagerDelegate`.

> Tip: This file contains some helper functions which aren't mentioned below or required, such as a timer that handles removing stale devices from the list of previously found devices.

### Scanning for SitePoint peripherals

In the example app, the scanning starts as soon as `centralManager` is available. The scan is initiated within the `centralManagerDidUpdateState` callback.

The scan specifies a filter on service UUID using `withServices:` to only return devices with the SitePoint service UUID of `00000100-34ed-12ef-63f4-317792041d17`.

```swift
func centralManagerDidUpdateState(_ central: CBCentralManager) {
    if central.state != .poweredOn {
        displayError("CBCentralManager is not powered on")
    } else {
        centralManager?.scanForPeripherals(withServices: [SitePointPeripheral.sitePointServiceUuid], options: [CBCentralManagerScanOptionAllowDuplicatesKey : true])
        BluetoothManager.logger.info("Started scanning")
    }
}
```

### Handling discovered SitePoint peripherals

When a scan finds a peripheral with the SitePoint Service UUID, it returns the peripheral using the `centralManager.didDiscover` callback.

The example app uses this callback to build a list of found SitePoint peripherals along with some manufacturer data, from the related scan response.

> Note: The example app also keeps a list of timestamps for each found peripheral. This is not required, but may be helpful to avoid stale devices remaining in the list. This is paired with a timer to do a stale device check and cleanup.

```swift
func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String: Any], rssi RSSI: NSNumber) {
    devicesToWhenFound[peripheral] = Date()
    devicesToScanStatus[peripheral] = getScanStatus(advertisementData)
}
```

### Connecting to a SitePoint peripheral 

Connect to a SitePoint by calling `centralManager.connect` and passing in the peripheral to connect.

Once connected, the `centralManager.didConnect` callback will be called.

### Initiate service discovery

From the `centralManager.didConnect` callback, call `discoverServices` on the peripheral to initiate the querying of services and their characteristics.

```swift
func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
    AppDelegate.instance.sitePoint.didConnect(peripheral)
    peripheral.discoverServices(nil)
}
```

These queries, along with additional handling for reading and writing data, are handled by `CBPeripheral` which is covered in the next section.

## Read Next

- <doc:B4_CBPeripheral>
