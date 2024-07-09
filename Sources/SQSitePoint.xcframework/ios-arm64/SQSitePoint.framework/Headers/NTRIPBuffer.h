#pragma once

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
//#include <cstring>

#include <iso646.h>
#include <stdint.h>
#ifdef __FFIGENDART__
    // do not include stdlib.h for FFI gen on Apple platforms
#else
    #include <stdlib.h>
#endif
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


//#define	MAX_SHORT_TEXT_LENGTH	32
//#define	MAX_DESCRIPTION_TEXT_LENGTH	256

typedef enum Error_Status_e
{
//    TODO: Do NOT add 'Error_Status_Unknown' nor 'Error_Status_0' entries into HTTP_Strings[7][3]
//     without addressing hard coded indexing values in source code. Search 'switch (temp)'.
    Error_Status_Unknown   = 0, //  This is explicitly defined to make Java happy. Java doesn't like undefined enums, and we can have this value under certain conditions.
    Error_Status_0   = Error_Status_Unknown,
    Error_Status_200 = 200,
// TODO: To add this value we need to also update HTTP_Strings[7][3].
//       Do NOT add 'Error_Status_400' an entry into HTTP_Strings[7][3] without addressing hard
//       coded indexing values in source code. Search 'switch (temp)'.
//    Error_Status_400 = 400,
    Error_Status_401 = 401,
	Error_Status_404 = 404,
	Error_Status_409 = 409,
	Error_Status_500 = 500,
	Error_Status_501 = 501,
	Error_Status_503 = 503,
}
Error_Status_t;

//TODO: Remember to set defaults in NTRIP_Parse_Init() function;
typedef struct NTRIP_Header_Info_s
{
	Error_Status_t 	Error_Status;
	bool			Authorized;

	uint8_t* Code;
	uint8_t* Short_Text;
	uint8_t* Description;

#ifdef notSWIGJAVA
    char* First_HTTP_Reply;
#else
    uint8_t* First_HTTP_Reply;
#endif
	uint8_t* Authorization;
	uint8_t* Cache_Control;			
	uint8_t* Connection;			
	uint8_t* Content_Length;		
	uint8_t* Content_Type;			
	uint8_t* Date;					
	uint8_t* Host;					
	uint8_t* Server;				
	uint8_t* Pragma;				
	uint8_t* Transfer_Encoding;		
	uint8_t* WWW_Authenticate;		
	uint8_t* Ntrip_Version;			
	uint8_t* Ntrip_Flags;

	//	NOTE: Leave all string buffers same length of 64, which ought to be a symbol/enum/define?  TODO: Do this better?

#ifdef SWIGJAVA
    char Code_string[64];
    char Short_Text_string[64];
    char Description_string[64];

    char First_HTTP_Reply_string[64];
    char Authorization_string[64];		// "Authorization: ",
    char Cache_Control_string[64];		// "Cache-Control: ",
    char Connection_string[64];			// "Connection: ",
    char Content_Length_string[64];		// "Content-Length: ",
    char Content_Type_string[64];		// "Content-Type: ",
    char Date_string[64];				// "Date: ",
    char Host_string[64];				// "Host: ",
    char Server_string[64];				// "Server: ",
    char Pragma_string[64];				// "Pragma: ",
    char Transfer_Encoding_string[64];	// "Transfer-Encoding: ",
    char WWW_Authenticate_string[64];	// "WWW-Authenticate: ",
    char Ntrip_Version_string[64];		// "Ntrip-Version: ",
    char Ntrip_Flags_string[64];		// "Ntrip-Flags: ",
#else
    uint8_t Code_string[64];
	uint8_t Short_Text_string[64];
	uint8_t Description_string[64];

    uint8_t First_HTTP_Reply_string[64];
	uint8_t	Authorization_string[64];		// "Authorization: ",
	uint8_t	Cache_Control_string[64];		// "Cache-Control: ",
	uint8_t	Connection_string[64];			// "Connection: ",
	uint8_t	Content_Length_string[64];		// "Content-Length: ",
	uint8_t	Content_Type_string[64];		// "Content-Type: ",
	uint8_t	Date_string[64];				// "Date: ",
	uint8_t	Host_string[64];				// "Host: ",
	uint8_t	Server_string[64];				// "Server: ",
	uint8_t	Pragma_string[64];				// "Pragma: ",
	uint8_t	Transfer_Encoding_string[64];	// "Transfer-Encoding: ",
	uint8_t	WWW_Authenticate_string[64];	// "WWW-Authenticate: ",
	uint8_t	Ntrip_Version_string[64];		// "Ntrip-Version: ",
	uint8_t	Ntrip_Flags_string[64];			// "Ntrip-Flags: ",
#endif
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

//	bool	raw_mode;	//TODO: This is set but not cleared. not guaranteed valid, see note in ntrip.c
	bool	chunked;	//TODO: Is this set or cleared anywhere?  is it even valid?

	NTRIP_Parse_Return_t	Last_Return_Value;	//DEBUG // NOTE: Mostly for diagnostics/debugging.
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

#ifdef SWIGJAVA
NTRIP_Parse_Return_t	NTRIP_Parse_Init(NTRIP_Parse_Context_t *Context, uint8_t *JavaByteArray, size_t length, NTRIP_Parse_Call_Back_t	*Callback); //NOTE: JavaByteArray is an SQ construct
#else
NTRIP_Parse_Return_t	NTRIP_Parse_Init(NTRIP_Parse_Context_t *Context, uint8_t *WorkingBuffer, size_t length, NTRIP_Parse_Call_Back_t	*Callback);
#endif

// Pass a chunk of data into the Ring Buffer for processing, and a Call Back 
// will be made for each message found.
// Buffer pointer will be invalid on return from Call Back function.  
// Copy data if you need to retain it.
#if defined(__iOS__)
__attribute__((visibility("default"))) __attribute__((used))
#endif
#ifdef SWIGJAVA
NTRIP_Parse_Return_t	NTRIP_Parse(NTRIP_Parse_Context_t *Context, uint8_t *JavaByteArray, size_t length); //NOTE: JavaByteArray is an SQ construct
#else
NTRIP_Parse_Return_t	NTRIP_Parse(NTRIP_Parse_Context_t *Context, uint8_t *Buffer, size_t length);
#endif

// Release_and_Poll API : Release previous message (if any) from 
// Context->WorkingBuffer, search for another message (if any) 
// and update Context->Poll parameter set for new message.
#if defined(__iOS__)
__attribute__((visibility("default"))) __attribute__((used))
#endif
NTRIP_Parse_Return_t	NTRIP_Parse_Next_Message(NTRIP_Parse_Context_t* Context);

