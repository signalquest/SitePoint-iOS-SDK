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

#include "os_target.h"

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
} ENUM_ATTR SqspSolType_t;

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
} PACKED_ATTR SqspLbModeC_t;

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
} PACKED_ATTR SqspLbConfigC_t;

#if (defined(SWIGJAVA) || defined(__FFIGENDART__) ) // NOTE: __FFIGENDART__ is defined (or not) in the ffigen.yaml file under "compiler-opts:" as "'-D__FFIGEN__'"
	// Do not define SqspSystemPowerC_s, SqspSystemPowerC_t
#else
//  Compact ("C") structures making use of bitfields.
	typedef struct SqspSystemPowerC_s
	{
		uint8_t State             : ((4 - 0) + 1); //  bits 0-4 One of : System_Power_State_e
		uint8_t SPARE             : 1; //  SPARE
		uint8_t Charging          : 1; //  Charging/Discharging		1=Charging/0=Discharging
		uint8_t Error             : 1; //  Charge/Discharge Error   1=Error (Query for more information, something is wrong!)
	} PACKED_ATTR SqspSystemPowerC_t;
#endif

typedef struct SqspRspC_s
{
  uint16_t mfgDataId;                   //  ???
  uint8_t  batteryLevel;                //  Battery level [0-100]
#if (defined(SWIGJAVA) || defined(__FFIGENDART__) )
  uint8_t  systemPowerState;            //  (Dis)charge state
#else
  SqspSystemPowerC_t Power;             //  (Dis)charge state	//TODO: Made permanent in SitePoint/NPG, adjust dependent projects accordingly.  See: defined(POWER_STATE_UPGRADE)
#endif
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
} PACKED_ATTR SqspRspC_t;

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
} PACKED_ATTR SqspStatusC_t;

typedef struct SqspRelPosC_s
{
  uint32_t iTOW;                        //  GPS time of week [ms]
  int32_t  posN;                        //  Northing Low-Precision  [cm]
  int32_t  posE;                        //  Easting Low-Precision   [cm]
  int32_t  posD;                        //  -Height Low-Precision   [cm]
  int8_t   posHpN;                      //  Northing High-Precision [mm]
  int8_t   posHpE;                      //  Easting High-Precision  [mm]
  int8_t   posHpD;                      //  -Height High-Precision  [mm]
} PACKED_ATTR SqspRelPosC_t;

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
   int32_t  hMSL;                       //  Height above Mean Sea Level [mm]
} PACKED_ATTR SqspLlaC_t;

//  No-bitfield versions of above - used on the phone/computer app side
#ifdef SWIGJAVA
typedef struct SqspLbMode_s
{
  char    fixedBaseEnable;              //  0: Operate as rover
                                        //  1: Operate as base
  char    autoSurveyEnable;             //  0: Operate as base using LLA
                                        //    [Is this correct?]
                                        //  1: Operate as base attempting self
                                        //    survey
  char    connected;                    //  READ ONLY - Ignored on write.
  char    correctionOutput;             //  0: Prefer BLE Corrections
                                        //  1: Prefer Wifi Corrections
  char    correctionInput;              //  0: Prefer NTRIP aiding over BLE
                                        //  1: Prefer Local FIXED BASE RTCM over
                                        //    BLE
  char    tripodCorrections;            //  1: Connected to a base and receiving
                                        //    corrections
  char    validOrNotBusy;               //  1: "Data is Valid" or "We're BUSY".
  char    broadcastEnable;              //  Used when fixedBaseEnable==1
} SqspLbMode_t;
#else
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
#endif

#ifdef SWIGJAVA
typedef struct SqLbConfig_s
{
    double       lon;                     //  Converted from lon + lonHp [deg]
    double       lat;                     //  Converted from lat + latHp [deg]
    double       height;                  //  Converted from height + heightHp [m]
    double       hMSL;                    //  Converted from hMSL + hMSLHp [m]
    double       hAcc;                    //  Converted from hAccInt [m]
    double       vAcc;                    //  Converted from vAccInt [m]
    int          duration;                //  Seconds
    SqspLbMode_t mode;
    char         reserved[4];
} SqspLbConfig_t;
#else
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
#endif

