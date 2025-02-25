//  SPDX-FileCopyrightText: 2025 Amber-Sophia Schröck 
//  SPDX-License-Identifier: MIT


#ifndef __vector_base_h_
#define __vector_base_h_ 1



#include "PVCTRplatform.h"

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

#define PVCTR_VERSION_MAJOR    1
#define PVCTR_VERSION_MINOR    0
#define PVCTR_VERSION_PATCH    0

#define PVCTR_VERSION          ((PVCTR_VERSION_MAJOR << 16) | (PVCTR_VERSION_MINOR << 8) | PVCTR_VERSION_PATCH)

// Kombiniere die Version als String
#define PVCTR_STRINGIFY(x) #x
#define PVCTR_TOSTRING(x) PVCTR_STRINGIFY(x)

#define PVCTR_VERSION_STRING    PVCTR_TOSTRING(PVCTR_VERSION_MAJOR) "." PVCTR_TOSTRING(PVCTR_VERSION_MINOR) "." PVCTR_TOSTRING(PVCTR_VERSION_PATCH)

#define PVCTR_VERSION_1_0 1

#if (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_LINUX)
// Linux
#include <stdint.h>
#include <stddef.h> 
#include <limits.h>

#define PVCTR_APIENTRY

#elif (PVCTR_ARCH == PVCTR_ARCH_ARM)

#include <stdint.h>
#include <stddef.h> 
#include <limits.h>

#define PVCTR_APIENTRY
#define PVCTR_PUBLICAPI

#if (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_ANDROID)
#define PVCTR_PUBLICAPI __attribute__((visibility("default")))
#else
#define PVCTR_PUBLICAPI
#endif

#elif (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_WINDOWS) && !defined(__SCITECH_SNAP__) && !defined(_WIN32_WCE)
/*
 * Win32
 */

#if defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif
#include <stddef.h> 
#include <limits.h>


#define PVCTR_APIENTRY __stdcall
#define PVCTR_PUBLICAPI __declspec(dllimport)

#elif (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_ANDROID)
#define PVCTR_PUBLICAPI __attribute__((visibility("default")))
#define PVCTR_APIENTRY __stdcall
#else

#include <stdint.h>
#include <stddef.h> 
#include <limits.h>

#define PVCTR_APIENTRY
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Datatypes
 */
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

/*
 * ERRORS
 */
#define PVCTR_OK                    0
#define PVCTR_ERROR_OUTOFMEM        1
#define PVCTR_ERROR_NULL_PTR        2
#define PVCTR_ERROR_INVALID_ARG     3
#define PVCTR_ERROR_LISTFULL        4
#define PVCTR_ERROR_NSUPPORT        5

#define PVCTR_get_proc_address 1
#define PVCTR_technic_add 1
#define PVCTR_technic_get 1
#define PVCTR_technic_user 1

/*
 * struct context
 */
typedef struct pvr_context pvr_context_t;

/*
 * vector
 */
typedef struct { union { struct { pvr_schar_t x, y; };  pvr_schar_t e[2]; }; }                      pvr_vec2c; 
typedef struct { union { struct { pvr_schar_t x, y, z; };  pvr_schar_t e[3]; }; }                   pvr_vec3c; 
typedef struct { union { struct { pvr_schar_t x, y, z, w; };  pvr_schar_t e[4]; }; }                pvr_vec4c; 
typedef struct { union { struct { pvr_schar_t x, y, z, w, a, b, c, d; };  pvr_schar_t e[8]; }; }    pvr_vec8c; 
typedef struct { union { struct { pvr_uchar_t x, y; };  pvr_uchar_t e[2]; }; }                      pvr_vec2uc; 
typedef struct { union { struct { pvr_uchar_t x, y, z; };  pvr_uchar_t e[3]; }; }                   pvr_vec3uc; 
typedef struct { union { struct { pvr_uchar_t x, y, z, w; };  pvr_uchar_t e[4]; }; }                pvr_vec4uc; 
typedef struct { union { struct { pvr_uchar_t x, y, z, w, a, b, c, d; };  pvr_uchar_t e[8]; }; }    pvr_vec8uc; 

