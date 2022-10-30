//
//  kern_dyld_patch.hpp
//  FeatureUnlock
//
//  Created by Mykola Grymalyuk on 2021-11-10.
//  Copyright © 2021-2022 Khronokernel. All rights reserved.
//

// Patch sets used by dyld patcher, see respective sections for patch set explanation
// Note the dyld patching is done recursively so all matching bytes are patched
// When developing new patch sets, ensure that all patches applied are intentional

#include <stdint.h>
#pragma mark - Sidecar/AirPlay Patch Set

// SidecarCore/AirPlaySupport share 1 large array of unsupported models.
// Namely models that do not support H.265 support:

//    iMac13,1 iMac13,2 iMac13,3 iMac14,1 iMac14,2 iMac14,3 iMac14,4 iMac15,1 iMac16,1 iMac16,2
//    MacBook8,1
//    MacBookAir5,1 MacBookAir5,2 MacBookAir6,1 MacBookAir6,2 MacBookAir7,1 MacBookAir7,2
//    MacBookPro9,1 MacBookPro9,2 MacBookPro10,1 MacBookPro10,2
//    MacBookPro11,1 MacBookPro11,2 MacBookPro11,3 MacBookPro11,4 MacBookPro11,5 MacBookPro12,1
//    Macmini6,1 Macmini6,2 Macmini7,1
//    MacPro5,1 MacPro6,1
//    iPad4,1 iPad4,2 iPad4,3 iPad4,4 iPad4,5 iPad4,6 iPad4,7 iPad4,8 iPad4,9
//    iPad5,1 iPad5,2 iPad5,3 iPad5,4 iPad6,11 iPad6,12

// In addition to this, AirPlaySupport has an extra array for excluding models that do not support a 'Unified Driver Model (UDM)'
// AirPlaySupport "requires" all models to have UART-based Wifi, however no issues have been found on legacy devices.

// To determine whether a machine is UDM-based, check whether the Wireless card is using IO80211Family or IO80211FamilyLegacy
// Keep in mind that macOS Monterey renames the IO80211 families:
// - IO80211Family   -> IO80211FamilyLegacy
// - IO80211FamilyV2 -> IO80211Family

//    iMac17,1 iMac18,1 iMac18,2 iMac18,3
//    MacBookPro13,1 MacBookPro13,2 MacBookPro13,3
//    MacBookPro14,1 MacBookPro14,2 MacBookPro14,3
//    MacMini8,1

// Note Macmini was mistyped as MacMini in 12.0 - 12.3 B1, however was resolved with 12.3 B2 (21E5206e):
// https://www.apple.com/macos/monterey/features/

static const uint8_t kSideCarAirPlayiMacOriginal[] = {
    // iMac13,1 iMac13,2 iMac13,3 iMac14,1 iMac14,2 iMac14,3 iMac14,4 iMac15,1 iMac16,1 iMac16,2
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x31, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x32, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x33, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x31, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x32, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x33, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x34, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x35, 0x2C, 0x31, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x31, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x32, 0x00,
};

static const uint8_t kSideCarAirPlayiMacAlternative2012Original[] {
    // iMac13,1 iMac13,2 iMac13,3
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x31, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x32, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x33, 0x00,
};
static const uint8_t kSideCarAirPlayiMacAlternative2013Original[] {
    // iMac14,1 iMac14,2 iMac14,3 iMac14,4
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x31, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x32, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x33, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x34, 0x00,
};
static const uint8_t kSideCarAirPlayiMacAlternative2014Original[] {
    // iMac15,1 iMac16,1 iMac16,2
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x35, 0x2C, 0x31, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x31, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x32, 0x00,
};

static const uint8_t kSideCarAirPlayMacBookOriginal[] = {
    // MacBook8,1
    // MacBookAir5,1 MacBookAir5,2 MacBookAir6,1 MacBookAir6,2 MacBookAir7,1 MacBookAir7,2
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x38, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x32, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x32, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x32, 0x00,
};

static const uint8_t kSideCarAirPlayMacBookMacBookAir2012Original[] = {
    // MacBook8,1
    // MacBookAir5,1 MacBookAir5,2
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x38, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x32, 0x00,
};

static const uint8_t kSideCarAirPlayMacBookAir2013_2015Original[] = {
    // MacBookAir6,1 MacBookAir6,2 MacBookAir7,1 MacBookAir7,2
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x32, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x32, 0x00,
};


