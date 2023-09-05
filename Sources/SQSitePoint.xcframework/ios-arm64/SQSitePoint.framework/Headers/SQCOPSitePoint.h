/******************************************************************************
** Copyright 2022 - SignalQuest, Inc.    PROPRIETARY & CONFIDENTIAL
*******************************************************************************
**
** This file is confidential and proprietary property of SignalQuest, Inc.
** All rights are reserved. This file may not be used, reproduced or
** distributed by any unauthorized party.  Unauthorized copies of this file
** must be deleted or destroyed immediately.
**
*******************************************************************************
**
** SQCOPSitePoint.h
**
**     SitePoint	SQ COP Sub Frame IDs and data structures
**
*******************************************************************************
** $Id: 
******************************************************************************/

#pragma once

//----------------------------------------------------------
// The following should be coming from SQ_CopProtocol_config.h or ???
//----------------------------------------------------------
#define     ENABLE_STATUS_EXTENSION (1) //force it, doesn't belong here
#define     lb_config_t_SIZE_PATCH (1)  //force it, doesn't belong here
#define 	ENABLE_LLA_EXTENSION	(1) //force it, doesn't belong here
//----------------------------------------------------------

//Notes:    https://gcc.gnu.org/onlinedocs/gcc-3.3/gcc/Type-Attributes.html
//          https://gcc.gnu.org/onlinedocs/gcc-3.2/gcc/Variable-Attributes.html
//  To specify multiple attributes, separate them by commas within the double parentheses: for example, __attribute__ ((aligned (16), packed)).

//From : cdefs.h : #define	__packed	__attribute__((__packed__))
#if !defined(__packed)
#define	__packed	__attribute__((__packed__))
#endif // not defined(__packed)

#include <iso646.h>
#include <stdint.h>
#include <time.h>

#if	defined(__ANDROID__) || defined(__iOS__)
#include "SQ_CopProtocol.h"
#else
#include "../SQCopProtocol/SQ_CopProtocol.h"
#endif

#if	001
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
#endif


//----------------------------------------------------------
// NOTE: Must define (only one) of the following #defines : 
//		USE_COP_SUB_FRAME_DEFINES 
//	or	USE_COP_SUB_FRAME_ENUM 
//	or	USE_COP_SUB_FRAME_TYPEDEF_ENUM
//	or	USE_COP_SUB_FRAME_CONST
//----------------------------------------------------------
#define	USE_COP_SUB_FRAME_DEFINES	(1)  //works, propagates Sub Frame type numbering

//----------------------------------------------------------

//	=========	==========	==============	============	============	=========	===========		==============	==============	=====================	============================================		
//	Notes		Task		typedef			Sub Frame ID	Sub Frame ID	To Sensor	From Sensor		Characteristic	Characteristic	Legacy Characteristic	COP Characteristic
//	=========	==========	==============	============	============	=========	===========		==============	==============	=====================	============================================		
//	Service: SitePoint -------------------------------------------------------------------------------------------------------------	00000100	Service
//	(BT MTU)	MTU							0x122F			4655										0x0105			261				00000000	
//	TBD	RSVD	OTA Update					0x1230			4656			?			?				0x0105			261				00000001				00000105 - 34ed - 12ef - 63f4 - 317792041d17
//	TBD	RSVD	OTA Status					0x1231			4657			?			?				0x0105			261				00000002				00000105 - 34ed - 12ef - 63f4 - 317792041d17
//																																		   ...
//				[Not Used]																												00000100	
//				[Not Used]																												00000101	
//				RTCM		user_payload_t	0x1232			4658			X							0x0105			261				00000102				00000105 - 34ed - 12ef - 63f4 - 317792041d17
//				Status		sqgps_status_t	0x1233			4659						X				0x0105			261				00000104				00000105 - 34ed - 12ef - 63f4 - 317792041d17
//				LLA			sqgps_lla_t		0x1234			4660						X				0x0105			261				00000103				00000105 - 34ed - 12ef - 63f4 - 317792041d17
//
//	Service : [Name ?] -------------------------------------------------------------------------------------------------------------	00000200	Service
//																										0x0105			261				00000200				???
//				MODE		lb_config_t		0x1235			4661			X			X				0x0105			261				00000201				00000105 - 34ed - 12ef - 63f4 - 317792041d17
//	=========	==========	==============	============	============	=========	===========		==============	==============	=====================	============================================		


