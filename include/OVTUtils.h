//  SPDX-FileCopyrightText: 2025 Amber-Sophia Schröck 
//  SPDX-License-Identifier: MIT

#ifndef __vector_utils_h_
#define __vector_utils_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

#include <OVT.h>

#define OVTUTILS_VERSION_1_0   1

#ifndef OVTx_get_proc_address
#define OVTx_get_proc_address 1

typedef void (*ovtx_funcptr)(void);
VECTORAPI ovtx_funcptr APIENTRY ovtx_get_proc_addressex (ovt_string_t funcName);
VECTORAPI ovt_pointer_t APIENTRY ovtx_get_proc_address(ovt_string_t funcName);

#endif // OVTx_get_proc_address


#ifdef __cplusplus
}
#endif


#endif // __vector_utils_h_