static const uint8_t kSideCarAirPlayMacBookProOriginal[] = {
    // MacBookPro9,1 MacBookPro9,2 MacBookPro10,1 MacBookPro10,2
    // MacBookPro11,1 MacBookPro11,2 MacBookPro11,3 MacBookPro11,4 MacBookPro11,5 MacBookPro12,1
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x39, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x39, 0x2C, 0x32, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x32, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x32, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x33, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x34, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x35, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x32, 0x2C, 0x31, 0x00,
};

static const uint8_t kSideCarAirPlayMacBookPro2012Original[] = {
    // MacBookPro9,1 MacBookPro9,2 MacBookPro10,1 MacBookPro10,2
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x39, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x39, 0x2C, 0x32, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x32, 0x00,
};

static const uint8_t kSideCarAirPlayMacBookPro2013_2015Original[] = {
    // MacBookPro11,1 MacBookPro11,2 MacBookPro11,3 MacBookPro11,4 MacBookPro11,5 MacBookPro12,1
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x32, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x33, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x34, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x35, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x32, 0x2C, 0x31, 0x00,
};


static const uint8_t kSideCarAirPlayStandaloneDesktopOriginal[] = {
    // Macmini6,1 Macmini6,2 Macmini7,1
    // MacPro5,1 MacPro6,1
    0x4D, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x32, 0x00,
    0x4D, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x37, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x50, 0x72, 0x6F, 0x35, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x50, 0x72, 0x6F, 0x36, 0x2C, 0x31
};

static const uint8_t kSideCarAirPlayMacProOriginal[] = {
    // MacPro5,1 MacPro6,1
    0x4D, 0x61, 0x63, 0x50, 0x72, 0x6F, 0x35, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x50, 0x72, 0x6F, 0x36, 0x2C, 0x31
};


static const uint8_t kSideCarAirPlayMacminiOriginal[] = {
    // Macmini6,1 Macmini6,2 Macmini7,1
    0x4D, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x32, 0x00,
    0x4D, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x37, 0x2C, 0x31, 0x00,
};


static const uint8_t kSideCarAirPlayiMacPatched[] = {
    // iNac13,1 iNac13,2 iNac13,3 iNac14,1 iNac14,2 iNac14,3 iNac14,4 iNac15,1 iNac16,1 iNac16,2
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x31, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x32, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x33, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x31, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x32, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x33, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x34, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x35, 0x2C, 0x31, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x31, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x32, 0x00,
};

static const uint8_t kSideCarAirPlayiMacAlternative2012Patched[] {
    // iNac13,1 iNac13,2 iNac13,3
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x31, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x32, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x33, 0x00,
};
static const uint8_t kSideCarAirPlayiMacAlternative2013Patched[] {
    // iNac14,1 iNac14,2 iNac14,3 iNac14,4
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x31, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x32, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x33, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x34, 0x00,
};
static const uint8_t kSideCarAirPlayiMacAlternative2014Patched[] {
    // iNac15,1 iNac16,1 iNac16,2
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x35, 0x2C, 0x31, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x31, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x32, 0x00,
};

static const uint8_t kSideCarAirPlayMacBookPatched[] = {
    // NacBook8,1
    // NacBookAir5,1 NacBookAir5,2 NacBookAir6,1 NacBookAir6,2 NacBookAir7,1 NacBookAir7,2
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x38, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x32, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x32, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x32, 0x00,
};

static const uint8_t kSideCarAirPlayMacBooMacBookAir2012Patched[] = {
    // NacBook8,1
    // NacBookAir5,1 NacBookAir5,2
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x38, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x32, 0x00,
};

static const uint8_t kSideCarAirPlayMacBookAir2013_2015Patched[] = {
    // NacBookAir6,1 NacBookAir6,2 NacBookAir7,1 NacBookAir7,2
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x32, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x32, 0x00,
};


static const uint8_t kSideCarAirPlayMacBookProPatched[] = {
    // NacBookPro9,1 NacBookPro9,2 NacBookPro10,1 NacBookPro10,2
    // NacBookPro11,1 NacBookPro11,2 NacBookPro11,3 NacBookPro11,4 NacBookPro11,5 NacBookPro12,1
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x39, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x39, 0x2C, 0x32, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x32, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x32, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x33, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x34, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x35, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x32, 0x2C, 0x31, 0x00,
};

static const uint8_t kSideCarAirPlayMacBookPro2012Patched[] = {
    // NacBookPro9,1 NacBookPro9,2 NacBookPro10,1 NacBookPro10,2
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x39, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x39, 0x2C, 0x32, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x32, 0x00,
};

static const uint8_t kSideCarAirPlayMacBookPro2013_2015Patched[] = {
    // NacBookPro11,1 NacBookPro11,2 NacBookPro11,3 NacBookPro11,4 NacBookPro11,5 NacBookPro12,1
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x32, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x33, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x34, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x35, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x32, 0x2C, 0x31, 0x00,
};


