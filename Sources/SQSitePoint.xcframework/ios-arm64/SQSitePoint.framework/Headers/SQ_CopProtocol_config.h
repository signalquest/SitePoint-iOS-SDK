/* SQ_CopProtocol_config.h */

#ifndef __SQ_CopProtocol_config_h__
#define __SQ_CopProtocol_config_h__


#include	<iso646.h>
#include	<stddef.h>
#include	<stdint.h>

#if defined(__APPLE__)
#include    <TargetConditionals.h>
#endif

#if 0 && (TARGET_RT_64_BIT == 1)
#error HERE : "#TARGET_CPU_ARM64"
#endif

//---------------------------------------------------------------------------------------------------------------------------------------
#if	defined(__ANDROID__) || defined(__iOS__)
//---------------------------------------------------------------------------------------------------------------------------------------
#define SQ_COP_SUB_FRAME_REPORT    (1)

//---------------------------------------------------------------------------------------------------------------------------------------
#elif ! defined(ESP_PLACEHOLDER)
//---------------------------------------------------------------------------------------------------------------------------------------

#include "sdkconfig.h"

//---------------------------------------------------------------------------------------------------------------------------------------
#elif	defined(NRF5340_XXAA_APPLICATION)	// !defined(ESP_PLACEHOLDER)
//---------------------------------------------------------------------------------------------------------------------------------------

	#if		defined(SQ_NPG_0026)
#include	"SQ_NPG_0026.h"
	#elif	defined(SQ_NPG_0027)
#include	"SQ_NPG_0027.h"
	#else
#warning	"SQCopProtocol Configuration issue."
	#endif

#else
#include "SQDefs.h"
#endif


//---------------------------------------------------------------------------------------------------------------------------------------
#if	defined(__ANDROID__) || defined(__iOS__)
//---------------------------------------------------------------------------------------------------------------------------------------

//	Common Host and Coprocessor Parameters, [These should be the same for both.]

#define SQ_COP_PROTOCOL_CONFIG_ENABLE (1)
#define SQ_COP_PROTOCOL_CONFIG_MAX_SUB_FRAMES (4)
#define SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE (243) //(1024)

//	Host and Coprocessor Specific Parameters, [These should probably be the same for both, particularly anything affecting Frame size.]
//---------------------------------------------------------------------------------------------------------------------------------------
#elif defined(ESP_PLACEHOLDER)
//---------------------------------------------------------------------------------------------------------------------------------------

//	Common Host and Coprocessor Parameters, [These should be the same for both.]

#define SQ_COP_PROTOCOL_CONFIG_ENABLE (1)
#define SQ_COP_PROTOCOL_CONFIG_MAX_SUB_FRAMES (4)
#define SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE (243)

//	Host and Coprocessor Specific Parameters, [These should probably be the same for both, particularly anything affecting Frame size.]

//---------------------------------------------------------------------------------------------------------------------------------------
#elif not defined(ENABLE_COPROCESSOR_IF)
//---------------------------------------------------------------------------------------------------------------------------------------

// NOT USING CO-PROCESSOR!

//	Common Host and Coprocessor Parameters, [These should be the same for both.]

#define SQ_COP_PROTOCOL_CONFIG_ENABLE (1)
#define SQ_COP_PROTOCOL_FIXED_BUFFER_SIZE (1)		//	define to enable fixed payload size
#define SQ_COP_PROTOCOL_CONFIG_MAX_SUB_FRAMES (4)
#define SQ_COP_PROTOCOL_CONFIG_USE_SPI_COPROCESSOR_SHIM (1)
#define SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE (1024)

//	Host and Coprocessor Specific Parameters, [These should probably be the same for both, particularly anything affecting Frame size.]

//---------------------------------------------------------------------------------------------------------------------------------------
#else // not defined(ENABLE_COPROCESSOR_IF)
//---------------------------------------------------------------------------------------------------------------------------------------

	#if		not	defined(SQ_COP_PROTOCOL_CONFIG_AS_SPI_SLAVE)	//-----------------------------------------------------
