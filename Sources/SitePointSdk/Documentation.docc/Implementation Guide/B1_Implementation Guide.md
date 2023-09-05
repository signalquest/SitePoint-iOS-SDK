# Implementation Guide

Review example app code to use the SitePoint SDK with Bluetooth and NTRIP.

## Overview

These are the high-level steps required to prepare your app for interfacing with the SitePoint SDK:

1. Declare <doc:B2_Permissions> for Bluetooth and Location Services.

2. Set up <doc:B3_CBCentralManager> to handle Bluetooth scanning and connections.

3. Set up <doc:B4_CBPeripheral> and delegate to query the connected SitePoint peripheral and to send and receive data.

5. Add handling for <doc:B5_NTRIP> connection management and RTCM parsing for aiding a SitePoint.

## Read Next

- <doc:B2_Permissions>
a
