#pragma once

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>

#include <iso646.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum	NTRIP_Parse_Return_e
{
	// ERRORS are negative, 
	// Normal Statuses are >= 0
	
	// Errors and Problems
	NTRIP_BAD_HEADER = -13,
	NTRIP_UNEXPECTED_CALLBACK_FUNCTION = -12,
	NTRIP_UNKNOWN_ERROR = -11,
	NTRIP_NO_CONTEXT = -10,
	NTRIP_BUFFER_OVERRUN = -9,
	NTRIP_BAD_CRC24Q = -8,
	NTRIP_BUFFER_TOO_SMALL = -7,
	NTRIP_BAD_PREAMBLE = -6,
	NTRIP_NO_BUFFER = -5,
	NTRIP_NO_CALLBACK = -4,
	NTRIP_NOT_ENOUGH_ROOM = -3,
	NTRIP_FULL = -2,
	NTRIP_NOT_INITIALIZED = -1,

	// Successful Operations
	NTRIP_SUCCESS = 0,
	NTRIP_MESSAGE_PENDING = 1,
	NTRIP_NO_MESSAGE_PENDING,
	NTRIP_INCOMPLETE_MESSAGE_PENDING,
	NTRIP_USE_EXISTING_BUFFER,
	NTRIP_USE_EXISTING_CALLBACK,
	NTRIP_USE_EXISTING_BUFFER_AND_CALLBACK,
}
NTRIP_Parse_Return_t;


typedef enum	NTRIP_Parse_Types_e
{
	NTRIP_RTCM_Message = 0, 
	NTRIP_V1_Header_Message = 1,
	NTRIP_V2_Header_Message = 2,
}
NTRIP_Parse_Types_t;


typedef	enum	NTRIP_Parse_Context_State_e
{
	NTRIP_INIT	=	0,

	  NTRIP_WAIT_FOR_BUFFER
	, NTRIP_WAIT_FOR_HEADER_START
	, NTRIP_WAIT_FOR_HEADER_END
	, NTRIP_WAIT_FOR_CHUNK_HEADER
	, NTRIP_WAIT_FOR_CHUNK_END
	, NTRIP_WAIT_FOR_ONE_OR_MORE_RTCM_FRAMES
	, NTRIP_WORK_THROUGH_CHUNK
}
NTRIP_Parse_Context_State_t;

typedef struct NTRIP_Parse_Poll_s
{
	NTRIP_Parse_Return_t Status;
	NTRIP_Parse_Types_t type;
	uint8_t* Buffer;
	size_t Length;
}
NTRIP_Parse_Poll_t;

typedef enum Error_Status_e
{
	Error_Status_200 = 200,
	Error_Status_401 = 401,
	Error_Status_404 = 404,
	Error_Status_409 = 409,
	Error_Status_500 = 500,
	Error_Status_501 = 501,
	Error_Status_503 = 503,
}
Error_Status_t;

typedef struct NTRIP_Header_Info_s
{
	Error_Status_t 	Error_Status;
	bool			Authorized;

	uint8_t* Code;
	uint8_t* Short_Text;
	uint8_t* Description;

	uint8_t* Authorization;
	uint8_t* Cache_Control;
	uint8_t* Connection;
	uint8_t* Content_Length;
	uint8_t* Content_Type;
	uint8_t* Date;
	uint8_t* First_HTTP_Reply;
	uint8_t* Host;
	uint8_t* Server;
	uint8_t* Pragma;
	uint8_t* Transfer_Encoding;
	uint8_t* WWW_Authenticate;
	uint8_t* Ntrip_Version;
	uint8_t* Ntrip_Flags;

	uint8_t Code_string[64];
	uint8_t Short_Text_string[64];
	uint8_t Description_string[64];

	uint8_t	Authorization_string[64];      // "Authorization: ",
	uint8_t	Cache_Control_string[64];      // "Cache-Control: ",
	uint8_t	Connection_string[64];         // "Connection: ",
	uint8_t	Content_Length_string[64];     // "Content-Length: ",
	uint8_t	Content_Type_string[64];       // "Content-Type: ",
	uint8_t	Date_string[64];               // "Date: ",
	uint8_t First_HTTP_Reply_string[64];
	uint8_t	Host_string[64];               // "Host: ",
	uint8_t	Server_string[64];             // "Server: ",
	uint8_t	Pragma_string[64];             // "Pragma: ",
	uint8_t	Transfer_Encoding_string[64];  // "Transfer-Encoding: ",
	uint8_t	WWW_Authenticate_string[64];   // "WWW-Authenticate: ",
	uint8_t	Ntrip_Version_string[64];      // "Ntrip-Version: ",
	uint8_t	Ntrip_Flags_string[64];        // "Ntrip-Flags: ",
}
NTRIP_Header_Info_t;