#if (defined(SWIGJAVA) || defined(__FFIGENDART__) ) // NOTE: __FFIGENDART__ is defined (or not) in the ffigen.yaml file under "compiler-opts:" as "'-D__FFIGEN__'"
typedef struct SqspRsp_s
{
  short    mfgDataId;                   //  ???
  char     batteryLevel;                //  Battery level [0-100]
  char     systemPowerState;            //  (Dis)charge state
  short    runTimeRemaining;            //  Run/charge time estimate in minutes
  char     satelliteCount;              //  Current Number of Satellites in use
  char     aidingBins;                  //  Each bit denotes an RTCM correction
                                        //    was received on an 8-second cycle.
  char     differential;                //  1: GNSS aided with Differential
                                        //    Corrections
  char     gpsFixOk;                    //  1: Valid Fix
  char     ambiguity;                   //  RTK Ambiguity:
                                        //    0: No RTK
                                        //    1: Float RTK operation
                                        //    2: Fixed RTK operation
  char     fix;                         //  GNSS Fix Type:
                                        //    0: No Fix
                                        //    1: No Fix
                                        //    2: 2D Fix
                                        //    3: 3D Fix
                                        //    4: GNSS
                                        //    5: Fixed Base (Time Only) Fix
  char     coprocOk;                    //  Factory Use
  char     surveyFailed;                //  1: Survey In Operation Failed
  char     surveyPositionValid;         //  1: Survey In Operation Completed
  char     surveyInProgress;            //  1: Survey In Busy
  char     headingFlag;                 //  Factory Use
  char     posValid;                    //  1: Relative NED position is valid
  char     validTime;                   //  1: UTC Time is Valid (GNSS-derived)
  SqspLbMode_t mode;
} SqspRsp_t;
#else
typedef struct SqspRsp_s
{
  uint16_t mfgDataId;                   //  ???
  uint8_t  batteryLevel;                //  Battery level [0-100]
#if (defined(SWIGJAVA) || defined(__FFIGENDART__) ) // NOTE: __FFIGENDART__ is defined (or not) in the ffigen.yaml file under "compiler-opts:" as "'-D__FFIGEN__'"
  uint8_t  systemPowerState;            //  (Dis)charge state
#else
  SqspSystemPowerC_t Power;             //  (Dis)charge state	//TODO: Made permanent in SitePoint/NPG, adjust dependent projects accordingly.  See: defined(POWER_STATE_UPGRADE)
#endif
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
#endif

#ifdef SWIGJAVA
//References about unsigned Java types:
// https://stackoverflow.com/questions/9854166/declaring-an-unsigned-int-in-java
// https://docs.oracle.com/javase/tutorial/java/nutsandbolts/datatypes.html
//
//As of Java 8, this is no longer true. In Java SE 8 and later, you can use the int data type to represent an unsigned 32-bit integer, which has a minimum value of 0 and a maximum value of 2^32-1. - see docs.oracle.com/javase/tutorial/java/nutsandbolts/… and docs.oracle.com/javase/8/docs/api/java/lang/Integer.html
//@7SpecialGems: I have updated the answer to include that information. That being said, it's not possible to declare unsigned integers or exclude negative values, it's only possible to use an int as if it were unsigned by using various methods. –
//Simeon Visser
// Jan 12, 2015 at 22:59

typedef struct SqspStatus_s
{
  int         iTOW;                    //  GPS time of week [ms]
  int         time;                    //  UTC time; can't use time_t
  char        solType;                 //  GNSS Solution Type (SqspSolType_t)
  char        numSV;                   //  Number of satellites used in
                                       //    position solution
  char        battery;                 //  Current charge of battery, if any
                                       //    (or 0 if none)
  char        reserved;                //  Unused
  SqspRsp_t   rsp;
  char        reserved2;               //  Pad length to a multiple of 4 bytes
} SqspStatus_t;
#else
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
  SqspRsp_t    rsp;
  uint8_t      reserved2;               //  Pad length to a multiple of 4 bytes
} SqspStatus_t;
#endif

#ifdef SWIGJAVA
typedef struct SqspRelPos_s
{
  int      iTOW;                        //  GPS time of week [ms]
  double   posN;                        //  Converted from posN+posNHp [m]
  double   posE;                        //  Converted from posE+posEHp [m]
  double   posD;                        //  Converted from posD+posDHp [m]
} SqspRelPos_t;
#else
typedef struct SqspRelPos_s
{
  uint32_t iTOW;                        //  GPS time of week [ms]
  double   posN;                        //  Converted from posN+posNHp [m]
  double   posE;                        //  Converted from posE+posEHp [m]
  double   posD;                        //  Converted from posD+posDHp [m]
} SqspRelPos_t;
#endif

#ifdef SWIGJAVA
typedef struct SqspLla_s
{
  int      iTOW;                        //  GPS time of week [ms]
  int      reserved;                    //  Unused
  double   lon;                         //  Converted from lon + lonHp [m]
  double   lat;                         //  Converted from lat + latHp [m]
  double   height;                      //  Converted from height + heightHp [m]
  double   hMSL;                        //  Converted from hMSL + hMSLHp [m]
  double   hAcc;                        //  Converted from hAcc
  double   vAcc;                        //  Converted from vAcc
} SqspLla_t;
#else
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
#endif