#if defined(USE_COP_SUB_FRAME_DEFINES)

#define COP_SF_OTA_MTU	 	0x122F
#define COP_SF_OTA_UPDATE 	0x1230
#define COP_SF_OTA_STATUS 	0x1231
#define COP_SF_RTCM			0x1232	//	user_payload_t
#define COP_SF_STATUS		0x1233	//	sqgps_status_t
#define COP_SF_LLA			0x1234	//	sqgps_lla_t
#define COP_SF_MODE			0x1235	//	lb_config_t
#define COP_SF_RELPOS		0x1236	//	sqgps_relpos_t

#define COP_SF_STATUS_PORTABLE	0x1243	//	sqgps_status_Portable_t
#define COP_SF_LLA_PORTABLE		0x1244	//	sqgps_lla_Portable_t
#define COP_SF_MODE_PORTABLE	0x1245	//	lb_config_Portable_t
#define COP_SF_RELPOS_PORTABLE	0x1246	//	sqgps_relpos_Portable_t

#elif defined(USE_COP_SUB_FRAME_ENUM)

enum COP_SF_e
{ 
	COP_SF_OTA_MTU	  = 0x122F,
	COP_SF_OTA_UPDATE = 0x1230,
	COP_SF_OTA_STATUS = 0x1231,
	COP_SF_RTCM = 0x1232, //	user_payload_t	
	COP_SF_STATUS = 0x1233, //	sqgps_status_t	
	COP_SF_LLA = 0x1234, //	sqgps_lla_t		
	COP_SF_MODE = 0x1235, //	lb_config_t		
	
	COP_SF_COP_SF_STATUS_PORTABLE		= 0x1243,	//	sqgps_status_Portable_t
	COP_SF_COP_SF_LLA_PORTABLE		= 0x1244,	//	sqgps_lla_Portable_t
	COP_SF_MODE_PORTABLE	= 0x1245,	//	lb_config_Portable_t

	COP_SF_FFFF = 0xFFFF, // force (at least 16 bit width)
};

#elif defined(USE_COP_SUB_FRAME_TYPEDEF_ENUM)

typedef enum COP_SF_e
{ 	
	COP_SF_OTA_MTU	  = 0x122F,
	COP_SF_OTA_UPDATE = 0x1230,
	COP_SF_OTA_STATUS = 0x1231,
	COP_SF_RTCM = 0x1232, //	user_payload_t	
	COP_SF_STATUS = 0x1233, //	sqgps_status_t	
	COP_SF_LLA = 0x1234, //	sqgps_lla_t		
	COP_SF_MODE = 0x1235, //	lb_config_t		

	COP_SF_COP_SF_STATUS_PORTABLE	= 0x1243,	//	sqgps_status_Portable_t
	COP_SF_LLA_PORTABLE		= 0x1244,	//	sqgps_lla_Portable_t
	COP_SF_MODE_PORTABLE	 	= 0x1245,	//	lb_config_Portable_t

	COP_SF_FFFF = 0xFFFF,	// force (at least 16 bit width)
}
COP_SF_e_t;

#elif defined(USE_COP_SUB_FRAME_CONST)

const uint16_t COP_SF_OTA_MTU		=	0x122F;
const uint16_t COP_SF_OTA_UPDATE 	=	0x1230;
const uint16_t COP_SF_OTA_STATUS 	=	0x1231;
const uint16_t COP_SF_RTCM			=	0x1232;	//	user_payload_t	
const uint16_t COP_SF_STATUS		=	0x1233; //	sqgps_status_t	
const uint16_t COP_SF_LLA			=	0x1234; //	sqgps_lla_t		
const uint16_t COP_SF_MODE			=	0x1235; //	lb_config_t		

const uint16_t COP_SF_COP_SF_STATUS_PORTABLE		= 	0x1243;	//	sqgps_status_Portable_t
const uint16_t COP_SF_LLA_PORTABLE			= 	0x1244;	//	sqgps_lla_Portable_t
const uint16_t COP_SF_MODE_PORTABLE	= 	0x1245;	//	lb_config_Portable_t

#else

#error "Must define (only one of) : USE_COP_SUB_FRAME_DEFINES or USE_COP_SUB_FRAME_ENUM or USE_COP_SUB_FRAME_TYPEDEF_ENUM or USE_COP_SUB_FRAME_CONST"
	
