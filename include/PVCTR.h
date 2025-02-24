//  SPDX-FileCopyrightText: 2025 Amber-Sophia Schröck 
//  SPDX-License-Identifier: MIT


#ifndef __vector_base_h_
#define __vector_base_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

#include "internal/PVCTRplatform.h"
#include "PVCTRerror.h"

#if (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_WINDOWS) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif
#ifndef VECTORAPI
#define VECTORAPI extern
#endif

#if defined(PVCTR_STATIC)
#   define PVCTR_PUBLICAPI
#elif (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_WINDOWS)
#   define PVCTR_PUBLICAPI __declspec(dllimport)
#elif defined (__SYMBIAN32__)
#   define PVCTR_PUBLICAPI IMPORT_C
#elif (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_ANDROID)
#   define PVCTR_PUBLICAPI __attribute__((visibility("default")))
#else
#   define PVCTR_PUBLICAPI
#endif



#if (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_WINDOWS) && !defined(_WIN32_WCE) && !defined(__SCITECH_SNAP__)
    /* Win32 but not WinCE */
#   define PVCTR_APIENTRY __stdcall
#else
#   define PVCTR_APIENTRY
#endif

#if (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_LINUX)
// Linux
#include <stdint.h>
#include <stddef.h> 
#include <limits.h>



#elif (PVCTR_ARCH == PVCTR_ARCH_ARM)
/*
 * Sun or Digital
 */
typedef int                     pvr_sint_t;
typedef unsigned int            pvr_uint_t;
typedef          float          pvr_float_t;

typedef long                    pvr_slong_t;
typedef unsigned long           pvr_ulong_t;


#elif (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_WINDOWS) && !defined(__SCITECH_SNAP__)
/*
 * Win32
 */
typedef __int32                 pvr_sint_t;
typedef unsigned __int32        pvr_uint_t;
typedef __int64                 pvr_slong_t;
typedef unsigned __int64        pvr_ulong_t;
typedef          float          pvr_float_t;

#else
#include <stdint.h>
#include <stddef.h> 
#include <limits.h>

typedef int32_t                 pvr_sint_t;
typedef uint32_t                pvr_uint_t;

#define PVCTR_SUPPORT_INT64   0
#define PVCTR_SUPPORT_FLOAT   0
#endif

typedef size_t                 pvr_size_t;
typedef signed   char          pvr_schar_t;
typedef unsigned char          pvr_uchar_t;
typedef signed   short int     pvr_sshort_t;
typedef unsigned short int     pvr_ushort_t;
typedef intptr_t               pvr_intptr_t;
typedef uintptr_t              pvr_uintptr_t;
typedef void                   pvr_void_t;
typedef void*                  pvr_pointer_t;
typedef const char*            pvr_string_t;
typedef size_t                 pvr_size_t;

typedef float                   pvr_float_t;
typedef double                  pvr_double_t;
typedef int32_t                 pvr_sint_t;
typedef uint32_t                pvr_uint_t;
typedef int64_t                 pvr_slong_t;
typedef uint64_t                pvr_ulong_t;

typedef enum {
    PVR_FALSE = 0,
    PVR_TRUE  = 1,
} pvr_bool_t;


#define PVCTR_VERSION_MAJOR    1
#define PVCTR_VERSION_MINOR    0
#define PVCTR_VERSION_PATCH    0

#define PVCTR_VERSION          ((PVCTR_VERSION_MAJOR << 16) | (PVCTR_VERSION_MINOR << 8) | PVCTR_VERSION_PATCH)

// Kombiniere die Version als String
#define PVCTR_STRINGIFY(x) #x
#define PVCTR_TOSTRING(x) PVCTR_STRINGIFY(x)

#define PVCTR_VERSION_STRING    PVCTR_TOSTRING(PVCTR_VERSION_MAJOR) "." PVCTR_TOSTRING(PVCTR_VERSION_MINOR) "." PVCTR_TOSTRING(PVCTR_VERSION_PATCH)

#ifndef PVCTR_VERSION_1_0
#define PVCTR_VERSION_1_0 1


typedef pvr_string_t (APIENTRYP PFPVRGETVERSIONSTRINGPROC) (void);
typedef pvr_uint_t   (APIENTRYP PFPVRGETVERSIONPROC) (void);

VECTORAPI pvr_string_t APIENTRY pvr_get_version_string (void);
VECTORAPI pvr_uint_t APIENTRY pvr_get_version(void);

#endif

#define PVCTR_VERSION_1_1 0

typedef struct { 
    pvr_uint_t using_techniq;
    pvr_uchar_t alignas_size; 
} pvr_context_t; // platzhalter

#ifdef __cplusplus
}
#endif

#include "PVCTRfasttype.h"

#endif // __vector_base_h_