#define SQ_COP_PROTOCOL_CONFIG_USE_PERFORMANCE_TIMERS (1)
	#endif	//	defined(SQ_COP_PROTOCOL_CONFIG_AS_SPI_SLAVE)	//-----------------------------------------------------

//	Common Host and Coprocessor Parameters, [These should be the same for both.]

#define SQ_COP_PROTOCOL_CONFIG_ENABLE (1)
#define SQ_COP_PROTOCOL_FIXED_BUFFER_SIZE (1)		//	define to enable fixed payload size
#define SQ_COP_PROTOCOL_CONFIG_MAX_SUB_FRAMES (4)
#define SQ_COP_PROTOCOL_CONFIG_USE_SPI_COPROCESSOR_SHIM (1)

	#if defined(ENABLE_COPROCESSOR_IF)
		#if		defined(INS_ENABLE)
#define SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE (sizeof(AllTransfers_t) + 256)
		#else	//	defined(INS_ENABLE)
#define SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE (1024)
		#endif	//	defined(INS_ENABLE)
	#endif	//	defined(ENABLE_COPROCESSOR_IF)

#if		defined(INS_ENABLE)
#include	"INS_internal.h"
typedef union _AllTransfers_u
{
	uint8_t init_frame[sizeof(INS_NavKF_Init_t)];
	uint8_t m_tick_frame[sizeof(INS_NavKFM_TickInput_t) + sizeof(NCycleNavTransfer_t)];
	uint8_t m_return_frame[sizeof(LCycleControlReset_t) + sizeof(MCycleControlReset_t) + sizeof(INS_NavKFN_OutputData_t)];
} AllTransfers_t;

#define SQ_COP_PROTOCOL_CONFIG_MAX_BUFFER_SIZE (sizeof(AllTransfers_t) + 256)
#endif	//	defined(INS_ENABLE)

//	Host and Coprocessor Specific Parameters, [These should probably be the same for both, particularly anything affecting Frame size.]
//=========================================================================================================================
	#if		defined(SQ_COP_PROTOCOL_CONFIG_AS_SPI_SLAVE)
//=========================================================================================================================

#define	DEBUG_BYPASS_RUN_CRC_CHECK		(1)		//	Don't check CRC on FW Run request, run any FW.  Useful during development.
#define	ENABLE_COPROCESSOR_FW_UPDATE	(1)		//	Enable Erase, Write to FLASH, CRC Flash and Boot downloaded FW.

		#if		0001	//move to ???
			#if		defined(SQ_COP_PROTOCOL_CONFIG_AS_SPI_SLAVE)	//-----------------------------------------------------
//----------------------------------------------------------------------------
//	Global Data
//----------------------------------------------------------------------------

extern	const	uint32_t	__Vectors;			//	Linker generated Global
extern	const	uint32_t	__Vectors_End;	//	Linker generated Global
extern	const	uint32_t	__Vectors_Size;	//	Linker generated Global

extern	const	uint32_t	Load$$LR$$LR_IROM1$$Base;		//	Linker generated Global
extern	const	uint32_t	Load$$LR$$LR_IROM1$$Limit;  //	Linker generated Global
extern	const	uint32_t	Load$$LR$$LR_IROM1$$Length; //	Linker generated Global
//----------------------------------------------------------------------------
			#endif	//	defined(SQ_COP_PROTOCOL_CONFIG_AS_SPI_SLAVE)	//-----------------------------------------------------
		#endif

//=========================================================================================================================
	#else	//	defined(SQ_COP_PROTOCOL_CONFIG_AS_SPI_SLAVE)
//=========================================================================================================================

#define SQ_COP_PROTOCOL_CONFIG_USE_PERFORMANCE_TIMERS (1)

//=========================================================================================================================
	#endif	//	defined(SQ_COP_PROTOCOL_CONFIG_AS_SPI_SLAVE)
//=========================================================================================================================

//---------------------------------------------------------------------------------------------------------------------------------------
#endif // not defined(ENABLE_COPROCESSOR_IF)
//---------------------------------------------------------------------------------------------------------------------------------------

#endif
