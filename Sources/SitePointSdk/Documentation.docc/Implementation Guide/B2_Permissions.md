# Permissions

Add permissions for Bluetooth and Location services.

## Adding permissions to your app

### Adding permissions to the Info.plist directly

In the Info.plist file, add the following permissions and adjust their text values to match your app's use case. These will be shown to end users when requesting their permission.

```
<key>NSLocationWhenInUseUsageDescription</key>
<string>$(PRODUCT_NAME) sends positions to some NTRIP services, as required.</string>
<key>NSLocationAlwaysAndWhenInUseUsageDescription</key>
<string>$(PRODUCT_NAME) sends positions to some NTRIP services, as required.</string>
<key>NSLocationAlwaysUsageDescription</key>
<string>$(PRODUCT_NAME) sends positions to some NTRIP services, as required.</string>
<key>NSBluetoothAlwaysUsageDescription</key>
<string>$(PRODUCT_NAME) interfaces with SitePoints.</string>
<key>NSBluetoothPeripheralUsageDescription</key>
<string>$(PRODUCT_NAME) interfaces with SitePoints.</string>
<key>UISupportedInterfaceOrientations</key>
```

### Adding permissions to the Info.plist using the GUI

Alternatively, you can add these from the Xcode native Info.plist editor by adding the extended key names and values.

| Key                                              | Value           |
| ------------------------------------------------ | --------------- |
| Privacy - Location When In Use Usage Description | $(PRODUCT_NAME) sends positions to some NTRIP services, as required. |
| Privacy - Location Always and When In Use Usage Description | $(PRODUCT_NAME) sends positions to some NTRIP services, as required. |
| Privacy - Location Always Usage Description | $(PRODUCT_NAME) sends positions to some NTRIP services, as required. |
| Privacy - Bluetooth Always Usage Description | $(PRODUCT_NAME) interfaces with SitePoints. |
| Privacy - Bluetooth Peripheral Usage Description | $(PRODUCT_NAME) interfaces with SitePoints. |

![Info.plist permissions](Permissions-Info-plist)


## Read Next

- <doc:B3_CBCentralManager>
