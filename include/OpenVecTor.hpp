#ifndef __vector_base_h_
#define __vector_base_h_ 1

#include "VT/OVplatform.h"
#include "VT/OVfasttype.hpp"

#define VECTOR_COPYRIGHT "Copyright (c) 2025 Amber-Sophia Schroeck " \
                       "MIT License"

#define VECTOR_VERSION 010000
#define VECTOR_VERSION_MAJOR    1
#define VECTOR_VERSION_MINOR    0
#define VECTOR_VERSION_PATCH    0

#define VECTOR_VERSION_AT_LEAST(major, minor, patch ) 	\
(((major) < VECTOR_VERSION_MAJOR)                                     \
 || ((major) == VECTOR_VERSION_MAJOR && (minor) < VECTOR_VERSION_MINOR) \
 || ((major) == VECTOR_VERSION_MAJOR && (minor) == VECTOR_VERSION_MINOR && (patch) <= VECTOR_VERSION_PATCH))	

#define VECTOR_STRINGIFY(n) VECTOR_STRINGIFY_HELPER(n)
#define VECTOR_STRINGIFY_HELPER(n) #n

#define VECTOR_VERSION_STRING VECTOR_STRINGIFY_HELPER(VECTOR_VERSION_MAJOR) "." \
     VECTOR_STRINGIFY_HELPER(VECTOR_VERSION_MINOR) "." VECTOR_STRINGIFY_HELPER(VECTOR_VERSION_PATCH) 
     
#ifndef VECTOR_VERSION_1_0
#define VECTOR_VERSION_1_0 1

typedef struct {
	ov_schar_t major;      /**< major number */
	ov_schar_t minor;      /**< minor number */
	ov_schar_t patch;      /**< patch number */
} ov_version_t;
  
typedef const char* (APIENTRYP PFNOPENVECTORVERSIONPROC) (void);
typedef const char* (APIENTRYP PFNOPENVECTORVERSIONSTRINGPROC) (void);

VECTORAPI const char* APIENTRY openvector_version (void);
VECTORAPI const char* APIENTRY openvector_version_string(void);
#endif



#ifdef __cplusplus
}
#endif

#endif // __vector_base_h_
