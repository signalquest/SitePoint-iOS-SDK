/******************************************************************************
** Copyright 2020 - SignalQuest, Inc.    PROPRIETARY & CONFIDENTIAL
*******************************************************************************
**
** This file is confidential and proprietary property of SignalQuest, Inc.
** All rights are reserved. This file may not be used, reproduced or
** distributed by any unauthorized party.  Unauthorized copies of this file
** must be deleted or destroyed immediately.
**
*******************************************************************************
**
** SQ_CopProtocol.h
**
**     SPI based Coprocessor Protocol Layer
**
*******************************************************************************
** $Id: 
******************************************************************************/

//############################################################################
#ifndef SQ_COPPROTOCOL_H_
#define SQ_COPPROTOCOL_H_
//############################################################################

#include "SQ_CopProtocol_config.h"

#include	<stdint.h>
#include	<stdbool.h>
#include	<string.h>

//	SQ_CopProtocol Status Return Codes
#define	SQ_CopProtocol_SUCCESS								( 0)
#define	SQ_CopProtocol_IDLE										SQ_CopProtocol_SUCCESS

#define	SQ_CopProtocol_SUB_FRAME_NOT_HANDLED	( 1)	//	TODO: Look into whether this should be a negative value.
#define	SQ_CopProtocol_SUB_FRAME_PENDING			( 2)
#define	SQ_CopProtocol_CROSS_PAGE_BOUNDARY		( 3)

#define	SQ_CopProtocol_NOT_INITIALIZED				( -1)
#define	SQ_CopProtocol_BUSY										( -2)
#define	SQ_CopProtocol_BAD_RX_FRAME						( -3)
#define	SQ_CopProtocol_BAD_RX_SUB_FRAME				( -4)
#define	SQ_CopProtocol_BAD_FW_ADDRESS					( -5)
#define	SQ_CopProtocol_PAYLOAD_TO_BIG					( -6)
#define	SQ_CopProtocol_NULL_IMAGE							( -7)
#define	SQ_CopProtocol_IMAGE_ALIGNMENT				( -8)
#define	SQ_CopProtocol_BAD_CRC								( -9)
#define	SQ_CopProtocol_NO_FRAME_PENDING				(-10)
#define	SQ_CopProtocol_ZERO_SIZE							(-11)
#define	SQ_CopProtocol_NO_PARTIAL_PAGE_ERASE	(-12)

#define	SQ_CopProtocol_FAILED									(-100)


#if		defined(SQ_COP_PROTOCOL_FIXED_BUFFER_SIZE)

//	NOTE:	SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE is max. total for Payload not counting Frame and Sub Frame overhead]
//	NOTE:	SQ_COP_PROTOCOL_ACTUAL_MAX_BUFFER_SIZE is max. total for Buffer including Frame and Sub Frame overhead]
//	NOTE: Actual Maximum Frame size	(used in code):
//
//	NOTE: Actual Maximum frame size	(used in code):
//
//		sizeof(SPI_Frame_Header_t)
//		+
//		SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE
//		+
//			(		SQ_COP_PROTOCOL_CONFIG_MAX_SUB_FRAMES
//					*
//					(sizeof(Sub_Frame_Header_t)	+	sizeof(uint32_t))		//	(sizeof(Sub_Frame_Header_t)	+ sizeof(SQ_CopProtocol_Buffer.CheckValue) )
//			)
//		)
//		+
//		sizeof(uint32_t)																				//	sizeof(SQ_CopProtocol_Buffer.CheckValue)
//
//	NOTE:	We don't strongly enforce SQ_COP_PROTOCOL_CONFIG_MAX_SUB_FRAMES, we'll allow more frames as long as they fit.

//	NOTE:	The actual Buffer size maybe as much as 4 bytes longer than SQ_COP_PROTOCOL_ACTUAL_MAX_BUFFER_SIZE due to padding (due to 4 byte alignment for CheckValue).
#define	SQ_COP_PROTOCOL_ACTUAL_MAX_BUFFER_SIZE				\
(		sizeof(SPI_Frame_Header_t)												\
	+	SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE            \
	+	(	SQ_COP_PROTOCOL_CONFIG_MAX_SUB_FRAMES           \
			*                                               \
			(sizeof(Sub_Frame_Header_t)	+	sizeof(uint32_t)) \
		)                                                 \
	+	sizeof(uint32_t)         													\
)
#endif	//	defined(SQ_COP_PROTOCOL_FIXED_BUFFER_SIZE)

