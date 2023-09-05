/******************************************************************************
** Copyright 2020 - SignalQuest, Inc.    PROPRIETARY & CONFIDENTIAL
*******************************************************************************
**
** CopFWProtocol.h
**
**     SPI based Coprocessor Boot FW Protocol Layer
**
*******************************************************************************
** $Id: 
******************************************************************************/

//############################################################################
#ifndef COPFWPROTOCOL_H_
#define COPFWPROTOCOL_H_
//############################################################################

#include	<stdint.h>
#include	"SQ_CopProtocol.h"

//	Coprocessor Flash Layout ---------------------------------------------------------------------
#define	COP_BOOT_IMAGE_BASE_0	(0x00010000ull)
#define COP_APPLICATION_ADDRESS	(COP_BOOT_IMAGE_BASE_0)   // Base of applications

//	NOTE:		from: nrfx_nvmc.c
//					static uint32_t flash_total_size_get(void)  { return flash_page_size_get() * flash_page_count_get(); }	
//					[flash_page_size 	= NVMC_FLASH_PAGE_SIZE;]
//					[page_count 			= NVMC_FLASH_PAGE_COUNT;]
//					#define NVMC_FLASH_PAGE_SIZE  0x1000 // 4 kB
//					#define NVMC_FLASH_PAGE_COUNT  128

#define	VECTOR_TABLE_SIZE			((size_t)(&__Vectors_Size))	//(0x00000400)
#define	BOOT_PARTITION_SIZE		(0x00010000ull)
#define	FLASH_SIZE						(0x00080000ull)	
#define	FW_PARTITION_SIZE			(FLASH_SIZE	-	BOOT_PARTITION_SIZE)

#define	BOOTLOW			0
#define	BOOTHIGH		(COP_BOOT_IMAGE_BASE_0 + BOOT_PARTITION_SIZE)

#define	COP_FW_LOW	(COP_BOOT_IMAGE_BASE_0)
#define	COP_FW_HIGH	(COP_BOOT_IMAGE_BASE_0	+	FW_PARTITION_SIZE)


#if  defined(__ANDROID__) || defined(__iOS__)

//	NOTE: Avoid Bit Fields for Flutter FFIgen.

typedef	struct	SPI_Frame_Header_s
{
	/* Coerce to 8 byte Boundary by width */
	uint16_t	Total_Length	; //:	16;
	uint16_t	Reserved16		; //:	16;
	uint32_t	Alignment_Pad	; //:	32;
}
SPI_Frame_Header_t; //TODO: More generic name: lose the "SPI", use "COP"?

typedef	struct	Sub_Frame_Header_s
{
	/*	All Sub Frames must begin with this Header for 8 byte alignment */
	uint16_t	Frame_Type		; //:	16;	//	NOTE:	Frame_enum_e
    uint16_t	Length			; //:	16;
	uint32_t	Alignment_Pad	; //:	32;	//	Also used for Boot Loader Flags to/from host
	/*	maintain 8 byte/64 bit width */
}
Sub_Frame_Header_t;

#else  // defined(__ANDROID__) or defined(__iOS__)

typedef	struct	SPI_Frame_Header_s
{
	/* Coerce to 8 byte Boundary by width */
	uint64_t	Total_Length	:	16;
	uint64_t	Reserved16		:	16;
	uint64_t	Alignment_Pad	:	32;
}
SPI_Frame_Header_t;

typedef	struct	Sub_Frame_Header_s
{
	/*	All Sub Frames must begin with this Header for 8 byte alignment */
	uint64_t	Frame_Type		:	16;	//	NOTE:	Frame_enum_e
  uint64_t		Length				:	16;
	uint64_t	Alignment_Pad	:	32;	//	Also used for Boot Loader Flags to/from host
	/*	maintain 8 byte/64 bit width */
}
Sub_Frame_Header_t;
#endif  // defined(__ANDROID__) or defined(__iOS__)



typedef	struct  SPI_Unknown_Frame_s
{
	//	All Sub Frames must begin with:
  Sub_Frame_Header_t	Header;
  uint8_t	Payload[8];				//	8 byte aligned dummy payload
  uint32_t	CheckValue;				//	dummy CheckValue, here for structure relative sizeof() calculations. NOTE: Actually located right after Payload.  Shown here for worst case Payload.
}
SPI_Unknown_Frame_t;


typedef	struct  SPI_BOOT_FROM_HOST_data_s
{
	//	All Sub Frames must begin with:
  Sub_Frame_Header_t	Header;
  uint32_t	Body[512/sizeof(uint32_t)];	//	Boot data	//	'nn' byte payload
  uint32_t	CheckValue;
}
SPI_BOOT_FROM_HOST_data_t;


typedef	struct  SPI_BOOT_TO_HOST_data_s
{
	//	All Sub Frames must begin with:
  Sub_Frame_Header_t	Header;
  uint32_t	Body[128];	//	Boot data
  uint32_t	CheckValue;
}
SPI_BOOT_TO_HOST_data_t;


//-- Union of Known Frames ---
typedef	union FramePayload_u
{
	SPI_Unknown_Frame_t			SPI_Unknown_Frame;	//	Bare Frame for parsing and sizeof(Frame CheckValue) in code.

	//	NOTE: (Should be) Same size as SQ_CopProtocol_Buffer.Buffer[] .
	#if		defined(SQ_COP_PROTOCOL_FIXED_BUFFER_SIZE)
	uint8_t	Payload[SQ_COP_PROTOCOL_ACTUAL_MAX_BUFFER_SIZE	-	(sizeof(SPI_Frame_Header_t)	+	sizeof(uint32_t))];	//	Account for Frame overhead			//	NOTE: Same size as SQ_CopProtocol_Buffer.Buffer[] .
	#else
	uint8_t	Payload[SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE];		//	NOTE: Same size as SQ_CopProtocol_Buffer.Buffer[] .
	#endif
}
FramePayload_t;

typedef	struct	SPI_Host_Frame_s
{
  SPI_Frame_Header_t	Header;			//	8 byte Header
  FramePayload_t			Payload;
  uint32_t						CheckValue;	//	NOTE: Actually located right after Payload.  Shown here for worst case Payload.
}
SPI_Host_Frame_t;

typedef	union	COP_Frame_u
{
	SPI_Host_Frame_t				Frame;
	SQ_CopProtocol_Buffer_t	byte;		//NOTE: SQ_CopProtocol_Buffer_t contains a Frame Header, in addition to at least one Sub Frame Header
}
COP_Frame_u_t;


extern	SQ_CopProtocol_Buffer_t	SQ_CopProtocol_Buffer;

//############################################################################
#endif //	COPFWPROTOCOL_H_
//############################################################################