typedef struct { union { struct { pvr_sshort_t x, y; };  pvr_sshort_t e[2]; }; }                    pvr_vec2s; 
typedef struct { union { struct { pvr_sshort_t x, y, z; };  pvr_sshort_t e[3]; }; }                 pvr_vec3s; 
typedef struct { union { struct { pvr_sshort_t x, y, z, w; };  pvr_sshort_t e[4]; }; }              pvr_vec4s; 
typedef struct { union { struct { pvr_sshort_t x, y, z, w, a, b, c, d; };  pvr_sshort_t e[8]; }; }  pvr_vec8s; 
typedef struct { union { struct { pvr_ushort_t x, y; };  pvr_ushort_t e[2]; }; }                    pvr_vec2us; 
typedef struct { union { struct { pvr_ushort_t x, y, z; };  pvr_ushort_t e[3]; }; }                 pvr_vec3us; 
typedef struct { union { struct { pvr_ushort_t x, y, z, w; };  pvr_ushort_t e[4]; }; }              pvr_vec4us; 
typedef struct { union { struct { pvr_ushort_t x, y, z, w, a, b, c, d; };  pvr_ushort_t e[8]; }; }  pvr_vec8us; 

typedef struct { union { struct { pvr_sint_t x, y; };  pvr_sint_t e[2]; }; }                        pvr_vec2i; 
typedef struct { union { struct { pvr_sint_t x, y, z; };  pvr_sint_t e[3]; }; }                     pvr_vec3i; 
typedef struct { union { struct { pvr_sint_t x, y, z, w; };  pvr_sint_t e[4]; }; }                  pvr_vec4i; 
typedef struct { union { struct { pvr_sint_t x, y, z, w, a, b, c, d; };  pvr_uint_t e[8]; }; }      pvr_vec8i; 
typedef struct { union { struct { pvr_uint_t x, y; };  pvr_uint_t e[2]; }; }                        pvr_vec2ui; 
typedef struct { union { struct { pvr_uint_t x, y, z; };  pvr_uint_t e[3]; }; }                     pvr_vec3ui; 
typedef struct { union { struct { pvr_uint_t x, y, z, w; };  pvr_uint_t e[4]; }; }                  pvr_vec4ui; 
typedef struct { union { struct { pvr_uint_t x, y, z, w, a, b, c, d; };  pvr_uint_t e[8]; }; }      pvr_vec8ui; 

typedef struct { union { struct { pvr_slong_t x, y; };  pvr_slong_t e[2]; }; }                      pvr_vec2l; 
typedef struct { union { struct { pvr_slong_t x, y, z; };  pvr_slong_t e[3]; }; }                   pvr_vec3l; 
typedef struct { union { struct { pvr_slong_t x, y, z, w; };  pvr_slong_t e[4]; }; }                pvr_vec4l; 
typedef struct { union { struct { pvr_slong_t x, y, z, w, a, b, c, d; };  pvr_slong_t e[8]; }; }    pvr_vec8l; 
typedef struct { union { struct { pvr_ulong_t x, y; };  pvr_ulong_t e[2]; }; }                      pvr_vec2ul; 
typedef struct { union { struct { pvr_ulong_t x, y, z; };  pvr_ulong_t e[3]; }; }                   pvr_vec3ul; 
typedef struct { union { struct { pvr_ulong_t x, y, z, w; };  pvr_ulong_t e[4]; }; }                pvr_vec4ul; 
typedef struct { union { struct { pvr_ulong_t x, y, z, w, a, b, c, d; };  pvr_ulong_t e[8]; }; }    pvr_vec8ul; 

typedef struct { union { struct { pvr_float_t x, y; };  pvr_float_t e[2]; }; }                      pvr_vec2f; 
typedef struct { union { struct { pvr_float_t x, y, z; };  pvr_float_t e[3]; }; }                   pvr_vec3f; 
typedef struct { union { struct { pvr_float_t x, y, z, w; };  pvr_float_t e[4]; }; }                pvr_vec4f; 
typedef struct { union { struct { pvr_float_t x, y, z, w, a, b, c, d; };  pvr_float_t e[8]; }; }    pvr_vec8f; 
typedef struct { union { struct { pvr_double_t x, y; };  pvr_double_t e[2]; }; }                    pvr_vec2d; 
typedef struct { union { struct { pvr_double_t x, y, z; };  pvr_double_t e[3]; }; }                 pvr_vec3d; 
typedef struct { union { struct { pvr_double_t x, y, z, w; };  pvr_double_t e[4]; }; }              pvr_vec4d; 
typedef struct { union { struct { pvr_double_t x, y, z, w, a, b, c, d; };  pvr_double_t e[8]; }; }  pvr_vec8d; 

