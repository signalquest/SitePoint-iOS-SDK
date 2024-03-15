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
**  File:     sqspTypes.h
**  Purpose:  SignalQuest SitePoint Data Types
**
*******************************************************************************/

//              -- NOTE ON NEARLY-DUPLICATE STRUCTURE FORMATS --
//  Some high level languages don't like working with structures with bitfields.
//  As such, there are structures, and conversion methods, to work with these
//  languages.

#ifndef   __SQSPTYPES_H__
#define   __SQSPTYPES_H__

#ifdef    __cplusplus
extern "C" {
#endif  //__cplusplus

//  Includes
#include <stdbool.h>
#include <stdint.h>

//  Defines

//  Data types
typedef enum SqspSolType_e
{
  SQSP_SOLTYPE_OFFLINE        = 0,      //  GPS receiver is powered off
  SQSP_SOLTYPE_ACQUIRING      = 1,      //  Acquiring satellites and satellite 
                                        //    orbit information
  SQSP_SOLTYPE_2D             = 2,      //  2D positioning mode
  SQSP_SOLTYPE_3D             = 3,      //  3D positioning mode
  SQSP_SOLTYPE_RTK_FLOAT      = 4,      //  RTK mode, unresolved integer
                                        //    ambiguity
  SQSP_SOLTYPE_RTK_FIXED      = 5,      //  RTK mode, high precision
  SQSP_SOLTYPE_AUTO_SURVEYING = 6,      //  local base mode, auto-surveying base
                                        //    position
  SQSP_SOLTYPE_FIXED_BASE     = 7,      //  local base mode, active base
  SQSP_SOLTYPE_UNSUPPORTED    = 8,      //  GPS is in a mode we do not support
} SqspSolType_t;

//  Compact ("C") structures making use of bitfields.
typedef struct SqspLbModeC_s
{
  uint8_t fixedBaseEnable   : 1;        //  0: Operate as rover
                                        //  1: Operate as base
  uint8_t autoSurveyEnable  : 1;        //  0: Operate as base using LLA
                                        //    [Is this correct?]
                                        //  1: Operate as base attempting self
                                        //    survey
  uint8_t connected         : 1;        //  READ ONLY - Ignored on write.
  uint8_t correctionOutput  : 1;        //  0: Prefer BLE Corrections
                                        //  1: Prefer Wifi Corrections
  uint8_t correctionInput   : 1;        //  0: Prefer NTRIP aiding over BLE
                                        //  1: Prefer Local FIXED BASE RTCM over
                                        //    BLE
  uint8_t tripodCorrections : 1;        //  1: Connected to a base and receiving
                                        //    corrections
  uint8_t validOrNotBusy    : 1;        //  1: "Data is Valid" or "We're BUSY".
  uint8_t broadcastEnable   : 1;        //  Used when fixedBaseEnable==1
} SqspLbModeC_t;

typedef struct SqspLbConfigC_s
{
  int32_t       lon;                    //  Longitude [deg] * 1e-7
  int32_t       lat;                    //  Latitude  [deg] * 1e-7
  int32_t       height;                 //  Height above geoid [mm]
  uint32_t      hAcc;                   //  Horizontal accuracy [mm] * 0.1
  uint32_t      vAcc;                   //  Vertical accuracy [mm] * 0.1
  int8_t        lonHp;                  //  Longitude [deg] high precision
                                        //    * 1e-9
  int8_t        latHp;                  //  Latitude [deg] high precision
                                        //    * 1e-9
  int8_t        heightHp;               //  Height above geoid [mm] high
                                        //    precision * 0.1
  SqspLbModeC_t mode;
  uint32_t      duration;               //  Seconds
  int32_t       hMSL;                   //  Height above Mean Sea Level [mm]
  int8_t        hMSLHp;                 //  Height about Mean Sea Level [mm]
                                        //    high precision * 0.1
  int8_t        reserved[3];            //  Pad length to a multiple of 4 bytes
} SqspLbConfigC_t;

typedef struct SqspRspC_s
{
  uint16_t mfgDataId;                   //  ???
  uint8_t  batteryLevel;                //  Battery level [0-100]
  uint8_t  systemPowerState;            //  (Dis)charge state
  uint16_t runTimeRemaining;            //  Run/charge time estimate in minutes
  uint8_t  satelliteCount;              //  Current number of satellites in use
  uint8_t  aidingBins;                  //  Each bit denotes an RTCM correction
                                        //    was received on an 8-second cycle.
  uint8_t  differential        : 1;     //  1: GNSS aided with Differential
                                        //     Corrections
  uint8_t  gpsFixOk            : 1;     //  1: Valid Fix
  uint8_t  ambiguity           : 2;     //  RTK Ambiguity:
                                        //    0: No RTK
                                        //    1: Float RTK operation
                                        //    2: Fixed RTK operation
  uint8_t  fix                 : 4;     //  GNSS Fix Type:
                                        //    0: No Fix
                                        //    1: No Fix
                                        //    2: 2D Fix
                                        //    3: 3D Fix
                                        //    4: GNSS
                                        //    5: Fixed Base (Time Only) Fix
  uint8_t  coprocOk            : 2;     //  Factory Use
  uint8_t  surveyFailed        : 1;     //  1: Survey In Operation Failed
  uint8_t  surveyPositionValid : 1;     //  1: Survey In Operation Completed
  uint8_t  surveyInProgress    : 1;     //  1: Survey In Busy
  uint8_t  headingFlag         : 1;     //  Factory Use
  uint8_t  posValid            : 1;     //  1: Relative NED position is valid
  uint8_t  validTime           : 1;     //  1: UTC Time is Valid (GNSS-derived)
  SqspLbModeC_t mode;
} __attribute__((packed)) SqspRspC_t;

typedef struct SqspStatusC_s
{
  uint32_t  iTOW;                       //  GPS time of week [ms]
  uint16_t  year;                       //  Year [UTC], or 0 if time unknown
  uint8_t   month;                      //  Month [UTC], 1-12 or 0 if unknown
  uint8_t   day;                        //  Day [UTC], 1-31 or 0 if unknown
  uint8_t   hour;                       //  Hour [UTC], 0-23 0 if unknown
  uint8_t   min;                        //  Minute [UTC], 0-59 or 0 if unknown
  uint8_t   sec;                        //  Seconds [UTC], 0-59 or 0 if unknown
  uint8_t   solType;                    //  GNSS Solution Type (SqspSolType_t)
  uint8_t   numSV;                      //  Number of satellites used in
                                        //    position solution
  uint8_t   battery;                    //  Current charge of battery, if any
                                        //    (or 0 if none)
  SqspRspC_t rsp;
} SqspStatusC_t;

typedef struct SqspRelPosC_s
{
  uint32_t iTOW;                        //  GPS time of week [ms]
  int32_t  posN;                        //  Northing Low-Precision  [cm]
  int32_t  posE;                        //  Easting Low-Precision   [cm]
  int32_t  posD;                        //  -Height Low-Precision   [cm]
  int8_t   posHpN;                      //  Northing High-Precision [mm]
  int8_t   posHpE;                      //  Easting High-Precision  [mm]
  int8_t   posHpD;                      //  -Height High-Precision  [mm]
} SqspRelPosC_t;

typedef struct SqspLlaC_s
{
  uint32_t iTOW;                        //  GPS time of week [ms]
  int32_t  lon;                         //  Longitude [deg] * 1e-7
  int32_t  lat;                         //  Latitude  [deg] * 1e-7
  int32_t  height;                      //  Height above geoid [mm]
  int8_t   lonHp;                       //  Longitude [deg] high precision
                                        //    * 1e-9
  int8_t   latHp;                       //  Latitude [deg] high precision
                                        //    * 1e-9
  int8_t   heightHp;                    //  Height about geoid [mm] high
                                        //    precision [mm] * 0.1
  int8_t   hMSLHp;                      //  Height above Mean Sea Level high
                                        //    precision [mm] * 0.1
  uint32_t hAcc;                        //  Horizontal accuracy [mm] * 0.1
  uint32_t vAcc;                        //  Vertical accuracy [mm] * 0.1
	int32_t  hMSL;                        //  Height above Mean Sea Level [mm]
} SqspLlaC_t;

//  No-bitfield versions of above - used on the phone/computer app side
typedef struct SqspLbMode_s
{
  uint8_t fixedBaseEnable;              //  0: Operate as rover
                                        //  1: Operate as base
  uint8_t autoSurveyEnable;             //  0: Operate as base using LLA
                                        //    [Is this correct?]
                                        //  1: Operate as base attempting self
                                        //    survey
  uint8_t connected;                    //  READ ONLY - Ignored on write.
  uint8_t correctionOutput;             //  0: Prefer BLE Corrections
                                        //  1: Prefer Wifi Corrections
  uint8_t correctionInput;              //  0: Prefer NTRIP aiding over BLE
                                        //  1: Prefer Local FIXED BASE RTCM over
                                        //    BLE
  uint8_t tripodCorrections;            //  1: Connected to a base and receiving
                                        //    corrections
  uint8_t validOrNotBusy;               //  1: "Data is Valid" or "We're BUSY".
  uint8_t broadcastEnable;              //  Used when fixedBaseEnable==1
} SqspLbMode_t;

typedef struct SqLbConfig_s
{
  double       lon;                     //  Converted from lon + lonHp [deg]
  double       lat;                     //  Converted from lat + latHp [deg]
  double       height;                  //  Converted from height + heightHp [m]
  double       hMSL;                    //  Converted from hMSL + hMSLHp [m]
  double       hAcc;                    //  Converted from hAccInt [m]
  double       vAcc;                    //  Converted from vAccInt [m]
  uint32_t     duration;                //  Seconds
  SqspLbMode_t mode;
  uint8_t      reserved[4];
} SqspLbConfig_t;

typedef struct SqspRsp_s
{
  uint16_t mfgDataId;                   //  ???
  uint8_t  batteryLevel;                //  Battery level [0-100]
  uint8_t  systemPowerState;            //  (Dis)charge state
  uint16_t runTimeRemaining;            //  Run/charge time estimate in minutes
  uint8_t  satelliteCount;              //  Current Number of Satellites in use
  uint8_t  aidingBins;                  //  Each bit denotes an RTCM correction
                                        //    was received on an 8-second cycle.
  uint8_t  differential;                //  1: GNSS aided with Differential
                                        //    Corrections
  uint8_t  gpsFixOk;                    //  1: Valid Fix
  uint8_t  ambiguity;                   //  RTK Ambiguity:
                                        //    0: No RTK
                                        //    1: Float RTK operation
                                        //    2: Fixed RTK operation
  uint8_t  fix;                         //  GNSS Fix Type:
                                        //    0: No Fix
                                        //    1: No Fix
                                        //    2: 2D Fix
                                        //    3: 3D Fix
                                        //    4: GNSS
                                        //    5: Fixed Base (Time Only) Fix
  uint8_t  coprocOk;                    //  Factory Use
  uint8_t  surveyFailed;                //  1: Survey In Operation Failed
  uint8_t  surveyPositionValid;         //  1: Survey In Operation Completed
  uint8_t  surveyInProgress;            //  1: Survey In Busy
  uint8_t  headingFlag;                 //  Factory Use
  uint8_t  posValid;                    //  1: Relative NED position is valid
  uint8_t  validTime;                   //  1: UTC Time is Valid (GNSS-derived)
  SqspLbMode_t mode;
} SqspRsp_t;

typedef struct SqspStatus_s
{
  uint32_t     iTOW;                    //  GPS time of week [ms]
  uint32_t     time;                    //  UTC time; can't use time_t
  uint8_t      solType;                 //  GNSS Solution Type (SqspSolType_t)
  uint8_t      numSV;                   //  Number of satellites used in
                                        //    position solution
  uint8_t      battery;                 //  Current charge of battery, if any
                                        //    (or 0 if none)
  uint8_t      reserved;                //  Unused
  SqspRsp_t rsp;
  uint8_t      reserved2;               //  Pad length to a multiple of 4 bytes
} SqspStatus_t;

typedef struct SqspRelPos_s
{
  uint32_t iTOW;                        //  GPS time of week [ms]
  double   posN;                        //  Converted from posN+posNHp [m]
  double   posE;                        //  Converted from posE+posEHp [m]
  double   posD;                        //  Converted from posD+posDHp [m]
} SqspRelPos_t;

typedef struct SqspLla_s
{
  uint32_t iTOW;                        //  GPS time of week [ms]
  uint32_t reserved;                    //  Unused
  double   lon;                         //  Converted from lon + lonHp [m]
  double   lat;                         //  Converted from lat + latHp [m]
  double   height;                      //  Converted from height + heightHp [m]
  double   hMSL;                        //  Converted from hMSL + hMSLHp [m]
  double   hAcc;                        //  Converted from hAcc
  double   vAcc;                        //  Converted from vAcc
} SqspLla_t;

//  Host MCU-related data types
typedef enum SqspHostMcuCommand_e
{
  SQSP_HOST_COMMAND_NONE = 0,
  SQSP_HOST_COMMAND_START_TRIPOD_AIDING = 1,
  SQSP_HOST_COMMAND_STOP_TRIPOD_AIDING = 2,
  SQSP_HOST_COMMAND_START_TRIPOD_AIDING_DELAYED = 3,
} SqspHostMcuCommand_t;

//  Constants

//  Variables

//  Functions
bool sqspLbModeExpand(  SqspLbMode_t  *lbm, const SqspLbModeC_t *lbms );
bool sqspLbModeCompact( SqspLbModeC_t *lbm, const SqspLbMode_t  *lbms );

bool sqspLbConfigExpand(  SqspLbConfig_t  *lbc, const SqspLbConfigC_t *lbcs );
bool sqspLbConfigCompact( SqspLbConfigC_t *lbc, const SqspLbConfig_t  *lbcs );

bool sqspRspExpand(  SqspRsp_t  *rsp, const SqspRspC_t *rsps );
bool sqspRspCompact( SqspRspC_t *rsp, const SqspRsp_t  *rsps );

bool sqspStatusExpand(  SqspStatus_t  *s, const SqspStatusC_t *ss );
bool sqspStatusCompact( SqspStatusC_t *s, const SqspStatus_t  *ss );

bool sqspRelPosExpand(  SqspRelPos_t  *rp, const SqspRelPosC_t *rps );
bool sqspRelPosCompact( SqspRelPosC_t *rp, const SqspRelPos_t  *rps );

bool sqspLlaExpand(  SqspLla_t  *lla, const SqspLlaC_t *llas );
bool sqspLlaCompact( SqspLlaC_t *lla, const SqspLla_t  *llas );

const uint8_t *sqspSolutionTypeLabel( uint8_t index );

#ifdef    __cplusplus
}
#endif  //__cplusplus

#endif  //__SQSPTYPES_H__