#endif // defined(USE_COP_SUB_FRAME_DEFINES)

//  NOTES:
//  1. Auto_Survey_Enable is valid regardless of the state of Fixed_Base_Enable or Broadcast_Enable
//  2. Performing a Survey in ROVER Mode (Fixed_Base_Enable==0) with Aiding is recommended.  
//  3. Broadcast_Enable requires (Fixed_Base_Enable==1)

typedef 	struct LB_CONFIG_MODE_FLAG_s
{
	uint8_t 	Fixed_Base_Enable  : 1; // If 'false' operate as rover
	                        // If 'true' operate as base
	uint8_t 	Auto_Survey_Enable : 1; // If 'false' operate as base using provided LLA [check/update this description]
	                        // If 'true' operate as base attempting self survey
	uint8_t 	Connected          : 1; // READ ONLY - Ignored on a Write.

	uint8_t 	Correction_Output  : 1; // If 'false' prefer BLE Corrections
	                        // If 'true' prefer Wifi Corrections

	uint8_t 	Aiding_Preference  : 1; // If 'false' prefer NTRIP aiding over a BLE link
	                        // If 'true' prefer Local FIXED BASE RTCM over a BLE link

	uint8_t 	SPARE              : (8 - 7); // Currently Unused bits.
	uint8_t 	Valid_or_Not_Busy  : 1; // If 'true' on a Read, "Data is Valid" or "We're BUSY".  Ignored on a Write. //TODO: Is "We're BUSY" used or useful?
	uint8_t 	Broadcast_Enable   : 1; // Broadcast_Enable requires (Fixed_Base_Enable==1)
}
LB_CONFIG_MODE_FLAG_t;


typedef  struct LB_CONFIG_MODE_PORTABLE_FLAG_s
{
	uint8_t  Fixed_Base_Enable  	;	//: 1; 		    // If 'false' operate as rover
							            //			    // If 'true' operate as base
	uint8_t  Auto_Survey_Enable     ;	//: 1; 		    // If 'false' operate as base using provided LLA [check/update this description]
							            //			    // If 'true' operate as base attempting self survey
	uint8_t  Connected      	    ;	//: 1; 		    // READ ONLY - Ignored on a Write.
							            //
	uint8_t  Correction_Output  	;	//: 1; 		    // If 'false' prefer BLE Corrections
							            //			    // If 'true' prefer Wifi Corrections
							            //
	uint8_t  Aiding_Preference  	;	//: 1; 		    // If 'false' prefer NTRIP aiding over a BLE link
							            //			    // If 'true' prefer Local FIXED BASE RTCM over a BLE link
							            //
	uint8_t  SPARE              	;	//: (8 - 7); 	// Currently Unused bits.
	uint8_t  Valid_or_Not_Busy 	    ; 	//: 1; 		    // If 'true' on a Read, "Data is Valid" or "We're BUSY".  Ignored on a Write. //TODO: Is "We're BUSY" used or useful?
	uint8_t  Broadcast_Enable  	    ; 	//: 1; 		    // Broadcast_Enable requires (Fixed_Base_Enable==1)
}
LB_CONFIG_MODE_PORTABLE_FLAG_t;


typedef union LB_CONFIG_MODE_FLAG_u
{
	uint8_t                 flags;
	LB_CONFIG_MODE_FLAG_t   bit;
}
LB_CONFIG_MODE_FLAG_u_t;


typedef union LB_CONFIG_MODE_FLAG_RAW_u
{
	uint8_t                 flags;
}
LB_CONFIG_MODE_FLAG_RAW_u_t;

#if ! (defined(__ANDROID__) || defined(__iOS__))
extern const    LB_CONFIG_MODE_FLAG_u_t _LB_CONFIG_MODE_FLAG_MODE_BIT_MASK;
#define  LB_CONFIG_MODE_FLAG_MODE_BIT_MASK  (  _LB_CONFIG_MODE_FLAG_MODE_BIT_MASK.flags )
#endif // not defined(__ANDROID__) or defined(__iOS__)

