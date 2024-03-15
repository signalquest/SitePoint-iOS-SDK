/*******************************************************************************
**  Copyright 2023 - SignalQuest, Inc.    PROPRIETARY & CONFIDENTIAL
********************************************************************************
**
**  This file is confidential and proprietary property of SignalQuest, Inc.
**  All rights are reserved. This file may not be used, reproduced or
**  distributed by any unauthorized party.  Unauthorized copies of this file
**  must be deleted or destroyed immediately.
**
********************************************************************************
**
**  File:     sqtpStatus.h
**  Purpose:  SignalQuest Status type declarations
**
*******************************************************************************/

#ifndef   __SQTPSTATUS_H__
#define   __SQTPSTATUS_H__

#ifdef    __cplusplus
extern "C" {
#endif  //__cplusplus

//  Includes

//  Defines

//  Data types
typedef enum SqtpStatus_e
{
  SQTP_STATUS_SUCCESS             =  0, //  General success
  SQTP_STATUS_FAILED              = -1, //  General failure
  SQTP_STATUS_FRAME_END           = -2, //  End of frame reached 
                                        //  Frame is full
  SQTP_STATUS_FRAME_BAD_FORMAT    = -3, //  Frame header error
  SQTP_STATUS_FRAME_BAD_LENGTH    = -4, //  Invalid frame length
  SQTP_STATUS_FRAME_BAD_CHECK     = -5, //  Frame check value mismatch
  SQTP_STATUS_SUBFRAME_BAD_FORMAT = -6, //  Subframe header error
  SQTP_STATUS_SUBFRAME_BAD_ID     = -7, //  Invalid subframe ID
  SQTP_STATUS_SUBFRAME_BAD_LENGTH = -8, //  Invalid subframe length
                                        //  Subframe did not fit in frame
  SQTP_STATUS_SUBFRAME_BAD_CHECK  = -9, //  Subframe check value mismatch
} __attribute__((enum_extensibility(closed))) SqtpStatus_t;

//  Constants

//  Variables

//  Functions

#ifdef    __cplusplus
}
#endif  //__cplusplus

#endif  //__SQTPSTATUS_H__