#if 000
typedef	struct  SQ_CopProtocol_Buffer_s
{

#if		defined(SQ_COP_PROTOCOL_FIXED_BUFFER_SIZE)
  uint8_t	Buffer[SQ_COP_PROTOCOL_ACTUAL_MAX_BUFFER_SIZE	-	(sizeof(SPI_Frame_Header_t)	+	sizeof(uint32_t))];	//	Account for Frame overhead
#else
  uint8_t	Buffer[SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE];	//[SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE];	//[MAX_COP_BUFFER_SIZE];
#endif

}
SQ_CopProtocol_Buffer_t;
#endif

#if  defined(__ANDROID__) || defined(__iOS__)

typedef	struct  SQ_CopProtocol_Buffer_s
{

#if		defined(SQ_COP_PROTOCOL_FIXED_BUFFER_SIZE)
  uint8_t	Buffer[SQ_COP_PROTOCOL_ACTUAL_MAX_BUFFER_SIZE	-	(sizeof(SPI_Frame_Header_t)	+	sizeof(uint32_t))];	//	Account for Frame overhead
#else
  uint8_t	Buffer[SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE];	//Buffer[243];	//[MAX_COP_BUFFER_SIZE];
#endif

}
SQ_CopProtocol_Buffer_t;

extern	SQ_CopProtocol_Buffer_t COP_In;		// 'flat' byte buffer for passing raw frames into COP layer
extern	SQ_CopProtocol_Buffer_t COP_Out;	// 'flat' byte buffer for passing raw frames out of COP layer

__attribute__((visibility("default"))) __attribute__((used))
uint8_t *get_COP_In_Pointer(SQ_CopProtocol_Buffer_t *pointer);

__attribute__((visibility("default"))) __attribute__((used))
uint8_t *get_COP_Out_Pointer(SQ_CopProtocol_Buffer_t *pointer);

//NOTE: Use SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE here to make ffigen happy
//NOTE: Use of SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE may need adjustment if defined(SQ_COP_PROTOCOL_FIXED_BUFFER_SIZE) is true.
#define sizeof_COP_In  SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE  //243 //SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE       //  aka: Dart: sizeOf<SQ_CopProtocol_Buffer_t>()
#define sizeof_COP_Out (sizeof(COP_Out))    //  aka: Dart: sizeOf<SQ_CopProtocol_Buffer_t>()

#else  //  defined(__ANDROID__) or defined(__iOS__)	//#if  000 //not defined(__ANDROID__)
extern SPI_Host_Frame_t	COP_Out;	//	SQ COP Protocol TX message
#endif  //  defined(__ANDROID__) or defined(__iOS__)


/* typedef the RX Callback function pointer */
typedef void SQ_CopProtocol_CB_ReceiveFrame_t(uint16_t type, uint16_t Status, const void *Buffer, size_t size, void *Context);

/* typedef the End Of Transaction callback function pointer */
typedef void SQ_CopProtocol_CB_EOT_t(uint16_t Status, void *Context);


/* Start building a new frame,
	 Returns error codes (TBD) [Frame is ‘Busy’, too large, etc.]
 */
__attribute__((visibility("default"))) __attribute__((used))
int16_t SQ_CopProtocol_Start_Frame(uint16_t type, const void *TX, size_t TXsize);

/* Add to an already started frame,
   Returns error codes (TBD) [Frame not started, Frame is ‘Busy’, too large, etc.]
 */
int16_t SQ_CopProtocol_Add_Sub_Frame(uint16_t type, const void *TX, size_t TXsize);

/* Send the frame,
   Returns error codes (TBD) [Frame not started, Frame is ‘Busy’, too large, etc.]

	NOTES:
	 - EOT_Callback is called after last Sub Frame RX Callback completes.
   - RX_Callback must be registered using SQ_CopProtocol_Register_RX_Handler().
	 - If EOT_Callback is NULL, then no callback occurs, and the calling program must poll
     SQ_CopProtocol_Frame_Status() to determine when the transaction is complete.
 */
#if  defined(__ANDROID__) || defined(__iOS__)

#include	"CopFWProtocol.h"  //Why isn't SQ_COP_PROTOCOL_ACTUAL_MAX_BUFFER_SIZE picked up here?

//Consider an implementation where we bury *Buffer and *Buffer_Length within a Context
//int16_t SQ_CopProtocol_Send_Frame(SQ_CopProtocol_CB_EOT_t *EOT_Callback, void *Context, void *Buffer);
//int16_t SQ_CopProtocol_Send_Frame(SQ_CopProtocol_CB_EOT_t *EOT_Callback, void *Context, void *Buffer, size_t *Buffer_Length);
__attribute__((visibility("default"))) __attribute__((used))
int16_t SQ_CopProtocol_Send_Frame(SQ_CopProtocol_CB_EOT_t *EOT_Callback, void *Context, void *Buffer, uint16_t *Buffer_Length);