typedef struct lb_config_s {
	int32_t  __packed	lonInt; /* Longitude [deg] * 1e-7 */
	int32_t  __packed	latInt; /* Latitude  [deg] * 1e-7 */
	int32_t  __packed	altInt /*height*/; /* Height above geoid [mm] */
	uint32_t __packed	hAccInt; /* Horizontal accuracy [mm] * 0.1 */
	uint32_t __packed	vAccInt; /* Vertical accuracy [mm] * 0.1 */
	int8_t   __packed	lonHpInt; /* Longitude [deg] high precision * 1e-9 */
	int8_t   __packed	latHpInt; /* Latitude [deg] high precision * 1e-9 */
	int8_t   __packed	altHpInt /*heightHp*/; /* Height about geoid high precision [mm] * 0.1 */

	LB_CONFIG_MODE_FLAG_u_t   __packed	mode;

#if  defined(lb_config_t_SIZE_PATCH)
	uint32_t __packed	DurationInt; /* Seconds */
	int32_t  __packed	altMSLInt; /*was: heightMSL*/ /* Height above geoid [mm] */
	int8_t   __packed	altMSLHpInt; /*was: heightMSLHp*/ /* Height about geoid high precision [mm] * 0.1 */
	int8_t   __packed	padding[3]; //  Pad length to a multiple of 4 bytes
#endif  //  defined(lb_config_t_SIZE_PATCH)
} lb_config_t;

typedef struct lb_config_raw_s {
	int32_t  __packed	lonInt; /* Longitude [deg] * 1e-7 */
	int32_t  __packed	latInt; /* Latitude  [deg] * 1e-7 */
	int32_t  __packed	altInt /*height*/; /* Height above geoid [mm] */
	uint32_t __packed	hAccInt; /* Horizontal accuracy [mm] * 0.1 */
	uint32_t __packed	vAccInt; /* Vertical accuracy [mm] * 0.1 */
	int8_t   __packed	lonHpInt; /* Longitude [deg] high precision * 1e-9 */
	int8_t   __packed	latHpInt; /* Latitude [deg] high precision * 1e-9 */
	int8_t   __packed	altHpInt /*heightHp*/; /* Height about geoid high precision [mm] * 0.1 */

    LB_CONFIG_MODE_FLAG_RAW_u_t	__packed	mode;

#if  defined(lb_config_t_SIZE_PATCH)
	uint32_t __packed	DurationInt; /* Seconds */
	int32_t  __packed	altMSLInt; /*was: heightMSL*/ /* Height above geoid [mm] */
	int8_t   __packed	altMSLHpInt; /*was: heightMSLHp*/ /* Height about geoid high precision [mm] * 0.1 */
	int8_t   __packed	padding[3]; //  Pad length to a multiple of 4 bytes
#endif  //  defined(lb_config_t_SIZE_PATCH)
} lb_config_raw_t;


typedef struct lb_config_Portable_s {
	double	__packed lon; //int32_t  lonInt; /* Longitude [deg] * 1e-7 */
	double	__packed lat; //int32_t  latInt; /* Latitude  [deg] * 1e-7 */
	double	__packed alt; //int32_t  altInt /*height*/; /* Height above geoid [mm] */
	double	__packed altMSL; //int32_t  altMSLInt; /*was: heightMSL*/ /* Height above geoid [mm] */
	double	__packed hAcc; //uint32_t hAccInt; /* Horizontal accuracy [mm] * 0.1 */
	double	__packed vAcc; //uint32_t vAccInt; /* Vertical accuracy [mm] * 0.1 */
	uint32_t  DurationInt;  // __attribute__ ((aligned (4), packed)); /* Seconds */

	LB_CONFIG_MODE_PORTABLE_FLAG_t	 mode;  // __attribute__ ((aligned (1), packed));

	uint8_t      Padding[4];
}
lb_config_Portable_t;



typedef struct RSP_UUID128_s
{
	uint8_t __packed	AD_Length;
	uint8_t __packed	AD_Type;
	uint8_t __packed	_128[16];
}
RSP_UUID_t;

