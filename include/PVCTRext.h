//  SPDX-FileCopyrightText: 2025 Amber-Sophia Schröck 
//  SPDX-License-Identifier: MIT


#ifndef __vector_extends_h_
#define __vector_extends_h_ 1

#ifndef __vector_base_h_
#error "include PVCTR.h first!!
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct { 
    pvr_uint_t using_techniq;
    pvr_uchar_t alignas_size; 
} pvr_context_t; // platzhalter



#ifdef __cplusplus
}
#endif

#endif // __vector_extends_h_