typedef struct { union { struct { pvr_uchar_t r, g, b, a; };  pvr_uchar_t e[4]; }; }                pvr_rgbac;
typedef struct { union { struct { pvr_float_t r, g, b, a; };  pvr_float_t e[4]; }; }                pvr_rgbaf;

typedef struct { union { struct { pvr_float_t x, y, w, h; };  pvr_float_t e[4]; }; }                pvr_rect;

typedef struct { 
    union { struct { pvr_float_t m11, m12, m21, m22; };  pvr_float_t e[4]; }; 
} pvr_mat2x2f;

typedef struct { 
    union { struct { pvr_float_t m11, m12, m13, m21, m22, m23; };  pvr_float_t e[6]; }; 
} pvr_mat2x3f;

typedef struct { 
    union { struct { pvr_float_t m11, m12, m13, m14, m21, m22, m23, m24; };  pvr_float_t e[8]; }; 
} pvr_mat2x4f;

typedef struct { 
    union { struct { pvr_float_t m11, m12, m21, m22, m31, m32; };  pvr_float_t e[6]; }; 
} pvr_mat3x2f;

typedef struct { 
    union { struct { pvr_float_t m11, m12, m13, m21, m22, m23, m31, m32, m33; };  pvr_float_t e[9]; }; 
} pvr_mat3x3f;

typedef struct { 
    union { struct { pvr_float_t m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34; };  pvr_float_t e[12]; }; 
} pvr_mat3x4f;

typedef struct { 
    union { struct { pvr_float_t m11, m12, m21, m22, m31, m32, m41, m42; };  pvr_float_t e[8]; }; 
} pvr_mat4x2f;

typedef struct { 
    union { struct { pvr_float_t m11, m12, m13, m21, m22, m23, m31, m32, m33, m41, m42, m43; };  pvr_float_t e[12]; }; 
} pvr_mat4x3f;

typedef struct { 
    union { struct { pvr_float_t m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44; };  pvr_float_t e[16]; }; 
} pvr_mat4x4f;

typedef struct { 
    union { struct { pvr_double_t m11, m12, m21, m22; };  pvr_float_t e[4]; }; 
} pvr_mat2x2d;

typedef struct { 
    union { struct { pvr_double_t m11, m12, m13, m21, m22, m23; };  pvr_double_t e[6]; }; 
} pvr_mat2x3d;

typedef struct { 
    union { struct { pvr_double_t m11, m12, m13, m14, m21, m22, m23, m24; };  pvr_double_t e[8]; }; 
} pvr_mat2x4d;

typedef struct { 
    union { struct { pvr_double_t m11, m12, m21, m22, m31, m32; };  pvr_double_t e[6]; }; 
} pvr_mat3x2d;

typedef struct { 
    union { struct { pvr_double_t m11, m12, m13, m21, m22, m23, m31, m32, m33; };  pvr_double_t e[9]; }; 
} pvr_mat3x3d;

typedef struct { 
    union { struct { pvr_double_t m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34; };  pvr_double_t e[12]; }; 
} pvr_mat3x4d;

typedef struct { 
    union { struct { pvr_double_t m11, m12, m21, m22, m31, m32, m41, m42; };  pvr_double_t e[8]; }; 
} pvr_mat4x2d;

typedef struct { 
    union { struct { pvr_double_t m11, m12, m13, m21, m22, m23, m31, m32, m33, m41, m42, m43; };  pvr_double_t e[12]; }; 
} pvr_mat4x3d;

typedef struct { 
    union { struct { pvr_double_t m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44; };  pvr_double_t e[16]; }; 
} pvr_mat4x4d;