// Pattern after PGN 65292 in '0026 'Sandwich' Trailer Message, bytes 2,5,6,7
//	Overall length should be: //uint8_t flat[31 - (1 + 17) - (1 + 1 + (0 * 2))]; //	Remaining space within RSP after AD_Length, AD Type and MFG ID (2)  [Note that ble_hs_adv_set_fields_mbuf() inserts AD_Length and AD Type but not MFG_ID.]
//typedef __packed struct RSP_s
typedef struct RSP_s
{
	//TODO: Consider unions for the bits in Bytes 6 & 7

	uint16_t   	MFG_DATA_ID;

	uint8_t      	battery_level;							//  Battery level
	uint8_t      	System_Power_State;						//  (Dis)charge state

	uint16_t     	RunTimeRemaining;						//  Run / charge time est.  (Minutes)

	uint8_t      	SatCount;								//  Byte 2 : Current Number of Satellites in use
			   											                  //  Byte 3~4 : DOP(Dilution of Precision) x102
	uint8_t      	SQ_Status;								//  Byte 5 : RTCM corrections received in last 10 seconds, unsigned 8 - bit integer(ranging from 0 to 10)
			   											//  Byte 6 : Status flags :
	uint8_t      	Differential       	  : 1; 				//    Bit 0 : Differential Mode
			   												//      1 = GNSS is being aided with Differential Corrections
	uint8_t      	gpsFixOk              : 1;				//    Bit 1 : Valid Fix
			   												//      1 = Valid
	uint8_t      	Ambiguity             : (3 - 2) + 1;	//    Bit 2~3 : RTK Ambiguity
			         												//      0 = No RTK
			         												//      1 = Float RTK operation
			         												//      2 = Fixed RTK operation
	uint8_t      	Fix                   : (7 - 4) + 1;	//    Bit 4~7 : GNSS Fix Type
															//      0~1 = No Fix
															//      2 = 2D Fix
															//      3 = 3D Fix
															//      4 = GNSS
															//      5 = Fixed Base Mode(aka ‘Time Only’) Fix
															//  Byte 7 : Status flags :
	uint8_t      	INSCoprocessorRunning : (1 - 0) + 1;	//    Bit 0~1 : Factory Use
	uint8_t      	SurveyFailed          : 1;				//    Bit 2 : Survey In Failed          1 = Survey In Operation Failed
	uint8_t      	SurveyPositionValid   : 1;				//    Bit 3 : Survey In Position Valid  1 = Survey In Operation Completed
	uint8_t      	SurveyInProgress      : 1;				//    Bit 4 : Survey In Busy            1 = Survey In Busy
	uint8_t      	HeadingFlag           : 1;				//    Bit 5 : Factory Use
	uint8_t      	PosValid              : 1;				//    Bit 6 : Position Valid            1 = Relative North, East and Down Position is valid
	uint8_t      	ValidTime             : 1;				//    Bit 7 : Valid Time                1 = UTC Time is Valid(Derived from GNSS Time)

	LB_CONFIG_MODE_FLAG_u_t   mode; //  Sensor mode [This struct is at max. overall length of 11 bytes.]
}
__packed
RSP_t;


