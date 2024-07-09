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
**  File:     sqspTypeWrap.h
**  Purpose:  SignalQuest SitePoint Data Types Accessor wrapping functions
**
*******************************************************************************/

#ifndef   __SQSPTYPEWRAP_H__
#define   __SQSPTYPEWRAP_H__

#ifdef    __cplusplus
extern "C" {
#endif  //__cplusplus

//  Includes
#include <stdint.h>

#include "os_target.h"

#include "sqspTypes.h"

//  Defines

//  Data types
#ifdef SWIGJAVA
typedef struct SqspSolTypeLabel_s
{
    char string[16];                   //  For returning fixed-size labels
} SqspSolTypeLabel_t;
#else
typedef struct SqspSolTypeLabel_s
{
  uint8_t string[16];                   //  For returning fixed-size labels
} SqspSolTypeLabel_t;
#endif

//  Constants

//  Variables

//  Functions

//  Shorthand suffix descriptions:
//    "C" -         Compacted structure using bitfields
//    Cast -        Typecasts the provided pointer to the named type.
//    Copy -        Copies the contents from the provided pointer to an object
//                  of the named type. This object is returned via the stack and
//                  not dynamically allocated.
//    ConvertCast - Typecasts the data at the provided pointer to the "C" or
//                  non-C type then converts it to a new object of the opposite
//                  type. This object is returned via the stack and not
//                  dynamically allocated.
//    ConvertCopy - Converts the provided object to an object of the opposite
//                  type. This object is returned via the stack and not
//                  dynamically allocated.
//    Create      - Creates a stack-returned object of the desired type with the
//                  given initial values for its fields.

FUNC_ATTR const SqspLbModeC_t   *sqspLbModeCCast(           const uint8_t *p );
FUNC_ATTR       SqspLbModeC_t    sqspLbModeCCopy(           const uint8_t *p );
FUNC_ATTR       SqspLbModeC_t    sqspLbModeCConvertCast(    const uint8_t *p );
FUNC_ATTR       SqspLbModeC_t    sqspLbModeCConvertCopy(    SqspLbMode_t lbms );
#ifdef SWIGJAVA
FUNC_ATTR       SqspLbModeC_t    sqspLbModeCCreate(         char fixedBaseEnable,
                                                            char autoSurveyEnable,
                                                            char connected,
                                                            char correctionOutput,
                                                            char correctionInput,
                                                            char tripodCorrections,
                                                            char validOrNotBusy,
                                                            char broadcastEnable );
#else
FUNC_ATTR       SqspLbModeC_t    sqspLbModeCCreate(         uint8_t fixedBaseEnable,
                                                            uint8_t autoSurveyEnable,
                                                            uint8_t connected,
                                                            uint8_t correctionOutput,
                                                            uint8_t correctionInput,
                                                            uint8_t tripodCorrections,
                                                            uint8_t validOrNotBusy,
                                                            uint8_t broadcastEnable );

#endif
#ifdef SWIGJAVA
FUNC_ATTR const SqspLbConfigC_t *sqspLbConfigCCast(         const uint8_t *JavaByteArray );
#else
FUNC_ATTR const SqspLbConfigC_t *sqspLbConfigCCast(         const uint8_t *p );
#endif
FUNC_ATTR       SqspLbConfigC_t  sqspLbConfigCCopy(         const uint8_t *p );
FUNC_ATTR       SqspLbConfigC_t  sqspLbConfigCConvertCast(  const uint8_t *p );
FUNC_ATTR       SqspLbConfigC_t  sqspLbConfigCConvertCopy(  SqspLbConfig_t lbcs );
FUNC_ATTR       SqspLbConfigC_t  sqspLbConfigCCreate(       int32_t       lon,
                                                            int32_t       lat,
                                                            int32_t       height,
                                                            uint32_t      hAcc,
                                                            uint32_t      vAcc,
                                                            int8_t        lonHp,
                                                            int8_t        latHp,
                                                            int8_t        heightHp,
                                                            SqspLbModeC_t mode,
                                                            uint32_t      duration,
                                                            int32_t       hMSL,
                                                            int8_t        hMSLHp );

#ifdef SWIGJAVA
FUNC_ATTR const SqspRspC_t      *sqspRspCCast(              const uint8_t *JavaByteArray );
#else
FUNC_ATTR const SqspRspC_t      *sqspRspCCast(              const uint8_t *p );
#endif
#ifdef SWIGJAVA
FUNC_ATTR       SqspRspC_t       sqspRspCCopy(              const uint8_t *JavaByteArray );
#else
FUNC_ATTR       SqspRspC_t       sqspRspCCopy(              const uint8_t *p );
#endif
FUNC_ATTR       SqspRspC_t       sqspRspCConvertCast(       const uint8_t *p );
FUNC_ATTR       SqspRspC_t       sqspRspCConvertCopy(       SqspRsp_t rsps );
	
#if (defined(SWIGJAVA) || defined(__FFIGEN__) ) // NOTE: __FFIGEN__ is defined (or not) in the ffigen.yaml file under "compiler-opts:" as "'-D__FFIGEN__'"
FUNC_ATTR       SqspRspC_t       sqspRspCCreate(            uint16_t mfgDataId,
                                                            uint8_t  batteryLevel,
                                                            uint8_t  systemPowerState,
                                                            uint16_t runTimeRemaining,
                                                            uint8_t  satelliteCount,
                                                            uint8_t  aidingBins,
                                                            uint8_t  differential,
                                                            uint8_t  gpsFixOk,
                                                            uint8_t  ambiguity,
                                                            uint8_t  fix,
                                                            uint8_t  coprocOk,
                                                            uint8_t  surveyFailed,
                                                            uint8_t  surveyPositionValid,
                                                            uint8_t  surveyInProgress,
                                                            uint8_t  headingFlag,
                                                            uint8_t  posValid,
                                                            uint8_t  validTime,
                                                            SqspLbModeC_t mode);
#else // DEBUG
//defined(POWER_STATE_UPGRADE) //TODO: Made permanent in SitePoint/NPG, adjust dependent projects accordingly.
FUNC_ATTR       SqspRspC_t       sqspRspCCreate(            uint16_t mfgDataId,
                                                            uint8_t  batteryLevel,
                                                            SqspSystemPowerC_t  Power,
                                                            uint16_t runTimeRemaining,
                                                            uint8_t  satelliteCount,
                                                            uint8_t  aidingBins,
                                                            uint8_t  differential,
                                                            uint8_t  gpsFixOk,
                                                            uint8_t  ambiguity,
                                                            uint8_t  fix,
                                                            uint8_t  coprocOk,
                                                            uint8_t  surveyFailed,
                                                            uint8_t  surveyPositionValid,
                                                            uint8_t  surveyInProgress,
                                                            uint8_t  headingFlag,
                                                            uint8_t  posValid,
                                                            uint8_t  validTime,
                                                            SqspLbModeC_t mode);
#endif // DEBUG
	
FUNC_ATTR const SqspStatusC_t   *sqspStatusCCast(           const uint8_t *p );
FUNC_ATTR       SqspStatusC_t    sqspStatusCCopy(           const uint8_t *p );
FUNC_ATTR       SqspStatusC_t    sqspStatusCConvertCast(    const uint8_t *p );
FUNC_ATTR       SqspStatusC_t    sqspStatusCConvertCopy(    SqspStatus_t ss );

#ifdef SWIGJAVA
FUNC_ATTR       SqspStatusC_t    sqspStatusCCreate(         int     iTOW,
                                                            short   year,
                                                            char    month,
                                                            char    day,
                                                            char    hour,
                                                            char    min,
                                                            char    sec,
                                                            char    solType,
                                                            char    numSV,
                                                            char    battery,
                                                            SqspRspC_t rsp );
#else
FUNC_ATTR       SqspStatusC_t    sqspStatusCCreate(         uint32_t   iTOW,
                                                            uint16_t   year,
                                                            uint8_t    month,
                                                            uint8_t    day,
                                                            uint8_t    hour,
                                                            uint8_t    min,
                                                            uint8_t    sec,
                                                            uint8_t    solType,
                                                            uint8_t    numSV,
                                                            uint8_t    battery,
                                                            SqspRspC_t rsp );
#endif

FUNC_ATTR const SqspRelPosC_t   *sqspRelPosCCast(           const uint8_t *p );
FUNC_ATTR       SqspRelPosC_t    sqspRelPosCCopy(           const uint8_t *p );
FUNC_ATTR       SqspRelPosC_t    sqspRelPosCConvertCast(    const uint8_t *p );
FUNC_ATTR       SqspRelPosC_t    sqspRelPosCConvertCopy(    SqspRelPos_t rps );
FUNC_ATTR       SqspRelPosC_t    sqspRelPosCCreate(         uint32_t iTOW,
                                                            int32_t  posN,
                                                            int32_t  posE,
                                                            int32_t  posD,
                                                            int8_t   posHpN,
                                                            int8_t   posHpE,
                                                            int8_t   posHpD );

FUNC_ATTR const SqspLlaC_t      *sqspLlaCCast(              const uint8_t *p );
FUNC_ATTR       SqspLlaC_t       sqspLlaCCopy(              const uint8_t *p );
FUNC_ATTR       SqspLlaC_t       sqspLlaCConvertCast(       const uint8_t *p );
FUNC_ATTR       SqspLlaC_t       sqspLlaCConvertCopy(       SqspLla_t llas );
FUNC_ATTR       SqspLlaC_t       sqspLlaCCreate(            uint32_t iTOW,
                                                            int32_t  lon,
                                                            int32_t  lat,
                                                            int32_t  height,
                                                            int8_t   lonHp,
                                                            int8_t   latHp,
                                                            int8_t   heightHp,
                                                            int8_t   hMSLHp,
                                                            uint32_t hAcc,
                                                            uint32_t vAcc,
                                                            int32_t  hMSL );

FUNC_ATTR const SqspLbMode_t    *sqspLbModeCast(            const uint8_t *p );
FUNC_ATTR       SqspLbMode_t     sqspLbModeCopy(            const uint8_t *p );
FUNC_ATTR       SqspLbMode_t     sqspLbModeConvertCast(     const uint8_t *p );
FUNC_ATTR       SqspLbMode_t     sqspLbModeConvertCopy(     SqspLbModeC_t lbms );
#ifdef SWIGJAVA
FUNC_ATTR       SqspLbMode_t     sqspLbModeCreate(          char fixedBaseEnable,
                                                            char autoSurveyEnable,
                                                            char connected,
                                                            char correctionOutput,
                                                            char correctionInput,
                                                            char tripodCorrections,
                                                            char validOrNotBusy,
                                                            char broadcastEnable );
#else
FUNC_ATTR       SqspLbMode_t     sqspLbModeCreate(          uint8_t fixedBaseEnable,
                                                            uint8_t autoSurveyEnable,
                                                            uint8_t connected,
                                                            uint8_t correctionOutput,
                                                            uint8_t correctionInput,
                                                            uint8_t tripodCorrections,
                                                            uint8_t validOrNotBusy,
                                                            uint8_t broadcastEnable );
#endif

FUNC_ATTR const SqspLbConfig_t  *sqspLbConfigCast(          const uint8_t *p );
#ifdef SWIGJAVA
FUNC_ATTR       SqspLbConfig_t   sqspLbConfigCopy(          const uint8_t *JavaByteArray );
#else
FUNC_ATTR       SqspLbConfig_t   sqspLbConfigCopy(          const uint8_t *p );
#endif
FUNC_ATTR       SqspLbConfig_t   sqspLbConfigConvertCast(   const uint8_t *p );
FUNC_ATTR       SqspLbConfig_t   sqspLbConfigConvertCopy(   SqspLbConfigC_t lbcs );
#ifdef SWIGJAVA
FUNC_ATTR       SqspLbConfig_t   sqspLbConfigCreate(        double       lon,
                                                            double       lat,
                                                            double       height,
                                                            double       hMSL,
                                                            double       hAcc,
                                                            double       vAcc,
                                                            int          duration,
                                                            SqspLbMode_t mode );
#else
FUNC_ATTR       SqspLbConfig_t   sqspLbConfigCreate(        double       lon,
                                                            double       lat,
                                                            double       height,
                                                            double       hMSL,
                                                            double       hAcc,
                                                            double       vAcc,
                                                            uint32_t     duration,
                                                            SqspLbMode_t mode );
#endif

#ifdef SWIGJAVA
FUNC_ATTR const SqspRsp_t       *sqspRspCast(               const uint8_t *JavaByteArray);
#else
FUNC_ATTR const SqspRsp_t       *sqspRspCast(               const uint8_t *p );
#endif
FUNC_ATTR       SqspRsp_t        sqspRspCopy(               const uint8_t *p );
FUNC_ATTR       SqspRsp_t        sqspRspConvertCast(        const uint8_t *p );
FUNC_ATTR       SqspRsp_t        sqspRspConvertCopy(        SqspRspC_t rsps );

#ifdef SWIGJAVA
#if 001
//No bitfields for Power just yet in JAVA
FUNC_ATTR       SqspRsp_t        sqspRspCreate(             short mfgDataId,
                                                            char  batteryLevel,
                                                            char  Power,
                                                            short runTimeRemaining,
                                                            char  satelliteCount,
                                                            char  aidingBins,
                                                            char  differential,
                                                            char  gpsFixOk,
                                                            char  ambiguity,
                                                            char  fix,
                                                            char  coprocOk,
                                                            char  surveyFailed,
                                                            char  surveyPositionValid,
                                                            char  surveyInProgress,
                                                            char  headingFlag,
                                                            char  posValid,
                                                            char  validTime,
                                                            SqspLbMode_t mode );
#else
FUNC_ATTR       SqspRsp_t        sqspRspCreate(             short mfgDataId,
                                                            char  batteryLevel,
                                                            SqspSystemPowerC_t  Power,
                                                            short runTimeRemaining,
                                                            char  satelliteCount,
                                                            char  aidingBins,
                                                            char  differential,
                                                            char  gpsFixOk,
                                                            char  ambiguity,
                                                            char  fix,
                                                            char  coprocOk,
                                                            char  surveyFailed,
                                                            char  surveyPositionValid,
                                                            char  surveyInProgress,
                                                            char  headingFlag,
                                                            char  posValid,
                                                            char  validTime,
                                                            SqspLbMode_t mode );
#endif
#else
FUNC_ATTR       SqspRsp_t        sqspRspCreate(             uint16_t mfgDataId,
                                                            uint8_t  batteryLevel,
                                                            SqspSystemPowerC_t  Power,
                                                            uint16_t runTimeRemaining,
                                                            uint8_t  satelliteCount,
                                                            uint8_t  aidingBins,
                                                            uint8_t  differential,
                                                            uint8_t  gpsFixOk,
                                                            uint8_t  ambiguity,
                                                            uint8_t  fix,
                                                            uint8_t  coprocOk,
                                                            uint8_t  surveyFailed,
                                                            uint8_t  surveyPositionValid,
                                                            uint8_t  surveyInProgress,
                                                            uint8_t  headingFlag,
                                                            uint8_t  posValid,
                                                            uint8_t  validTime,
                                                            SqspLbMode_t mode );
#endif

FUNC_ATTR const SqspStatus_t    *sqspStatusCast(            const uint8_t *p );
#ifdef SWIGJAVA
FUNC_ATTR       SqspStatus_t     sqspStatusCopy(            const uint8_t *JavaByteArray );
#else
FUNC_ATTR       SqspStatus_t     sqspStatusCopy(            const uint8_t *p );
#endif
FUNC_ATTR       SqspStatus_t     sqspStatusConvertCast(     const uint8_t *p );
FUNC_ATTR       SqspStatus_t     sqspStatusConvertCopy(     SqspStatusC_t ss );
FUNC_ATTR       SqspStatus_t     sqspStatusCreate(          uint32_t  iTOW,
                                                            uint32_t  time,
                                                            uint8_t   solType,
                                                            uint8_t   numSV,
                                                            uint8_t   battery,
                                                            SqspRsp_t rsp );

FUNC_ATTR const SqspRelPos_t    *sqspRelPosCast(            const uint8_t *p );
FUNC_ATTR       SqspRelPos_t     sqspRelPosCopy(            const uint8_t *p );
FUNC_ATTR       SqspRelPos_t     sqspRelPosConvertCast(     const uint8_t *p );
FUNC_ATTR       SqspRelPos_t     sqspRelPosConvertCopy(     SqspRelPosC_t rps );
FUNC_ATTR       SqspRelPos_t     sqspRelPosCreate(          uint32_t iTOW,
                                                            double   posN,
                                                            double   posE,
                                                            double   posD );

FUNC_ATTR const SqspLla_t       *sqspLlaCast(               const uint8_t *p );
#ifdef SWIGJAVA
FUNC_ATTR       SqspLla_t        sqspLlaCopy(               const uint8_t *JavaByteArray );
#else
FUNC_ATTR       SqspLla_t        sqspLlaCopy(               const uint8_t *p );
#endif


FUNC_ATTR       SqspLla_t        sqspLlaConvertCast(        const uint8_t *p );
FUNC_ATTR       SqspLla_t        sqspLlaConvertCopy(        SqspLlaC_t llas );

#ifdef SWIGJAVA
FUNC_ATTR       SqspLla_t        sqspLlaCreate(             int      iTOW,
                                                            double   lon,
                                                            double   lat,
                                                            double   height,
                                                            double   hMSL,
                                                            double   hAcc,
                                                            double   vAcc );
#else
FUNC_ATTR       SqspLla_t        sqspLlaCreate(             uint32_t iTOW,
                                                            double   lon,
                                                            double   lat,
                                                            double   height,
                                                            double   hMSL,
                                                            double   hAcc,
                                                            double   vAcc );
#endif

#ifdef SWIGJAVA
FUNC_ATTR SqspSolTypeLabel_t sqspSolutionTypeLabelCopy(     char index );
#else
FUNC_ATTR SqspSolTypeLabel_t sqspSolutionTypeLabelCopy(     uint8_t index );
#endif

#ifdef SWIGJAVA
// The following functions are primarily intended for SWIGJAVA interfaces but may be useful 
// for other language FFI interfaces also.
// SWIG JAVA Helpers:

int SqspSqspLbModeC_tByteArray(uint8_t *JavaByteArray, int Length,  SqspLbModeC_t *Mode    );
int SqspLbMode_tByteArray     (uint8_t *JavaByteArray, int Length,  SqspLbMode_t *Mode     );
int SqspRspC_tByteArray       (uint8_t *JavaByteArray, int Length,  SqspRspC_t *Response   );
int SqspRsp_tByteArray        (uint8_t *JavaByteArray, int Length,  SqspRsp_t *Response    );
int SqspStatus_tByteArray     (uint8_t *JavaByteArray, int Length,  SqspStatus_t *Status   );
int SqspStatusC_tByteArray    (uint8_t *JavaByteArray, int Length,  SqspStatusC_t *Status  );
int SqspLlaC_tByteArray       (uint8_t *JavaByteArray, int Length,  SqspLlaC_t *LLA        );
int SqspLla_tByteArray        (uint8_t *JavaByteArray, int Length,  SqspLla_t *LLA         );
int SqspLbConfig_tByteArray   (uint8_t *JavaByteArray, int Length,  SqspLbConfig_t *Config );
int SqspLbConfigC_tByteArray  (uint8_t *JavaByteArray, int Length,  SqspLbConfigC_t *Config);

int SqspLbModeC_tSize(void);
int SqspLbMode_tSize(void);
int SqspRspC_tSize(void);
int SqspRsp_tSize(void);
int SqspStatus_tSize(void);
int SqspStatusC_tSize(void);
int SqspLlaC_tSize(void);
int SqspLla_tSize(void);
int SqspLbConfig_tSize(void);
int SqspLbConfigC_tSize(void);
int SqspLbModeC_tSize(void);
int SqspLbMode_tSize(void);
int SqspRspC_tSize(void);
int SqspRsp_tSize(void);
int SqspStatus_tSize(void);
int SqspStatusC_tSize(void);

#endif //SWIGJAVA

#ifdef    __cplusplus
}
#endif  //__cplusplus

#endif  //__SQCOP_SFSITEPOINT_H__