/*
 * Functions
 */
typedef pvr_pointer_t (pvr_techniq_func)(pvr_string_t funcName);

typedef pvr_string_t (APIENTRYP PFPVRGETVERSIONSTRINGPROC) (void);
typedef pvr_uint_t   (APIENTRYP PFPVRGETVERSIONPROC) (void);
typedef pvr_schar_t (APIENTRYP PFPVRTECHNIQADDPROC)(pvr_string_t technic_name, pvr_techniq_func* getfunc);
typedef pvr_bool_t (APIENTRYP PFPVRTECHNIQAVAIBLEPROC)(pvr_string_t technic_name);
typedef pvr_bool_t (APIENTRYP PFPVRTECHNIQUNSETPROC)(pvr_string_t technic_name);
typedef pvr_techniq_func* (APIENTRYP PFPVRTECHNIQGETPROC)(pvr_string_t technic_name);
typedef pvr_pointer_t (APIENTRYP PFPVRGETTECNICGETFUNCPROC)(pvr_string_t technic_name, pvr_string_t funcName);
typedef pvr_schar_t (APIENTRYP PFPVRPVRMAININITFUNCPROC)(int argc, char *argv[]); 

typedef void (*pvr_funcptr)(void);
VECTORAPI pvr_funcptr APIENTRY pvr_get_proc_addressex (pvr_string_t funcName);
VECTORAPI pvr_pointer_t APIENTRY pvr_get_proc_address(pvr_string_t funcName);

VECTORAPI pvr_schar_t APIENTRY pvr_main_init(char ***argv, int *argc);
/*
 * Techniq_Simd_functs
 */
typedef pvr_schar_t (APIENTRY pvr_techniq_create_simd)(const void* arg); // techniq name in get_func: pvr_techniq_create

#ifdef PVCTR_PROTOTYPES
VECTORAPI pvr_string_t APIENTRY pvr_get_version_string (void);
VECTORAPI pvr_uint_t   APIENTRY pvr_get_version(void);

VECTORAPI pvr_schar_t APIENTRY  pvr_techniq_add(pvr_string_t technic_name, pvr_techniq_func* getfunc);
VECTORAPI pvr_bool_t  APIENTRY  pvr_techniq_avaible(pvr_string_t technic_name);
VECTORAPI pvr_bool_t  APIENTRY  pvr_techniq_unset(pvr_string_t technic_name);
VECTORAPI pvr_techniq_func*  APIENTRY  pvr_techniq_get(pvr_string_t technic_name);
VECTORAPI pvr_pointer_t APIENTRY  pvr_techniq_get_func(pvr_string_t technic_name, pvr_string_t funcName);
//----------
VECTORAPI pvr_context_t* APIENTRY pvr_context_create(const pvr_uchar_t id,  const void* args, const pvr_size_t sargs);
VECTORAPI pvr_context_t* APIENTRY pvr_context_createex(const pvr_string_t technic_name, const void* args, const pvr_size_t sargs);
VECTORAPI pvr_schar_t APIENTRY pvr_context_api_geterror(const pvr_context_t* context);
VECTORAPI pvr_void_t  APIENTRY pvr_context_make_current(const pvr_context_t* context);
VECTORAPI pvr_context_t* APIENTRY pvr_context_current();


VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec2c(pvr_vec2c* pvec, const pvr_schar_t x, const pvr_schar_t y);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec3c(pvr_vec3c* pvec, const pvr_schar_t x, const pvr_schar_t y, const pvr_schar_t z);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec4c(pvr_vec4c* pvec, const pvr_schar_t x, const pvr_schar_t y, const pvr_schar_t z, const pvr_schar_t w);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec8c(pvr_vec8c* pvec, const pvr_schar_t x, const pvr_schar_t y, const pvr_schar_t z, const pvr_schar_t w, 
                                                                        const pvr_schar_t a, const pvr_schar_t b, const pvr_schar_t c, const pvr_schar_t d);

VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec2uc(pvr_vec2uc* pvec, const pvr_uchar_t x, const pvr_uchar_t y);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec3uc(pvr_vec3uc* pvec, const pvr_uchar_t x, const pvr_uchar_t y, const pvr_uchar_t z);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec4uc(pvr_vec4uc* pvec, const pvr_uchar_t x, const pvr_uchar_t y, const pvr_uchar_t z, const pvr_uchar_t w);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec8uc(pvr_vec8uc* pvec, const pvr_uchar_t x, const pvr_uchar_t y, const pvr_uchar_t z, const pvr_uchar_t w, 
                                                                          const pvr_uchar_t a, const pvr_uchar_t b, const pvr_uchar_t c, const pvr_uchar_t d);
                                                        
// short
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec2s(pvr_vec2s* pvec, const pvr_sshort_t x, const pvr_sshort_t y);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec3s(pvr_vec3s* pvec, const pvr_sshort_t x, const pvr_sshort_t y, const pvr_sshort_t z);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec4s(pvr_vec4s* pvec, const pvr_sshort_t x, const pvr_sshort_t y, const pvr_sshort_t z, const pvr_sshort_t w);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec8s(pvr_vec8s* pvec, const pvr_sshort_t x, const pvr_sshort_t y, const pvr_sshort_t z, const pvr_sshort_t w, 
                                                                        const pvr_sshort_t a, const pvr_sshort_t b, const pvr_sshort_t c, const pvr_sshort_t d);

VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec2us(pvr_vec2us* pvec, const pvr_ushort_t x, const pvr_ushort_t y);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec3us(pvr_vec3us* pvec, const pvr_ushort_t x, const pvr_ushort_t y, const pvr_ushort_t z);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec4us(pvr_vec4us* pvec, const pvr_ushort_t x, const pvr_ushort_t y, const pvr_ushort_t z, const pvr_ushort_t w);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec8us(pvr_vec8us* pvec, const pvr_ushort_t x, const pvr_ushort_t y, const pvr_ushort_t z, const pvr_ushort_t w, 
                                                                          const pvr_ushort_t a, const pvr_ushort_t b, const pvr_ushort_t c, const pvr_ushort_t d);
//int
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec2i(pvr_vec2s* pvec, const pvr_sint_t x, const pvr_sint_t y);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec3i(pvr_vec3s* pvec, const pvr_sint_t x, const pvr_sint_t y, const pvr_sint_t z);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec4i(pvr_vec4s* pvec, const pvr_sint_t x, const pvr_sint_t y, const pvr_sint_t z, const pvr_sint_t w);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec8i(pvr_vec8s* pvec, const pvr_sint_t x, const pvr_sint_t y, const pvr_sint_t z, const pvr_sint_t w, 
                                                                        const pvr_sint_t a, const pvr_sint_t b, const pvr_sint_t c, const pvr_sint_t d);

VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec2ui(pvr_vec2us* pvec, const pvr_uint_t x, const pvr_uint_t y);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec3ui(pvr_vec3us* pvec, const pvr_uint_t x, const pvr_uint_t y, const pvr_uint_t z);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec4ui(pvr_vec4us* pvec, const pvr_uint_t x, const pvr_uint_t y, const pvr_uint_t z, const pvr_uint_t w);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec8ui(pvr_vec8us* pvec, const pvr_uint_t x, const pvr_uint_t y, const pvr_uint_t z, const pvr_uint_t w, 
                                                                          const pvr_uint_t a, const pvr_uint_t b, const pvr_uint_t c, const pvr_uint_t d);
// long
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec2l(pvr_vec2l* pvec, const pvr_slong_t x, const pvr_slong_t y);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec3l(pvr_vec3l* pvec, const pvr_slong_t x, const pvr_slong_t y, const pvr_slong_t z);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec4l(pvr_vec4l* pvec, const pvr_slong_t x, const pvr_slong_t y, const pvr_slong_t z, const pvr_slong_t w);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec8l(pvr_vec8l* pvec, const pvr_slong_t x, const pvr_slong_t y, const pvr_slong_t z, const pvr_slong_t w, 
                                                                        const pvr_slong_t a, const pvr_slong_t b, const pvr_slong_t c, const pvr_slong_t d);

VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec2ul(pvr_vec2ul* pvec, const pvr_ulong_t x, const pvr_ulong_t y);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec3ul(pvr_vec3ul* pvec, const pvr_ulong_t x, const pvr_ulong_t y, const pvr_ulong_t z);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec4ul(pvr_vec4ul* pvec, const pvr_ulong_t x, const pvr_ulong_t y, const pvr_ulong_t z, const pvr_ulong_t w);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec8ul(pvr_vec8ul* pvec, const pvr_ulong_t x, const pvr_ulong_t y, const pvr_ulong_t z, const pvr_ulong_t w, 
                                                                          const pvr_ulong_t a, const pvr_ulong_t b, const pvr_ulong_t c, const pvr_ulong_t d);
//float / double
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec2f(pvr_vec2f* pvec, const pvr_float_t x, const pvr_float_t y);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec3f(pvr_vec3f* pvec, const pvr_float_t x, const pvr_float_t y, const pvr_float_t z);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec4f(pvr_vec4f* pvec, const pvr_float_t x, const pvr_float_t y, const pvr_float_t z, const pvr_float_t w);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec8f(pvr_vec8f* pvec, const pvr_float_t x, const pvr_float_t y, const pvr_float_t z, const pvr_float_t w, 
                                                                        const pvr_float_t a, const pvr_float_t b, const pvr_float_t c, const pvr_float_t d);

VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec2d(pvr_vec2d* pvec, const pvr_double_t x, const pvr_double_t y);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec3d(pvr_vec3d* pvec, const pvr_double_t x, const pvr_double_t y, const pvr_double_t z);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec4d(pvr_vec4d* pvec, const pvr_double_t x, const pvr_double_t y, const pvr_double_t z, const pvr_double_t w);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_vec8d(pvr_vec8d* pvec, const pvr_double_t x, const pvr_double_t y, const pvr_double_t z, const pvr_double_t w, 
                                                                          const pvr_double_t a, const pvr_double_t b, const pvr_double_t c, const pvr_double_t d);

VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_rgbac(pvr_rgbac* pvec, const pvr_uchar_t r, const pvr_uchar_t, const pvr_uchar_t g, const pvr_uchar_t b, const pvr_uchar_t a);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_rgbaf(pvr_rgbaf* pvec, const pvr_float_t r, const pvr_float_t, const pvr_uchar_t g, const pvr_float_t b, const pvr_float_t a);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_rect(pvr_rect* pvec, const pvr_float_t x, const pvr_float_t y, const pvr_float_t height, const pvr_float_t width);

VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat44f(pvr_mat4x4f *pmat, pvr_float_t m[16]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat43f(pvr_mat4x3f *pmat, pvr_float_t m[12]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat34f(pvr_mat3x4f *pmat, pvr_float_t m[12]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat42f(pvr_mat4x2f *pmat, pvr_float_t m[8]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat24f(pvr_mat2x4f *pmat, pvr_float_t m[8]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat33f(pvr_mat3x3f *pmat, pvr_float_t m[9]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat32f(pvr_mat3x2f *pmat, pvr_float_t m[6]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat23f(pvr_mat2x3f *pmat, pvr_float_t m[6]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat22f(pvr_mat2x2f *pmat, pvr_float_t m[4]);

VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat44d(pvr_mat4x4d *pmat, pvr_double_t m[16]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat43d(pvr_mat4x3d *pmat, pvr_double_t m[12]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat34d(pvr_mat3x4d *pmat, pvr_double_t m[12]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat42d(pvr_mat4x2d *pmat, pvr_double_t m[8]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat24d(pvr_mat2x4d *pmat, pvr_double_t m[8]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat33d(pvr_mat3x3d *pmat, pvr_double_t m[9]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat32d(pvr_mat3x2d *pmat, pvr_double_t m[6]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat23d(pvr_mat2x3d *pmat, pvr_double_t m[6]);
VECTORAPI pvr_schar_t APIENTRY pvr_vector_create_mat22d(pvr_mat2x2d *pmat, pvr_double_t m[4]);

#endif // PVCTR_PROTOTYPES


#ifdef __cplusplus
}
#endif

#include "PVCTRfasttype.h"

#endif // __vector_base_h_