typedef struct RSP_Portable_s
{
	//TODO: Consider unions for the bits in Bytes 6 & 7

	uint16_t 	MFG_DATA_ID;

	uint8_t  	battery_level;							//  Battery level
	uint8_t  	System_Power_State;						//  (Dis)charge state

	uint16_t 	RunTimeRemaining;						//  Run / charge time est.  (Minutes)

	uint8_t  	SatCount;								//  Byte 2 : Current Number of Satellites in use
	//  Byte 3~4 : DOP(Dilution of Precision) x102
	uint8_t  	SQ_Status;								//  Byte 5 : RTCM corrections received in last 10 seconds, unsigned 8 - bit integer(ranging from 0 to 10)
	//  Byte 6 : Status flags :
	uint8_t  	Differential       	  ;	//	: 1; //    Bit 0 : Differential Mode
	//      1 = GNSS is being aided with Differential Corrections
	uint8_t  	gpsFixOk              ;	//	: 1;				//    Bit 1 : Valid Fix
	//      1 = Valid
	uint8_t  	Ambiguity             ;	//	: (3 - 2) + 1;	//    Bit 2~3 : RTK Ambiguity
	//      0 = No RTK
	//      1 = Float RTK operation
	//      2 = Fixed RTK operation
	uint8_t  	Fix                   ;	//	: (7 - 4) + 1;	//    Bit 4~7 : GNSS Fix Type
	//      0~1 = No Fix
	//      2 = 2D Fix
	//      3 = 3D Fix
	//      4 = GNSS
	//      5 = Fixed Base Mode(aka ‘Time Only’) Fix
	//  Byte 7 : Status flags :
	uint8_t  	INSCoprocessorRunning ;	//	: (1 - 0) + 1;	//    Bit 0~1 : Factory Use
	uint8_t  	SurveyFailed          ;	//	: 1;				//    Bit 2 : Survey In Failed          1 = Survey In Operation Failed
	uint8_t  	SurveyPositionValid   ;	//	: 1;				//    Bit 3 : Survey In Position Valid  1 = Survey In Operation Completed
	uint8_t  	SurveyInProgress      ;	//	: 1;				//    Bit 4 : Survey In Busy            1 = Survey In Busy
	uint8_t  	HeadingFlag           ;	//	: 1;				//    Bit 5 : Factory Use
	uint8_t  	PosValid              ;	//	: 1;				//    Bit 6 : Position Valid            1 = Relative North, East and Down Position is valid
	uint8_t  	ValidTime             ;	//	: 1;				//    Bit 7 : Valid Time                1 = UTC Time is Valid(Derived from GNSS Time)

	uint8_t 	Fixed_Base_Enable  	;	//: 1; 		// If 'false' operate as rover
							//				// If 'true' operate as base
	uint8_t 	Auto_Survey_Enable  ;	//: 1; 		// If 'false' operate as base using provided LLA [check/update this description]
							//				// If 'true' operate as base attempting self survey
	uint8_t 	Connected      	    ;	//: 1; 		// READ ONLY - Ignored on a Write.
							//
	uint8_t 	Correction_Output  	;	//: 1; 		// If 'false' prefer BLE Corrections
							//				// If 'true' prefer Wifi Corrections
							//
	uint8_t 	Aiding_Preference  	;	//: 1; 		// If 'false' prefer NTRIP aiding over a BLE link
							//				// If 'true' prefer Local FIXED BASE RTCM over a BLE link
							//
	uint8_t 	SPARE              	;	//: (8 - 7); 	// Currently Unused bits.
	uint8_t 	Valid_or_Not_Busy 	; 	//: 1; 		// If 'true' on a Read, "Data is Valid" or "We're BUSY".  Ignored on a Write. //TODO: Is "We're BUSY" used or useful?
	uint8_t 	Broadcast_Enable  	; 	//: 1; 		// Broadcast_Enable requires (Fixed_Base_Enable==1)
}
RSP_Portable_t;


typedef struct RSP_MFG_s
{
	uint8_t __packed	AD_Length;
	uint8_t __packed	AD_Type;
	RSP_t	__packed	DATA;
}
RSP_MFG_t;


typedef 	struct RSP_Frame_s
{
	RSP_UUID_t	__packed	UUID;
	RSP_MFG_t	__packed	MFG;
}
RSP_Frame_t;

typedef struct sqgps_relpos_s {
	uint32_t iTOW; /* GPS time of week [ms] */
	int32_t posN; /* Low-Precision Component of Northing [cm] */
	int32_t posE; /* Low-Precision Component of Easting [cm] */
	int32_t posD; /* Low-Precision Component of -Height [cm] */
	int8_t posHpN; /* High-Precision Component of Northing [mm] */
	int8_t posHpE; /* High-Precision Component of Easting [mm] */
	int8_t posHpD; /* High-Precision Component of -Height [mm] */
} sqgps_relpos_t;

typedef struct sqgps_relpos_Portable_s {
	uint32_t iTOW; /* GPS time of week [ms] */
	double	posN; /* Northing [m] */
	double	posE; /* Easting [m] */
	double	posD; /* -Height [m] */
} sqgps_relpos_Portable_t;

typedef 	struct sqgps_lla_s {
	uint32_t 	iTOW; /* GPS time of week [ms] */
	int32_t  	lon; /* Longitude [deg] * 1e-7 */
	int32_t  	lat; /* Latitude  [deg] * 1e-7 */
	int32_t  	height; /* Height above geoid [mm] */
	int8_t   	lonHp; /* Longitude [deg] high precision * 1e-9 */
	int8_t   	latHp; /* Latitude [deg] high precision * 1e-9 */
	int8_t   	heightHp; /* Height about geoid high precision [mm] * 0.1 */
	int8_t   	hMSLHp; /* Height above MSL high precision [mm] * 0.1 */
	uint32_t 	hAcc; /* Horizontal accuracy [mm] * 0.1 */
	uint32_t 	vAcc; /* Vertical accuracy [mm] * 0.1 */
#if defined(ENABLE_LLA_EXTENSION)
	int32_t  	hMSL; /* Height above MSL [mm] */
#endif
} sqgps_lla_t;
	

