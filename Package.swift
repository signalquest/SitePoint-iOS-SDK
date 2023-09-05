// swift-tools-version: 5.8

import PackageDescription

let package = Package(
    name: "SitePointSdk",
    platforms: [.iOS(.v14)],
    products: [
        .library(
            name: "SitePointSdk",
            targets: ["SitePointSdk", "SitePointLib"]),
    ],
    dependencies: [
    ],
    targets: [
        .target(name: "SitePointSdk", dependencies: ["SitePointLib"], path: "Sources/SitePointSdk"),
        .binaryTarget(name: "SitePointLib", path: "Sources/SQSitePoint.xcframework")
    ]
)
