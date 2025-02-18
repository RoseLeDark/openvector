//  SPDX-FileCopyrightText: 2025 Amber-Sophia Schröck 
//  SPDX-License-Identifier: MIT


#ifndef __vector_base_h_
#define __vector_base_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
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

#if defined(OPENVECTOR_STATIC)
#   define OPENVECTOR_PUBLICAPI
#elif defined(_WIN32)
#   define OPENVECTOR_PUBLICAPI __declspec(dllimport)
#elif defined (__SYMBIAN32__)
#   define OPENVECTOR_PUBLICAPI IMPORT_C
#elif defined(__ANDROID__)
#   define OPENVECTOR_PUBLICAPI __attribute__((visibility("default")))
#else
#   define OPENVECTOR_PUBLICAPI
#endif

#if defined(_WIN32) && !defined(_WIN32_WCE) && !defined(__SCITECH_SNAP__)
    /* Win32 but not WinCE */
#   define OPENVECTOR_APIENTRY __stdcall
#else
#   define OPENVECTOR_APIENTRY
#endif

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__) || defined(__SCO__) || defined(__USLC__)
// Linux
#include <stdint.h>
#include <stddef.h>

typedef int32_t                 ovt_sint_t;
typedef uint32_t                ovt_uint_t;
typedef int64_t                 ovt_slong_t;
typedef uint64_t                ovt_ulong_t;
typedef float                   ovt_float_t;

#define OPENVECTOR_SUPPORT_INT64   1
#define OPENVECTOR_SUPPORT_FLOAT   1

#elif defined(__sun__) || defined(__digital__)
/*
 * Sun or Digital
 */
typedef int                     ovt_sint_t;
typedef unsigned int            ovt_uint_t;
typedef          float          ovt_float_t;

#if defined(__arch64__) || defined(_LP64)
typedef long int                ovt_slong_t;
typedef unsigned long int       ovt_ulong_t;
#else
typedef long long int           ovt_slong_t;
typedef unsigned long long int  ovt_ulong_t;
#endif /* __arch64__ */

#define OPENVECTOR_SUPPORT_INT64   1
#define OPENVECTOR_SUPPORT_FLOAT   1


#elif defined(_WIN32) && !defined(__SCITECH_SNAP__)
/*
 * Win32
 */
typedef __int32                 ovt_sint_t;
typedef unsigned __int32        ovt_uint_t;
typedef __int64                 ovt_slong_t;
typedef unsigned __int64        ovt_ulong_t;
typedef          float          ovt_float_t;
#define OPENVECTOR_SUPPORT_INT64   1
#define OPENVECTOR_SUPPORT_FLOAT   1

#else
#include <stdint.h>

typedef int32_t                 ovt_sint_t;
typedef uint32_t                ovt_uint_t;

#define OPENVECTOR_SUPPORT_INT64   0
#define OPENVECTOR_SUPPORT_FLOAT   0
#endif

typedef size_t                 ovt_size_t;
typedef signed   char          ovt_schar_t;
typedef unsigned char          ovt_uchar_t;
typedef signed   short int     ovt_sshort_t;
typedef unsigned short int     ovt_ushort_t;
typedef intptr_t               ovt_intptr_t;
typedef uintptr_t              ovt_uintptr_t;
typedef void                   ovt_void_t;
typedef void*                  ovt_pointer_t;
typedef const char*            ovt_string_t;

typedef enum {
    OVT_FALSE = 0,
    OVT_TRUE  = 1,
} ovt_bool_t;

#if __cplusplus >= 201703L
# define CL_HPP_DEFINE_STATIC_MEMBER_ inline
#elif defined(_MSC_VER)
# define CL_HPP_DEFINE_STATIC_MEMBER_ __declspec(selectany)
#elif defined(__MINGW32__)
# define CL_HPP_DEFINE_STATIC_MEMBER_ __attribute__((selectany))
#else
# define CL_HPP_DEFINE_STATIC_MEMBER_ __attribute__((weak))
#endif // !_MSC_VER

#define OVECTOR_VERSION_MAJOR    1
#define OVECTOR_VERSION_MINOR    0
#define OVECTOR_VERSION_PATCH    0

#define OVECTOR_VERSION          ((OVECTOR_VERSION_MAJOR << 16) | (OVECTOR_VERSION_MINOR << 8) | OVECTOR_VERSION_PATCH)

// Kombiniere die Version als String
#define ___STRINGIFY(x) #x
#define OVECTOR_TOSTRING(x) ___STRINGIFY(x)

#define OVECTOR_VERSION_STRING    OVECTOR_TOSTRING(OVECTOR_VERSION_MAJOR) "." OVECTOR_TOSTRING(OVECTOR_VERSION_MINOR) "." OVECTOR_TOSTRING(OVECTOR_VERSION_PATCH)

#ifndef OVECTOR_VERSION_1_0
#define OVECTOR_VERSION_1_0 1


typedef const char* (APIENTRYP PFNOVTGETVERSIONSTRINGPROC) (void);
typedef ovt_uint_t   (APIENTRYP PFNOVTGETVERSIONPROC) (void);

VECTORAPI const char* APIENTRY ovt_get_version_string (void);
VECTORAPI ovt_uint_t APIENTRY ovt_get_version(void);

#endif

#define OVECTOR_VERSION_1_1 0



#ifdef __cplusplus
}
#endif

#include "OVTfasttype.h"

#endif // __vector_base_h_