typedef 	struct sqgps_lla_Portable_s {
	uint32_t 	iTOW; /* GPS time of week [ms] */
    uint32_t    dummy;
    double		lon;	//int32_t  lon; /* Longitude [deg] * 1e-7 */
	double		lat; //int32_t  lat; /* Latitude  [deg] * 1e-7 */
	double		height; //int32_t  height; /* Height above geoid [mm] */
	double		hMSL; //int32_t  hMSL; /* Height above MSL [mm] */
	double		hAcc; //uint32_t hAcc; /* Horizontal accuracy [mm] * 0.1 */
	double		vAcc; //uint32_t vAcc; /* Vertical accuracy [mm] * 0.1 */
} __packed sqgps_lla_Portable_t;

typedef enum MODE_e
{
    MODE_OFFLINE        = 0,  /* GPS receiver is powered off */
    MODE_ACQUIRING      = 1,  /* Acquiring satellites and satellite orbit information */
    MODE_2D             = 2,  /* 2D positioning mode */
    MODE_3D             = 3,  /* 3D positioning mode */
    MODE_RTK_FLOAT      = 4,  /* RTK mode, unresolved integer ambiguity */
    MODE_RTK_FIXED      = 5,  /* RTK mode, high precision */
    MODE_AUTO_SURVEYING = 6,  /* local base mode, auto-surveying base position */
    MODE_FIXED_BASE     = 7,  /* local base mode, active base */
    MODE_UNSUPPORTED    = 8,  /* GPS is in a mode we do not support */ // force (at least 16 bit width)
}
MODE_e_t;

uint8_t MODE_strings [][16] =
{
    "Offline",
    "Acquiring",
    "2D",
    "3D",
    "RTK-float",
    "RTK-fixed",
    "Auto surveying",
    "Fixed base",
    "Unsupported",
};

uint8_t MODE_OFFLINE_string[16] = "Offline";
uint8_t MODE_ACQUIRING_string[16] = "Acquiring";
uint8_t MODE_2D_string[16] = "2D";
uint8_t MODE_3D_string[16] = "3D";
uint8_t MODE_RTK_FLOAT_string[16] = "RTK-float";
uint8_t MODE_RTK_FIXED_string[16] = "RTK-fixed";
uint8_t MODE_AUTO_SURVEYING_string[16] = "Auto surveying";
uint8_t MODE_FIXED_BASE_string[16] = "Fixed base";
uint8_t MODE_UNSUPPORTED_string[16] = "Unsupported";

uint8_t* MODE_pointers [] =
{
    (uint8_t*)&MODE_OFFLINE_string,
    (uint8_t*)&MODE_ACQUIRING_string,
    (uint8_t*)&MODE_2D_string,
    (uint8_t*)&MODE_3D_string,
    (uint8_t*)&MODE_RTK_FLOAT_string,
    (uint8_t*)&MODE_RTK_FIXED_string,
    (uint8_t*)&MODE_AUTO_SURVEYING_string,
    (uint8_t*)&MODE_FIXED_BASE_string,
    (uint8_t*)&MODE_UNSUPPORTED_string,
};

uint8_t* MODE_lookup(uint8_t n);

typedef 	struct sqgps_status_s {
	uint32_t  iTOW; /* GPS time of week [ms] */
	uint16_t  year; /* Year [UTC], or 0 if time unknown */
	uint8_t   month; /* Month [UTC], 1-12 or 0 if unknown */
	uint8_t   day; /* Day [UTC], 1-31 or 0 if unknown */
	uint8_t   hour; /* Hour [UTC], 0-23 0 if unknown */
	uint8_t   min; /* Minute [UTC], 0-59 or 0 if unkown */
	uint8_t   sec; /* Seconds [UTC], 0-59 or 0 if unknown */
	
	/* mode should be one of : 
	 * MODE_OFFLINE, MODE_ACQUIRING, MODE_2D, MODE_3D, MODE_RTK_FLOAT, 
	 * MODE_RTK_FIXED, MODE_AUTO_SURVEYING, MODE_FIXED_BASE, 
	 * MODE_UNSUPPORTED   */
	uint8_t   mode; /* GNSS mode, [not u-blox mode, a mode determined unique to this FW] not to be confused with Sensor mode : LB_CONFIG_MODE_FLAG_u_t __ packed mode; */
	uint8_t   numSV; /* number of satellites used in position solution */
	uint8_t   battery; /* current charge of battery, if any (or 0 if none) */
#if defined(ENABLE_STATUS_EXTENSION)
	RSP_t    RSP;
	//	int8_t  __packed padding[3]; //  Pad length to a multiple of 4 bytes
#endif // defined(ENABLE_STATUS_EXTENSION)
}
__packed
sqgps_status_t;

