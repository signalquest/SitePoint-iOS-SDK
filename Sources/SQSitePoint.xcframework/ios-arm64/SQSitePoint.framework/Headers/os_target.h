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
**  File:     os_target.h
**  Purpose:  OS-specific attribute macros
**
*******************************************************************************/

#ifndef __OS_TARGET_H__
#define __OS_TARGET_H__

#if     _WIN64                                  //  64-bit Windows

#define ENUM_ATTR

#define FUNC_ATTR

#define PACKED_ATTR   __attribute__((packed))

#elif   _WIN32                                  //  32-bit Windows

#define ENUM_ATTR

#define FUNC_ATTR

#define PACKED_ATTR   __attribute__((packed))

#elif   __APPLE__                               //  Any Apple device
  #include "TargetConditionals.h"
  #if TARGET_OS_IPHONE && TARGET_OS_SIMULATOR   //  iPhone simulators

//  The below attribute makes it so that enum members can be accessed by name in
//  Swift (enum_type.ENUM_MEMBER). Without this, enum members are treated like
//  constants (ENUM_MEMBER) whose names could conflict with other code elements
//  in Swift.
#define ENUM_ATTR     __attribute__((enum_extensibility(closed)))
//  The below attributes make it so that functions that will be built into a
//  dynamic library are not removed due to a lack of reference.
#define FUNC_ATTR     __attribute__((visibility("default"))) __attribute__((used))

#define PACKED_ATTR   __attribute__((packed))

  #elif TARGET_OS_IPHONE                        //  iPhone

//  The below attribute makes it so that enum members can be accessed by name in
//  Swift (enum_type.ENUM_MEMBER). Without this, enum members are treated like
//  constants (ENUM_MEMBER) whose names could conflict with other code elements
//  in Swift.
#define ENUM_ATTR     __attribute__((enum_extensibility(closed)))
//  The below attributes make it so that functions that will be built into a
//  dynamic library are not removed due to a lack of reference.
#define FUNC_ATTR     __attribute__((visibility("default"))) __attribute__((used))

#define PACKED_ATTR   __attribute__((packed))

  #else                                         //  Everything else is a Mac

#define ENUM_ATTR

#define FUNC_ATTR

#define PACKED_ATTR   __attribute__((packed))

  #endif
#elif   __ANDROID__                             //  Android phones

#define ENUM_ATTR

#define FUNC_ATTR

#define PACKED_ATTR   __attribute__((packed))

#elif   __linux                                 //  Linux

#define ENUM_ATTR

#define FUNC_ATTR

#define PACKED_ATTR   __attribute__((packed))

#elif   __unix                                  //  Unix

#define ENUM_ATTR

#define FUNC_ATTR

#define PACKED_ATTR   __attribute__((packed))

#elif   __posix                                 //  generically POSIX-compliant

#define ENUM_ATTR

#define FUNC_ATTR

#define PACKED_ATTR   __attribute__((packed))

#else                                           //  Everything else

#define ENUM_ATTR

#define FUNC_ATTR

#define PACKED_ATTR   __attribute__((packed))

#endif

#endif