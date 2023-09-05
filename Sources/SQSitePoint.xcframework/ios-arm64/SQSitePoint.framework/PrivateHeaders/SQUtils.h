#ifndef SQUTILS_H_
#define SQUTILS_H_

#include	<iso646.h>
#include	<stddef.h>

//---------------------------------------------------------------------------------------------------------------------------------------
#if	defined(__ANDROID__) || defined(__iOS__)
//---------------------------------------------------------------------------------------------------------------------------------------
	//	...
#define NO_ANGLES	(1)

#elif		defined(ESP_PLATFORM)	//	defined(CONFIG_IDF_TARGET_ARCH_RISCV)
	//	...
#define NO_ANGLES	(1)

#elif		defined(NRF5340_XXAA_APPLICATION)	//defined(SQ_COP_PROTOCOL_CONFIG_AS_SPI_SLAVE)	//TODO:		Reconcile NRF5340_XXAA_APPLICATION vs SQ_COP_PROTOCOL_CONFIG_AS_SPI_SLAVE here.
	#if		defined(SQ_NPG_0026)
#include	"SQ_NPG_0026.h"
	#elif	defined(SQ_NPG_0027)
#include	"SQ_NPG_0027.h"
	#else
#warning	"SQCopProtocol Configuration issue."
	#endif
#else	//	defined(NRF5340_XXAA_APPLICATION)	//defined(SQ_COP_PROTOCOL_CONFIG_AS_SPI_SLAVE)

#include	"SQDefs.h"

void SQ_Zero( void *pu8Object, u16 u16ObjectSize );
f32 SQ_atan2( f32 f32Num, f32 f32Den );
f32 SQ_atan1( f32 f32Num, f32 f32Den );
f32 SQ_wrap180_180( f32 f32Angle );
f32 SQ_wrap90_90( f32 f32Angle );
u16 CRC16_calc(u16 u16CRC, u8 u8CRCData);
#endif	//	defined(NRF5340_XXAA_APPLICATION)	//defined(SQ_COP_PROTOCOL_CONFIG_AS_SPI_SLAVE)

unsigned short SQCRC16(unsigned short fcs, unsigned char *buf, size_t len);
													 
#endif // SQUTILS_H_