typedef 	struct sqgps_status_Portable_s {
	uint32_t  iTOW; /* GPS time of week [ms] */

	uint32_t	Time;   //time_t	Time;   //NOTE: time_t is (often) platform dependent sometimes 32 bit sometimes 64 bit.
	//  REFERENCES: https://en.wikipedia.org/wiki/Year_2038_problem#:~:text=Thus%2C%20a%20signed%2032%2Dbit,on%20Tuesday%2C%2019%20January%202038.
	//              https://betterprogramming.pub/the-end-of-unix-time-what-will-happen-1b1a25ec1c20
	
	/* mode should be one of : 
	 * MODE_OFFLINE, MODE_ACQUIRING, MODE_2D, MODE_3D, MODE_RTK_FLOAT, 
	 * MODE_RTK_FIXED, MODE_AUTO_SURVEYING, MODE_FIXED_BASE, 
	 * MODE_UNSUPPORTED   */
	uint8_t   mode; /* GNSS mode, [not u-blox mode, not lb_config_t, a mode determined unique to this FW] not to be confused with Sensor mode : LB_CONFIG_MODE_FLAG_u_t __ packed mode; */
	uint8_t   numSV; /* number of satellites used in position solution */
	uint8_t   battery; /* current charge of battery, if any (or 0 if none) */
	uint8_t   __packed PADDING_1;
#if defined(ENABLE_STATUS_EXTENSION)
	RSP_Portable_t    RSP;
	int8_t  __packed PADDING_2; //  Pad length to a multiple of 4 bytes
#endif // defined(ENABLE_STATUS_EXTENSION)
}
__packed
sqgps_status_Portable_t;


#if 000 //deprecate:
typedef union SQCOPSitePoint_u
{
    sqgps_lla_Portable_t    	lla;
    sqgps_status_Portable_t 	status;
	lb_config_Portable_t		config;
}
SQCOPSitePoint_u_t;
#endif

sqgps_status_Portable_t Init_sqgps_status_Portable_t(sqgps_status_Portable_t *target);
sqgps_relpos_Portable_t Init_sqgps_relpos_Portable_t(sqgps_relpos_Portable_t *target);
sqgps_lla_Portable_t Init_sqgps_lla_Portable_t(sqgps_lla_Portable_t *target);
lb_config_Portable_t Init_lb_config_Portable_t(lb_config_Portable_t *target);

sqgps_status_Portable_t * Pointer_to_status(const uint8_t *FromCOP);
sqgps_lla_Portable_t * Pointer_to_lla(const uint8_t *FromCOP);
lb_config_Portable_t * Pointer_to_config(const uint8_t *FromCOP);

RSP_t * Pointer_to_rsp(const uint8_t *FromCOP);
RSP_t Rsp_from_bytes(const uint8_t bytes[11]);
RSP_Portable_t Rsp_portable_from_bytes(const uint8_t bytes[11]);

sqgps_status_Portable_t SitepointConvertStatusToPortable(sqgps_status_Portable_t *target, const uint8_t *FromCOP);
sqgps_relpos_Portable_t SitepointConvertRelposToPortable(sqgps_relpos_Portable_t *target, const uint8_t *FromCOP);
sqgps_lla_Portable_t SitepointConvertLLAToPortable(sqgps_lla_Portable_t *target, const uint8_t *FromCOP);
lb_config_Portable_t SitepointConvertConfigToPortable(lb_config_Portable_t *target, const uint8_t *FromCOP);

const void *SitepointConvertConfigToCOP(lb_config_Portable_t FromPortable);


#if  ! (defined(__ANDROID__) || defined(__iOS__) )
extern SQ_CopProtocol_Parse_Frame_Context_t	SQ_CopProtocol_Parse_Frame_Context;
#endif



