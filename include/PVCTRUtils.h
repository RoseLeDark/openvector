//  SPDX-FileCopyrightText: 2025 Amber-Sophia Schröck 
//  SPDX-License-Identifier: MIT

#ifndef __vector_utils_h_
#define __vector_utils_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

#include <PVCTR.h>

#define PVCTRUTILS_VERSION_1_0   1

#ifndef PVCTRx_get_proc_address
#define PVCTRx_get_proc_address 1

typedef void (*pvrx_funcptr)(void);
VECTORAPI pvrx_funcptr APIENTRY pvrx_get_proc_addressex (pvr_string_t funcName);
VECTORAPI pvr_pointer_t APIENTRY pvrx_get_proc_address(pvr_string_t funcName);

#endif // PVCTRx_get_proc_address


#ifdef __cplusplus
}
#endif


#endif // __vector_utils_h_