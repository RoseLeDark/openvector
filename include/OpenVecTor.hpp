#ifndef __vector_base_h_
#define __vector_base_h_ 1

#include <KHR/khrplatform.h>

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

typedef int32_t                 ov_sint_t;
typedef uint32_t                ov_uint_t;
typedef int64_t                 ov_slong_t;
typedef uint64_t                ov_ulong_t;
typedef          float          ov_float_t;

#define OPENVECTOR_SUPPORT_INT64   1
#define OPENVECTOR_SUPPORT_FLOAT   1

#elif defined(__sun__) || defined(__digital__)
/*
 * Sun or Digital
 */
typedef int                     ov_sint_t;
typedef unsigned int            ov_uint_t;
typedef          float          ov_float_t;

#if defined(__arch64__) || defined(_LP64)
typedef long int                ov_slong_t;
typedef unsigned long int       ov_ulong_t;
#else
typedef long long int           ov_slong_t;
typedef unsigned long long int  ov_ulong_t;
#endif /* __arch64__ */

#define OPENVECTOR_SUPPORT_INT64   1
#define OPENVECTOR_SUPPORT_FLOAT   1


#elif defined(_WIN32) && !defined(__SCITECH_SNAP__)
/*
 * Win32
 */
typedef __int32                 ov_sint_t;
typedef unsigned __int32        ov_uint_t;
typedef __int64                 ov_slong_t;
typedef unsigned __int64        ov_ulong_t;
typedef          float          ov_float_t;
#define OPENVECTOR_SUPPORT_INT64   1
#define OPENVECTOR_SUPPORT_FLOAT   1

#else
#include <stdint.h>

typedef int32_t                 ov_sint_t;
typedef uint32_t                ov_uint_t;

#define OPENVECTOR_SUPPORT_INT64   0
#define OPENVECTOR_SUPPORT_FLOAT   0
#endif

typedef signed   char          ov_schar_t;
typedef unsigned char          ov_uchar_t;
typedef signed   short int     ov_sshort_t;
typedef unsigned short int     ov_ushort_t;
typedef intptr_t               ov_intptr_t;
typedef uintptr_t              ov_uintptr_t;

typedef enum {
    OV_FALSE = 0,
    OV_TRUE  = 1,
} ov_boolean_t;

#if __cplusplus >= 201703L
# define CL_HPP_DEFINE_STATIC_MEMBER_ inline
#elif defined(_MSC_VER)
# define CL_HPP_DEFINE_STATIC_MEMBER_ __declspec(selectany)
#elif defined(__MINGW32__)
# define CL_HPP_DEFINE_STATIC_MEMBER_ __attribute__((selectany))
#else
# define CL_HPP_DEFINE_STATIC_MEMBER_ __attribute__((weak))
#endif // !_MSC_VER


#define VECTOR_VERSION 010000
#define VECTOR_VERSION_MAJOR    1
#define VECTOR_VERSION_MINOR    0
#define VECTOR_VERSION_PATCH    0

#ifndef VECTOR_VERSION_1_0
#define VECTOR_VERSION_1_0 1

typedef const char* (APIENTRYP PFNOPENVECTORVERSIONPROC) (void);

VECTORAPI const char* APIENTRY openvector_version (void);
#endif



#ifdef __cplusplus
}
#endif

#endif // __vector_base_h_