//  Host MCU-related data types
typedef enum SqspHostMcuCommand_e
{
  SQSP_HOST_COMMAND_NONE = 0,
  SQSP_HOST_COMMAND_START_TRIPOD_AIDING = 1,
  SQSP_HOST_COMMAND_STOP_TRIPOD_AIDING = 2,
  SQSP_HOST_COMMAND_START_TRIPOD_AIDING_DELAYED = 3,
} ENUM_ATTR SqspHostMcuCommand_t;

//  Constants

//  Variables

//  Functions
#ifdef SWIGJAVA
FUNC_ATTR bool sqspLbModeCInit( SqspLbModeC_t *lbm, char fixedBaseEnable,
                                char autoSurveyEnable, char connected, char correctionOutput,
                                char correctionInput, char tripodCorrections, char validOrNotBusy,
                                char broadcastEnable );
FUNC_ATTR bool sqspLbModeInit(  SqspLbMode_t  *lbm, char fixedBaseEnable,
                                char autoSurveyEnable, char connected, char correctionOutput,
                                char correctionInput, char tripodCorrections, char validOrNotBusy,
                                char broadcastEnable );
#else
FUNC_ATTR bool sqspLbModeCInit( SqspLbModeC_t *lbm, uint8_t fixedBaseEnable,
                                uint8_t autoSurveyEnable, uint8_t connected, uint8_t correctionOutput,
                                uint8_t correctionInput, uint8_t tripodCorrections, uint8_t validOrNotBusy,
                                uint8_t broadcastEnable );
FUNC_ATTR bool sqspLbModeInit(  SqspLbMode_t  *lbm, uint8_t fixedBaseEnable,
                                uint8_t autoSurveyEnable, uint8_t connected, uint8_t correctionOutput,
                                uint8_t correctionInput, uint8_t tripodCorrections, uint8_t validOrNotBusy,
                                uint8_t broadcastEnable );
#endif
FUNC_ATTR bool sqspLbModeExpand(  SqspLbMode_t  *lbm,
  const SqspLbModeC_t *lbms );
FUNC_ATTR bool sqspLbModeCompact( SqspLbModeC_t *lbm,
  const SqspLbMode_t  *lbms );

FUNC_ATTR bool sqspLbConfigCInit( SqspLbConfigC_t *lbc, int32_t lon,
  int32_t lat, int32_t height, uint32_t hAcc, uint32_t vAcc, int8_t lonHp,
  int8_t latHp, int8_t heightHp, const SqspLbModeC_t *mode, uint32_t duration,
  int32_t hMSL, int8_t hMSLHp );
FUNC_ATTR bool sqspLbConfigInit(  SqspLbConfig_t  *lbc, double lon, double lat,
  double height, double hMSL, double hAcc, double vAcc, uint32_t duration,
  const SqspLbMode_t *mode );
FUNC_ATTR bool sqspLbConfigExpand(  SqspLbConfig_t  *lbc,
  const SqspLbConfigC_t *lbcs );
FUNC_ATTR bool sqspLbConfigCompact( SqspLbConfigC_t *lbc,
  const SqspLbConfig_t  *lbcs );

#if (defined(SWIGJAVA) || defined(__FFIGENDART__) ) // NOTE: __FFIGENDART__ is defined (or not) in the ffigen.yaml file under "compiler-opts:" as "'-D__FFIGEN__'"
FUNC_ATTR bool sqspRspCInit( SqspRspC_t *rsp,
	short mfgDataId,
	char batteryLevel,
	char systemPowerState,
	short runTimeRemaining,
	char satelliteCount,
	char aidingBins,
	char differential,
	char gpsFixOk,
	char ambiguity,
	char fix,
	char coprocOk,
	char surveyFailed,
	char surveyPositionValid,
	char surveyInProgress,
	char headingFlag,
	char posValid,
	char validTime,
	const SqspLbModeC_t *mode);
#else	
FUNC_ATTR bool sqspRspCInit( SqspRspC_t *rsp,
	uint16_t mfgDataId,
	uint8_t batteryLevel,
	SqspSystemPowerC_t systemPowerState,
	uint16_t runTimeRemaining,
	uint8_t satelliteCount,
	uint8_t aidingBins,
	uint8_t differential,
	uint8_t gpsFixOk,
	uint8_t ambiguity,
	uint8_t fix,
	uint8_t coprocOk,
	uint8_t surveyFailed,
	uint8_t surveyPositionValid,
	uint8_t surveyInProgress,
	uint8_t headingFlag,
	uint8_t posValid,
	uint8_t validTime,
	const SqspLbModeC_t *mode);