#else // defined(__ANDROID__) or defined(__iOS__)
__attribute__((visibility("default"))) __attribute__((used))
int16_t SQ_CopProtocol_Send_Frame(SQ_CopProtocol_CB_EOT_t *EOT_Callback, void *Context);
#endif // defined(__ANDROID__) or defined(__iOS__)
/* Poll the frame status,
   Useful if not using a Callback function, also for timeout/fault logic.
   Returns error codes (TBD) [Frame is ‘Free’, Frame is ‘Busy’, too large, etc.]
 */
int16_t SQ_CopProtocol_Frame_Status(void);

/* Register a Callback function for a received Sub Frame type,
   must only be called when Frame is not ‘Busy, etc.
	 Returns error codes (TBD) [Frame is ‘Busy’, etc.]

	NOTES:
	 -If no receive handler is registered, received frames will be ignored
		and discarded.
 */
int16_t SQ_CopProtocol_Register_RX_Handler(void *Context, SQ_CopProtocol_CB_ReceiveFrame_t *RX_Callback);
int16_t SQ_CopProtocol_Register_TX_Handler(void *Context, SQ_CopProtocol_CB_EOT_t *TX_Callback);

/*	Resend last Frame [Useful when Coprocessor is too busy to reply, or replies with a partial or corrupt frame.] */
int16_t SQ_CopProtocol_Resend_Frame(SQ_CopProtocol_CB_EOT_t *EOT_Callback, void *Context);

void	SQ_CopProtocol_FSM(void);
void	SQ_CopProtocol_Callback(uint16_t Status_, const uint8_t *Buffer, size_t size, void *Context);

#if 000
#if  defined(__ANDROID__) || defined(__iOS__)

typedef	struct  SQ_CopProtocol_Buffer_s
{

#if		defined(SQ_COP_PROTOCOL_FIXED_BUFFER_SIZE)
  uint8_t	Buffer[SQ_COP_PROTOCOL_ACTUAL_MAX_BUFFER_SIZE	-	(sizeof(SPI_Frame_Header_t)	+	sizeof(uint32_t))];	//	Account for Frame overhead
#else
  uint8_t	Buffer[SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE];	//[SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE];	//[MAX_COP_BUFFER_SIZE];
#endif

}
SQ_CopProtocol_Buffer_t;

extern	SQ_CopProtocol_Buffer_t COP_In;		// 'flat' byte buffer for passing raw frames into COP layer
extern	SQ_CopProtocol_Buffer_t COP_Out;	// 'flat' byte buffer for passing raw frames out of COP layer

__attribute__((visibility("default"))) __attribute__((used))
uint8_t *get_COP_In_Pointer(SQ_CopProtocol_Buffer_t *pointer);

__attribute__((visibility("default"))) __attribute__((used))
uint8_t *get_COP_Out_Pointer(SQ_CopProtocol_Buffer_t *pointer);

#else  //  defined(__ANDROID__)	or defined(__iOS__)//#if  000 //not defined(__ANDROID__)
extern SPI_Host_Frame_t	COP_Out;	//	SQ COP Protocol TX message
#endif  //  defined(__ANDROID__) or defined(__iOS__)
#endif // 000

#if defined(SQ_COP_SUB_FRAME_REPORT)

typedef union Payload_u_s
{
    uint8_t		        Payload[8];			//	8 byte aligned dummy payload
    uint64_t		    Payload2;			//	8 byte aligned dummy payload
}
Payload_u_t;

typedef struct SubFrame_Report_s
{
    uint8_t *Payload; //	8 byte aligned payload

    uint16_t SubFrame_Type;
    uint16_t Length;

    uint16_t Status;
}
SubFrame_Report_t;

typedef struct Frame_Report_Array_s
{
    SubFrame_Report_t   SubFrame[SQ_COP_PROTOCOL_CONFIG_MAX_SUB_FRAMES];
}
Frame_Report_Array_t;

typedef struct Frame_Report_s
{
    SubFrame_Report_t   SubFrame[SQ_COP_PROTOCOL_CONFIG_MAX_SUB_FRAMES];
    uint16_t    Number_of_SubFrames;
}
Frame_Report_t;

__attribute__((visibility("default"))) __attribute__((used))
Frame_Report_t   SQ_CopProtocol_Parse_Frame(const uint8_t *Buffer, size_t size);

Frame_Report_Array_t * pointerFromFrameReport(Frame_Report_t * report);

SubFrame_Report_t reportAtIndex(Frame_Report_t * report, int64_t index);


#endif  //  defined(SQ_COP_SUB_FRAME_REPORT)



//############################################################################
#endif //	SQ_COPPROTOCOL_H_
//############################################################################