static const uint8_t kSideCarAirPlayStandaloneDesktopPatched[] = {
    // Nacmini6,1 Nacmini6,2 Nacmini7,1
    // NacPro5,1 NacPro6,1
    0x4E, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x32, 0x00,
    0x4E, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x37, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x50, 0x72, 0x6F, 0x35, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x50, 0x72, 0x6F, 0x36, 0x2C, 0x31
};

static const uint8_t kSideCarAirPlayMacminiPatched[] = {
    // Nacmini6,1 Nacmini6,2 Nacmini7,1
    0x4E, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x32, 0x00,
    0x4E, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x37, 0x2C, 0x31, 0x00,
};

static const uint8_t kSideCarAirPlayMacProPatched[] = {
    // NacPro5,1 NacPro6,1
    0x4E, 0x61, 0x63, 0x50, 0x72, 0x6F, 0x35, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x50, 0x72, 0x6F, 0x36, 0x2C, 0x31
};

// SidecarCore.framework
// Replaces iPad with hPad
static const uint8_t kSidecariPadModelOriginal[] = {
    // iPad4,1 iPad4,2 iPad4,3 iPad4,4 iPad4,5 iPad4,6 iPad4,7 iPad4,8 iPad4,9
    // iPad5,1 iPad5,2 iPad5,3 iPad5,4 iPad6,11 iPad6,12
    0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x31, 0x00,
    0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x32, 0x00,
    0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x33, 0x00,
    0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x34, 0x00,
    0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x35, 0x00,
    0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x36, 0x00,
    0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x37, 0x00,
    0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x38, 0x00,
    0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x39, 0x00,
    0x69, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x31, 0x00,
    0x69, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x32, 0x00,
    0x69, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x33, 0x00,
    0x69, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x34, 0x00,
    0x69, 0x50, 0x61, 0x64, 0x36, 0x2C, 0x31, 0x31, 0x00,
    0x69, 0x50, 0x61, 0x64, 0x36, 0x2C, 0x31, 0x32
};

static const uint8_t kSidecariPadModelPatched[] = {
    // hPad4,1 hPad4,2 hPad4,3 hPad4,4 hPad4,5 hPad4,6 hPad4,7 hPad4,8 hPad4,9
    // hPad5,1 hPad5,2 hPad5,3 hPad5,4 hPad6,11 hPad6,12
    0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x31, 0x00,
    0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x32, 0x00,
    0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x33, 0x00,
    0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x34, 0x00,
    0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x35, 0x00,
    0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x36, 0x00,
    0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x37, 0x00,
    0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x38, 0x00,
    0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x39, 0x00,
    0x68, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x31, 0x00,
    0x68, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x32, 0x00,
    0x68, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x33, 0x00,
    0x68, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x34, 0x00,
    0x68, 0x50, 0x61, 0x64, 0x36, 0x2C, 0x31, 0x31, 0x00,
    0x68, 0x50, 0x61, 0x64, 0x36, 0x2C, 0x31, 0x32
};

// AirPlaySupport.framework
// Replaces Mac with Nac
static const uint8_t kMacModelAirplayExtendedOriginal[] = {
    // iMac17,1 iMac18,1 iMac18,2 iMac18,3
    // MacBookPro13,1 MacBookPro13,2 MacBookPro13,3 MacBookPro14,1 MacBookPro14,2 MacBookPro14,3
    // MacMini8,1
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x37, 0x2C, 0x31, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x38, 0x2C, 0x31, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x38, 0x2C, 0x32, 0x00,
    0x69, 0x4D, 0x61, 0x63, 0x31, 0x38, 0x2C, 0x33, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x33, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x33, 0x2C, 0x32, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x33, 0x2C, 0x33, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x34, 0x2C, 0x31, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x34, 0x2C, 0x32, 0x00,
    0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x34, 0x2C, 0x33, 0x00,
    0x4D, 0x61, 0x63, // 0x4D, 0x69, 0x6E, 0x69, 0x38, 0x2C, 0x31 // 12.0 - 12.3 B1 is MacMini8,1, 12.3 B2+ is Macmini8,1
};