//	Prototype for a Call Back function
typedef void	NTRIP_Parse_Call_Back_t(NTRIP_Parse_Return_t Status, NTRIP_Parse_Types_t type, uint8_t* Buffer, size_t Length);

typedef enum NTRIP_Version_e
{
	NTRIP_VERSION_UNKNOWN = 0,
	NTRIP_VERSION_1,
	NTRIP_VERSION_2,

	NTRIP_V1 = NTRIP_VERSION_1,
	NTRIP_V2 = NTRIP_VERSION_2,
}
NTRIP_Version_t;

typedef	struct	NTRIP_Parse_Context_s
{
	NTRIP_Parse_Call_Back_t* CallBack;

	uint8_t* WorkingBuffer;
	size_t Length;

	NTRIP_Parse_Context_State_t	State;
	NTRIP_Parse_Context_State_t	Last_State;	//DEBUG

	//-------------------

	uint8_t* Head;
	uint8_t* Tail;
	uint8_t* Wptr;
	uint8_t* Bptr;

	uint8_t* End_of_Chunk;

	int	Count;
	int	Free;

	int	ChunkSize;

	bool	chunked;

	NTRIP_Parse_Return_t	Last_Return_Value;
	NTRIP_Version_t			NTRIP_Version;

	NTRIP_Parse_Poll_t	Poll;
	NTRIP_Header_Info_t	Header;
}
NTRIP_Parse_Context_t;


// Initialize and/or Re-Initialize an NTRIP_Parse_Context_t and assign a 
// predefined Working Buffer.
// Working Buffer should be (at least) 2x the size of largest chunk (message) 
// we expect to receive on the link to the NTRIP server.
// Use previously assigned Working Buffer if NULL is passed. (Ignore length.)
// Use previously assigned Callback if NULL is passed.
#if defined(__iOS__)
__attribute__((visibility("default"))) __attribute__((used))
#endif
NTRIP_Parse_Return_t	NTRIP_Parse_Init(NTRIP_Parse_Context_t *Context, uint8_t *WorkingBuffer, size_t length, NTRIP_Parse_Call_Back_t	*Callback);


// Pass a chunk of data into the Ring Buffer for processing, and a Call Back 
// will be made for each message found.
// Buffer pointer will be invalid on return from Call Back function.  
// Copy data if you need to retain it.
#if defined(__iOS__)
__attribute__((visibility("default"))) __attribute__((used))
#endif
NTRIP_Parse_Return_t	NTRIP_Parse(NTRIP_Parse_Context_t *Context, uint8_t *Buffer, size_t length);


// Release_and_Poll API : Release previous message (if any) from 
// Context->WorkingBuffer, search for another message (if any) 
// and update Context->Poll parameter set for new message.
#if defined(__iOS__)
__attribute__((visibility("default"))) __attribute__((used))
#endif
NTRIP_Parse_Return_t	NTRIP_Parse_Next_Message(NTRIP_Parse_Context_t* Context);

