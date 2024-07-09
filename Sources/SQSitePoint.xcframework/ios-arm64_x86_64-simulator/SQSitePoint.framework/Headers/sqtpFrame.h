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
**  File:     sqtpFrame.h
**  Purpose:  SignalQuest Transport Protocol frame handler declarations
**
*******************************************************************************/

#ifndef   __SQTPFRAME_H__
#define   __SQTPFRAME_H__

#ifdef    __cplusplus
extern "C" {
#endif  //__cplusplus

//  Includes
#include <stddef.h>
#include <stdint.h>

#include "os_target.h"

#include "sqtpStatus.h"

#include "sqtpSubframeIDs.h"

//  Defines

//  Data types
typedef struct SqtpSubframe_s
{
  const uint8_t    *payload;            //  Subframe payload pointer
  SqtpSubframeId_t id;                  //  Subframe ID
  size_t           length;              //  Subframe payload length
} SqtpSubframe_t;

#ifdef notSWIGJAVA
typedef struct SqtpFrameReader_s
{
  const uint8_t    *JavaByteArray;      //  Frame buffer pointer
  size_t           length;              //  Frame's discerned length
  size_t           index;               //  Read index into frame
  SqtpStatus_t     status;              //  Current frame parsing status
  SqtpSubframe_t   subframe;            //  Current subframe information
} SqtpFrameReader_t;
#else
typedef struct SqtpFrameReader_s
{
  const uint8_t    *frame;              //  Frame buffer pointer
  size_t           length;              //  Frame's discerned length
  size_t           index;               //  Read index into frame
  SqtpStatus_t     status;              //  Current frame parsing status
  SqtpSubframe_t   subframe;            //  Current subframe information
} SqtpFrameReader_t;
#endif

#ifdef notSWIGJAVA
typedef struct SqtpFrameWriter_s
{
    //JLM: This doesn't work 'cause it causes some of the JNI to break, and it can't figure out how to return a byte[] it doesn't know the length of...sigh.
  uint8_t          *JavaByteArray;      //  Frame buffer pointer
  size_t           length;              //  Maximum frame length
  size_t           index;               //  Write index into frame
  SqtpStatus_t     status;              //  Current status
} SqtpFrameWriter_t;
#else
typedef struct SqtpFrameWriter_s
{
  uint8_t          *frame;              //  Frame buffer pointer
  size_t           length;              //  Maximum frame length
  size_t           index;               //  Write index into frame
  SqtpStatus_t     status;              //  Current status
} SqtpFrameWriter_t;
#endif

//  Constants

//  Variables

//  Functions

//  Function: sqtpFrameGetLength
//  Purpose:  Returns the determined length of the frame given. If the frame
//              format is determined to be invalid a length of 0 will be
//              returned. Checking whether the reported length is over-long is
//              upon the caller to perform.
//  Params:   buf: Pointer to the frame buffer.
//  Returns:  See Purpose.
FUNC_ATTR size_t sqtpFrameGetLength( const uint8_t *buf );

//  Function: sqtpFrameReaderInit
//  Purpose:  Initializes a SqtpFrameReader_t object given a buffer of frame
//              data to be parsed. The frame and first subframe are verified.
//  Params:   fr: Pointer to SqtpFrameReader_t object to initialize.
//            buf: Pointer to raw frame buffer to parse.
//            sz: Known length of the frame buffer.
//  Returns:  Object at fr modified; returned value is same as fr->status.
//  Note:     It is expected that the caller will make no changes to the
//              contents of the SqtpFrameReader_t object once initialized.
#ifdef SWIGJAVA
FUNC_ATTR SqtpStatus_t sqtpFrameReaderInit( SqtpFrameReader_t *fr, const uint8_t *JavaByteArray, size_t sz );
#else
FUNC_ATTR SqtpStatus_t sqtpFrameReaderInit( SqtpFrameReader_t *fr, const uint8_t *buf, size_t sz );
#endif

//  Function: sqtpFrameReaderReset
//  Purpose:  Resets the read position of the SqtpFrameReader_t object to the
//              first subframe. First subframe is reverified.
//  Params:   fr: Pointer to SqtpFrameReader_t object to reset.
//  Returns:  Object at fr modified; returned value is same as fr->status.
FUNC_ATTR SqtpStatus_t sqtpFrameReaderReset( SqtpFrameReader_t *fr );

//  Function: sqtpFrameReaderNext
//  Purpose:  Moves the read position ahead within the frame to the next
//              subframe. Subframe is then verified. If no further subframes are
//              available, then SQTP_STATUS_FRAME_END is returned.
//  Params:   fr: Pointer to SqtpFrameReader_t object to move ahead.
//  Returns:  Object at fr modified; returned value is same as fr->status.
FUNC_ATTR SqtpStatus_t sqtpFrameReaderNext( SqtpFrameReader_t *fr );

//  Function: sqtpFrameWriterInit
//  Purpose:  Initializes a SqtpFrameWriter_t object given a writable buffer.
//  Params:   fw: Pointer to SqtpFrameWriter_t object to initialize.
//            buf: Pointer to writable buffer space to use.
//            sz: Maximum allowable size of the frame buffer.
//  Returns:  Object at fr modified; returned value is same as fr->status.
//  Note:     It is expected that the caller will make no changes to the
//              contents of the SqtpFrameWriter_t object once initialized.
#ifdef SWIGJAVA
FUNC_ATTR SqtpStatus_t sqtpFrameWriterInit( SqtpFrameWriter_t *fw, uint8_t *JavaByteArray, size_t sz );
#else
FUNC_ATTR SqtpStatus_t sqtpFrameWriterInit( SqtpFrameWriter_t *fw, uint8_t *buf, size_t sz );
#endif
//  Function: sqtpFrameWriterReset
//  Purpose:  Resets the write position of a SqtpFrameWriter_t object. This
//              would be used when frame buffers should be reused.
//  Params:   fw: Pointer to SqtpFrameWriter_t object to reset.
//  Returns:  Object at fr modified; returned value is same as fr->status.
FUNC_ATTR SqtpStatus_t sqtpFrameWriterReset( SqtpFrameWriter_t * fw );

//  Function: sqtpFrameWriterWriteDirect
//  Purpose:  Attempts to write a subframe to a frame. If a subframe will not
//              fit, SQTP_STATUS_SUBFRAME_BAD_LENGTH is returned.
//  Params:   fw: Pointer to SqtpFrameWriter_t object to update.
//            id: Subframe ID.
//            payload: Pointer to subframe contents.
//            sz: Size of the payload.
//  Returns:  Object at fr modified; returned value is same as fr->status.
#ifdef SWIGJAVA
FUNC_ATTR SqtpStatus_t sqtpFrameWriterWriteDirect( SqtpFrameWriter_t *fw, SqtpSubframeId_t id, const uint8_t *JavaByteArray, size_t sz );
#else
FUNC_ATTR SqtpStatus_t sqtpFrameWriterWriteDirect( SqtpFrameWriter_t *fw, SqtpSubframeId_t id, const uint8_t *payload, size_t sz );
#endif

//  Function: sqtpFrameWriterWriteSubframe
//  Purpose:  Attempts to write a subframe to a frame. If a subframe will not
//              fit, SQTP_STATUS_SUBFRAME_BAD_LENGTH is returned.
//  Params:   fw: Pointer to SqtpFrameWriter_t object to update.
//            sf: Pointer to SqtpSubframe_t object to write.
//  Returns:  Object at fr modified; returned value is same as fr->status.
FUNC_ATTR SqtpStatus_t sqtpFrameWriterWriteSubframe( SqtpFrameWriter_t *fw,
  const SqtpSubframe_t *sf );

//  Function: sqtpFrameWriterFinalize
//  Purpose:  Finalizes/closes the given frame so that it is now ready to be
//            transferred.
//  Params:   fw: Pointer to SqtpFrameWriter_t object to close.
//  Returns:  Object at fr modified; returned value is same as fr->status.
//            SQTP_STATUS_FRAME_END if frame has been appropriately finalized;
//              fr->index will have the length of the finalized frame.
FUNC_ATTR SqtpStatus_t sqtpFrameWriterFinalize( SqtpFrameWriter_t *fw );

//  The below functions work much the same as the above, but return structures
//  directly instead of working on structures at a pointer.
#ifdef SWIGJAVA
FUNC_ATTR SqtpFrameReader_t sqtpFrameReaderInitStruct( const uint8_t *JavaByteArray, size_t sz );
#else
FUNC_ATTR SqtpFrameReader_t sqtpFrameReaderInitStruct( const uint8_t *buf, size_t sz );
#endif

FUNC_ATTR SqtpFrameReader_t sqtpFrameReaderResetStruct( SqtpFrameReader_t fr );
FUNC_ATTR SqtpFrameReader_t sqtpFrameReaderNextStruct( SqtpFrameReader_t fr );

#ifdef SWIGJAVA
FUNC_ATTR SqtpFrameWriter_t sqtpFrameWriterInitStruct( uint8_t *JavaByteArray, size_t sz );
#else
FUNC_ATTR SqtpFrameWriter_t sqtpFrameWriterInitStruct( uint8_t *buf, size_t sz );
#endif

//FUNC_ATTR SqtpFrameWriter_t sqtpFrameWriterResetStruct( SqtpFrameWriter_t fw ); //TODO: Need to look into this.

#ifdef SWIGJAVA
FUNC_ATTR SqtpFrameWriter_t sqtpFrameWriterWriteStructDirect(SqtpFrameWriter_t fw, SqtpSubframeId_t id, const uint8_t *JavaByteArray, size_t sz );
#else
FUNC_ATTR SqtpFrameWriter_t sqtpFrameWriterWriteStructDirect(SqtpFrameWriter_t fw, SqtpSubframeId_t id, const uint8_t *payload, size_t sz );
#endif

FUNC_ATTR SqtpFrameWriter_t sqtpFrameWriterWriteStructSubframe(SqtpFrameWriter_t fw, SqtpSubframe_t sf );
FUNC_ATTR SqtpFrameWriter_t sqtpFrameWriterFinalizeStruct(SqtpFrameWriter_t fw );

#ifdef SWIGJAVA
// SWIGJAVA helper(s):
//Not currently implemented: int SqspFrameByteArray  (uint8_t *JavaByteArray, int Length,  SqtpFrameWriter_t *FW);
int SqtpCheckValue_tSize(void);
#endif

#ifdef    __cplusplus
}
#endif  //__cplusplus

#endif  //__SQTPFRAME_H__
