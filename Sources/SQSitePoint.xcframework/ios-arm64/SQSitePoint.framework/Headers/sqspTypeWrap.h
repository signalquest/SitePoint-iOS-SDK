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

#include "sqspTypes.h"

//  Defines

//  Data types
typedef struct SqspSolTypeLabel_s
{
  uint8_t string[16];                   //  For returning fixed-size labels
} SqspSolTypeLabel_t;

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

const SqspLbModeC_t   *sqspLbModeCCast(          const uint8_t *p );
      SqspLbModeC_t    sqspLbModeCCopy(          const uint8_t *p );
      SqspLbModeC_t    sqspLbModeCConvertCast(   const uint8_t *p );
      SqspLbModeC_t    sqspLbModeCConvertCopy(   SqspLbMode_t lbms );

const SqspLbConfigC_t *sqspLbConfigCCast(        const uint8_t *p );
      SqspLbConfigC_t  sqspLbConfigCCopy(        const uint8_t *p );
      SqspLbConfigC_t  sqspLbConfigCConvertCast( const uint8_t *p );
      SqspLbConfigC_t  sqspLbConfigCConvertCopy( SqspLbConfig_t lbcs );

const SqspRspC_t      *sqspRspCCast(             const uint8_t *p );
      SqspRspC_t       sqspRspCCopy(             const uint8_t *p );
      SqspRspC_t       sqspRspCConvertCast(      const uint8_t *p );
      SqspRspC_t       sqspRspCConvertCopy(      SqspRsp_t rsps );

const SqspStatusC_t   *sqspStatusCCast(          const uint8_t *p );
      SqspStatusC_t    sqspStatusCCopy(          const uint8_t *p );
      SqspStatusC_t    sqspStatusCConvertCast(   const uint8_t *p );
      SqspStatusC_t    sqspStatusCConvertCopy(   SqspStatus_t ss );

const SqspRelPosC_t   *sqspRelPosCCast(          const uint8_t *p );
      SqspRelPosC_t    sqspRelPosCCopy(          const uint8_t *p );
      SqspRelPosC_t    sqspRelPosCConvertCast(   const uint8_t *p );
      SqspRelPosC_t    sqspRelPosCConvertCopy(   SqspRelPos_t rps );

const SqspLlaC_t      *sqspLlaCCast(             const uint8_t *p );
      SqspLlaC_t       sqspLlaCCopy(             const uint8_t *p );
      SqspLlaC_t       sqspLlaCConvertCast(      const uint8_t *p );
      SqspLlaC_t       sqspLlaCConvertCopy(      SqspLla_t llas );

const SqspLbMode_t    *sqspLbModeCast(           const uint8_t *p );
      SqspLbMode_t     sqspLbModeCopy(           const uint8_t *p );
      SqspLbMode_t     sqspLbModeConvertCast(    const uint8_t *p );
      SqspLbMode_t     sqspLbModeConvertCopy(    SqspLbModeC_t lbms );

const SqspLbConfig_t  *sqspLbConfigCast(         const uint8_t *p );
      SqspLbConfig_t   sqspLbConfigCopy(         const uint8_t *p );
      SqspLbConfig_t   sqspLbConfigConvertCast(  const uint8_t *p );
      SqspLbConfig_t   sqspLbConfigConvertCopy(  SqspLbConfigC_t lbcs );

const SqspRsp_t       *sqspRspCast(              const uint8_t *p );
      SqspRsp_t        sqspRspCopy(              const uint8_t *p );
      SqspRsp_t        sqspRspConvertCast(       const uint8_t *p );
      SqspRsp_t        sqspRspConvertCopy(       SqspRspC_t rsps );

const SqspStatus_t    *sqspStatusCast(           const uint8_t *p );
      SqspStatus_t     sqspStatusCopy(           const uint8_t *p );
      SqspStatus_t     sqspStatusConvertCast(    const uint8_t *p );
      SqspStatus_t     sqspStatusConvertCopy(    SqspStatusC_t ss );

const SqspRelPos_t    *sqspRelPosCast(           const uint8_t *p );
      SqspRelPos_t     sqspRelPosCopy(           const uint8_t *p );
      SqspRelPos_t     sqspRelPosConvertCast(    const uint8_t *p );
      SqspRelPos_t     sqspRelPosConvertCopy(    SqspRelPosC_t rps );

const SqspLla_t       *sqspLlaCast(              const uint8_t *p );
      SqspLla_t        sqspLlaCopy(              const uint8_t *p );
      SqspLla_t        sqspLlaConvertCast(       const uint8_t *p );
      SqspLla_t        sqspLlaConvertCopy(       SqspLlaC_t llas );

SqspSolTypeLabel_t sqspSolutionTypeLabelCopy( uint8_t index );

#ifdef    __cplusplus
}
#endif  //__cplusplus

#endif  //__SQCOP_SFSITEPOINT_H__