#endif

#if (defined(SWIGJAVA) || defined(__FFIGENDART__) ) // NOTE: __FFIGENDART__ is defined (or not) in the ffigen.yaml file under "compiler-opts:" as "'-D__FFIGEN__'"//No bitfields for SqspSystemPowerC_t Power just yet in JAVA
FUNC_ATTR bool sqspRspInit(  SqspRsp_t  *rsp,
	short mfgDataId,
	char batteryLevel,
	char Power,
	short runTimeRemaining,
	char satelliteCount,
	char aidingBins,
	char differential,
	char gpsFixOk,
	char ambiguity,
	char fix,
	char coprocOk,
	char surveyFailed,
	char surveyPositionValid,
	char surveyInProgress,
	char headingFlag,
	char posValid,
	char validTime,
	const SqspLbMode_t *mode);
#else
FUNC_ATTR bool sqspRspInit(  SqspRsp_t  *rsp,
	uint16_t mfgDataId,
	uint8_t batteryLevel,
	SqspSystemPowerC_t Power,
	uint16_t runTimeRemaining,
	uint8_t satelliteCount,
	uint8_t aidingBins,
	uint8_t differential,
	uint8_t gpsFixOk,
	uint8_t ambiguity,
	uint8_t fix,
	uint8_t coprocOk,
	uint8_t surveyFailed,
	uint8_t surveyPositionValid,
	uint8_t surveyInProgress,
	uint8_t headingFlag,
	uint8_t posValid,
	uint8_t validTime,
	const SqspLbMode_t *mode);
#endif  
	
FUNC_ATTR bool sqspRspExpand(  SqspRsp_t  *rsp, const SqspRspC_t *rsps );
FUNC_ATTR bool sqspRspCompact( SqspRspC_t *rsp, const SqspRsp_t  *rsps );

FUNC_ATTR bool sqspStatusCInit( SqspStatusC_t *s, uint32_t iTOW, uint16_t year,
  uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec,
  uint8_t solType, uint8_t numSV, uint8_t battery, const SqspRspC_t *rsp );
FUNC_ATTR bool sqspStatusInit(  SqspStatus_t  *s, uint32_t iTOW, uint32_t time,
  uint8_t solType, uint8_t numSV, uint8_t battery, const SqspRsp_t *rsp );
FUNC_ATTR bool sqspStatusExpand(  SqspStatus_t  *s, const SqspStatusC_t *ss );
FUNC_ATTR bool sqspStatusCompact( SqspStatusC_t *s, const SqspStatus_t  *ss );

FUNC_ATTR bool sqspRelPosCInit( SqspRelPosC_t *rp, uint32_t iTOW, int32_t posN,
  int32_t posE, int32_t posD, int8_t posHpN, int8_t posHpE, int8_t posHpD );
FUNC_ATTR bool sqspRelPosInit(  SqspRelPos_t  *rp, uint32_t iTOW, double posN,
  double posE, double posD );
FUNC_ATTR bool sqspRelPosExpand(  SqspRelPos_t  *rp, const SqspRelPosC_t *rps );
FUNC_ATTR bool sqspRelPosCompact( SqspRelPosC_t *rp, const SqspRelPos_t  *rps );

FUNC_ATTR bool sqspLlaCInit( SqspLlaC_t *lla, uint32_t iTOW, int32_t lon,
  int32_t lat, int32_t height, int8_t lonHp, int8_t latHp, int8_t heightHp,
  int8_t hMSLHp, uint32_t hAcc, uint32_t vAcc, int32_t hMSL );
FUNC_ATTR bool sqspLlaInit(  SqspLla_t  *lla, uint32_t iTOW, double lon,
  double lat, double height, double hMSL, double hAcc, double vAcc );
FUNC_ATTR bool sqspLlaExpand(  SqspLla_t  *lla, const SqspLlaC_t *llas );
FUNC_ATTR bool sqspLlaCompact( SqspLlaC_t *lla, const SqspLla_t  *llas );

#ifdef  SWIGJAVA
FUNC_ATTR const char *sqspSolutionTypeLabel( char index );
#else
FUNC_ATTR const uint8_t *sqspSolutionTypeLabel( uint8_t index );
#endif

#ifdef    __cplusplus
}
#endif  //__cplusplus

#endif  //__SQSPTYPES_H__
