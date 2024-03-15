/*******************************************************************************
**  Copyright 2024 - SignalQuest, Inc.    PROPRIETARY & CONFIDENTIAL
********************************************************************************
**
**  This file is confidential and proprietary property of SignalQuest, Inc.
**  All rights are reserved. This file may not be used, reproduced or
**  distributed by any unauthorized party.  Unauthorized copies of this file
**  must be deleted or destroyed immediately.
**
********************************************************************************
**
**  File:     sqtpSubframeIDs.h
**  Purpose:  SignalQuest Transport Protocol Subframe IDs
**
*******************************************************************************/

/*******************************************************************************
**  Revision Log
********************************************************************************
**  Rev   Date      Editor  Notes
**  ----------------------------------------------------------------------------
**  0.01  20231220  KRH     Initial Design (SitePoint subframe IDs)
**
*******************************************************************************/

//                        !!NOTE ON ADDING NEW IDS!!
//  To avoid value reuse, please help to maintain IDs being sorted by value. The
//  only exception being reserved values at the top of the list. Generally, IDs
//  will probably be grouped with associated IDs. If this list gets so large
//  that we need to start finding individual unassigned IDs, then we should
//  probably redefine the protocol.

#ifndef   __SQTPSUBFRAMEIDS_H__
#define   __SQTPSUBFRAMEIDS_H__

#ifdef    __cplusplus
extern "C" {
#endif  //__cplusplus

//  Includes
#include <stdint.h>

//  Defines
#define sqtpSubframeIdIsReserved(a) ( ( (a) == SQTP_ID_RESERVED_0000 )  \
                                    ||( (a) == SQTP_ID_RESERVED_FFFF ) )
                                    //  Non-zero if (a) is a reserved value

//  Data types
typedef enum SqtpSubframeId_e
{
  //  Reserved IDs - do not reuse!
  SQTP_ID_RESERVED_0000                                               = 0x0000,
  SQTP_ID_RESERVED_FFFF                                               = 0xFFFF,

  //  Legacy Request/Response IDs
  SQTP_ID_LEGACY_REQUEST                                              = 0x0080,
  SQTP_ID_LEGACY_RESPONSE                                             = 0x0081,

  //  RTCM Messages (using RTCM message ID)
  SQTP_ID_RTCM                                                        = 0x00D3,
  
  //  SitePoint Subframe IDs
  SQTP_ID_SITEPOINT_OTA_MTU                                           = 0x122F,
  SQTP_ID_SITEPOINT_OTA_UPDATE                                        = 0x1230,
  SQTP_ID_SITEPOINT_OTA_STATUS                                        = 0x1231,
  SQTP_ID_SITEPOINT_RTCM                                              = 0x1232,
  
  //  SitePoint Compact Subframe IDs
  SQTP_ID_SITEPOINT_STATUS_COMPACT                                    = 0x1233,
  SQTP_ID_SITEPOINT_LLA_COMPACT                                       = 0x1234,
  SQTP_ID_SITEPOINT_LOCAL_BASE_CONFIG_COMPACT                         = 0x1235,
  SQTP_ID_SITEPOINT_RELPOS_COMPACT                                    = 0x1236,
  
  SQTP_ID_SITEPOINT_HOSTMCU_STATUS                                    = 0x1237,
  SQTP_ID_SITEPOINT_BLE_STATUS                                        = 0x1238,

  //  SitePoint Non-compact (No bitfields) Subframe IDs
  SQTP_ID_SITEPOINT_STATUS                                            = 0x1243,
  SQTP_ID_SITEPOINT_LLA                                               = 0x1244,
  SQTP_ID_SITEPOINT_LOCAL_BASE_CONFIG                                 = 0x1245,
  SQTP_ID_SITEPOINT_RELPOS                                            = 0x1246,
  
  //  uBlox-originating Subframe messages ID
  SQTP_ID_UBLOX                                                       = 0x62B5,

} __attribute__((enum_extensibility(closed))) SqtpSubframeId_t;

//  Constants

//  Variables

//  Functions

#ifdef    __cplusplus
}
#endif  //__cplusplus

#endif  //__SQTPSUBFRAMEIDS_H__