static const uint8_t kMacModelAirplayExtendedPatched[] = {
    // iNac17,1 iNac18,1 iNac18,2 iNac18,3
    // NacBookPro13,1 NacBookPro13,2 NacBookPro13,3 NacBookPro14,1 NacBookPro14,2 NacBookPro14,3
    // NacMini8,1
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x37, 0x2C, 0x31, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x38, 0x2C, 0x31, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x38, 0x2C, 0x32, 0x00,
    0x69, 0x4E, 0x61, 0x63, 0x31, 0x38, 0x2C, 0x33, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x33, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x33, 0x2C, 0x32, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x33, 0x2C, 0x33, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x34, 0x2C, 0x31, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x34, 0x2C, 0x32, 0x00,
    0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x34, 0x2C, 0x33, 0x00,
    0x4E, 0x61, 0x63, // 0x4E, 0x69, 0x6E, 0x69, 0x38, 0x2C, 0x31 // 12.0 - 12.3 B1 is MacMini8,1, 12.3 B2+ is Macmini8,1
};

static const uint8_t kAirPlayVmmOriginal[] = {
    // p2pAllow kern.hv_vmm_present
    0x70, 0x32, 0x70, 0x41, 0x6C, 0x6C, 0x6F, 0x77, 0x00,
    0x6B, 0x65, 0x72, 0x6E, 0x2E, 0x68, 0x76, 0x5F, 0x76, 0x6D, 0x6D, 0x5F, 0x70, 0x72, 0x65, 0x73, 0x65, 0x6E, 0x74
};

static const uint8_t kAirPlayVmmPatched[] = {
    // p2pAllow kern.hv_acidanthera
    0x70, 0x32, 0x70, 0x41, 0x6C, 0x6C, 0x6F, 0x77, 0x00,
    0x6B, 0x65, 0x72, 0x6E, 0x2E, 0x68, 0x76, 0x5F, 0x61, 0x63, 0x69, 0x64, 0x61, 0x6E, 0x74, 0x68, 0x65, 0x72, 0x61
};

#pragma mark - NightShift Patch Set

// CoreBrightness.framework
// Lowers NightShift requirement: 10.12 - 10.13.0

// With macOS 10.12.4, Apple added NightShift support to all 2012+ Macs
// However omitted support for older models without a clear reason.
// This patch lowers the requirement to the bare minimum (ie. MacBook8,1 -> MacBook1,1)
// Patch set originally developed by Pike.R.Alpha:
// https://pikeralpha.wordpress.com/2017/01/30/4398/
// Exact strings pulled from CDF's NightShiftEnabler:
// https://github.com/cdf/NightShiftEnabler

// Note macOS 10.13.1 added iMacPro model family thus shifting the patch to include it
// If new Mac families are introduced, expect NightShift patch set to be adjusted again

static const uint8_t kNightShiftLegacyOriginal[] = {
    // MacBookPro9,x iMac13,x Macmini6,x MacBookAir5,x MacPro6,1 MacBook8,1
    0x09, 0x00, 0x00, 0x00,
    0x0D, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00,
    0x05, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00
};
static const uint8_t kNightShiftLegacyPatched[] = {
    // MacBookPro1,x iMac1,x Macmini1,x MacBookAir1,x MacPro1,1 MacBook1,1
    0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00
};

// CoreBrightness.framework
// Lowers NightShift requirement: 10.13.1+
static const uint8_t kNightShiftOriginal[] = {
    // MacBookPro9,x iMacPro1,1 iMac13,x Macmini6,x MacBookAir5,x MacPro6,1 MacBook8,1
    0x09, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00,
    0x0D, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00,
    0x05, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00
};
static const uint8_t kNightShiftPatched[] = {
    // MacBookPro1,x iMacPro1,1 iMac1,x Macmini1,x MacBookAir1,x MacPro1,1 MacBook1,1
    0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00
};

#pragma mark - Verify Patch Size

// Patching the dyld requires that both the find and replace are of same length
static_assert(sizeof(kSideCarAirPlayMacBookOriginal) == sizeof(kSideCarAirPlayMacBookPatched), "patch size invalid");
static_assert(sizeof(kSideCarAirPlayMacBookProOriginal) == sizeof(kSideCarAirPlayMacBookProPatched), "patch size invalid");
static_assert(sizeof(kSideCarAirPlayiMacOriginal) == sizeof(kSideCarAirPlayiMacPatched), "patch size invalid");
static_assert(sizeof(kSideCarAirPlayStandaloneDesktopOriginal) == sizeof(kSideCarAirPlayStandaloneDesktopPatched), "patch size invalid");
static_assert(sizeof(kMacModelAirplayExtendedOriginal) == sizeof(kMacModelAirplayExtendedPatched), "patch size invalid");
static_assert(sizeof(kSidecariPadModelOriginal) == sizeof(kSidecariPadModelPatched), "patch size invalid");
static_assert(sizeof(kNightShiftLegacyOriginal) == sizeof(kNightShiftLegacyPatched), "patch size invalid");
static_assert(sizeof(kNightShiftOriginal) == sizeof(kNightShiftPatched), "patch size invalid");
