//  SPDX-FileCopyrightText: 2025 Amber-Sophia Schröck 
//  SPDX-License-Identifier: MIT
#ifndef __vector_fast_type_h_
#define __vector_fast_type_h_ 1

#include "PVCTR.h"

#define PVR_FAST_TYPE_SETBIT(TYPE, POS, BIT) if(TYPE->count < POS) TYPE->bits[POS] = BIT; 
#define PVR_FAST_TYPE_GETBIT(TYPE, POS)      TYPE->bits[POS]; 
#define PVR_FAST_TYPE_SET(TYPE, VALUE)       TYPE->value = VALUE;
#define PVR_FAST_TYPE_GET(TYPE, VALUE)       TYPE->value;

// --- Basic Bit Type (fast_bit) ---
typedef struct {
    uint8_t bit : 1;  // Ein Bit im `bit`-Feld
} pvr_bit_t;

// --- Fast Type für eine Anzahl von Bits ---
#define PVCTR_FAST_TYPE(Bits, TBaseType, TName) \
typedef struct { \
    union { \
        TBaseType value; \
        pvr_bit_t bits[Bits]; \
    }; \
    size_t count;  \
} TName; 

#if PVCTR_VERSION_1_0 == 1

PVCTR_FAST_TYPE(sizeof(pvr_schar_t)    * CHAR_BIT, pvr_schar_t,   pvr_fast_schar_t);
PVCTR_FAST_TYPE(sizeof(pvr_uchar_t)    * CHAR_BIT, pvr_uchar_t,   pvr_fast_uchar_t);
PVCTR_FAST_TYPE(sizeof(pvr_sshort_t)   * CHAR_BIT, pvr_sshort_t,  pvr_fast_sshort_t);
PVCTR_FAST_TYPE(sizeof(pvr_ushort_t)   * CHAR_BIT, pvr_ushort_t,  pvr_fast_ushort_t);
PVCTR_FAST_TYPE(sizeof(pvr_sint_t)     * CHAR_BIT, pvr_sint_t,    pvr_fast_sint_t);
PVCTR_FAST_TYPE(sizeof(pvr_uint_t)     * CHAR_BIT, pvr_uint_t,    pvr_fast_uint_t);

PVCTR_FAST_TYPE(sizeof(pvr_float_t)    * CHAR_BIT, pvr_float_t,   pvr_fast_float_t);

PVCTR_FAST_TYPE(sizeof(pvr_double_t)    * CHAR_BIT, pvr_double_t,   pvr_fast_double_t);

PVCTR_FAST_TYPE(sizeof(pvr_slong_t)    * CHAR_BIT, pvr_slong_t,   pvr_fast_slong_t);
PVCTR_FAST_TYPE(sizeof(pvr_ulong_t)    * CHAR_BIT, pvr_ulong_t,   pvr_fast_ulong_t);

typedef pvr_uchar_t (APIENTRYP PFPVRFASTSCHARCREATEPROC) (pvr_fast_schar_t *type, const pvr_schar_t value); 
typedef pvr_uchar_t (APIENTRYP PFPVRFASTUCHARCREATEPROC) (pvr_fast_uchar_t *type, const pvr_uchar_t value); 
typedef pvr_uchar_t (APIENTRYP PFPVRFASTSSHORTCREATEPROC) (pvr_fast_sshort_t *type, const pvr_sshort_t value); 
typedef pvr_uchar_t (APIENTRYP PFPVRFASTUSHORTCREATEPROC) (pvr_fast_ushort_t *type, const pvr_ushort_t value); 
typedef pvr_uchar_t (APIENTRYP PFPVRFASTSINTCREATEPROC) (pvr_fast_sint_t *type, const pvr_sint_t value); 
typedef pvr_uchar_t (APIENTRYP PFPVRFASTUINTCREATEPROC) (pvr_fast_uint_t *type, const pvr_uint_t value); 

typedef pvr_uchar_t (APIENTRYP PFPVRFASTFLOATCREATEPROC) (pvr_fast_float_t *type, const pvr_float_t value); 
typedef pvr_uchar_t (APIENTRYP PFPVRFASTDOUBLECREATEPROC) (pvr_fast_double_t *type, const pvr_double_t value); 
typedef pvr_uchar_t (APIENTRYP PFPVRFASTSLONGCREATEPROC) (pvr_fast_slong_t *type, const pvr_slong_t value); 
typedef pvr_uchar_t (APIENTRYP PFPVRFASTULONGCREATEPROC) (pvr_fast_ulong_t *type, const pvr_ulong_t value); 

typedef pvr_void_t (APIENTRYP PFPVRFASTTYPEEQUALPROC) (const volatile pvr_void_t *a, const volatile pvr_void_t *b); 
typedef pvr_void_t (APIENTRYP PFPVRFASTTYPEGREATERPROC) (const volatile pvr_void_t *a, const volatile pvr_void_t *b); 
typedef pvr_void_t (APIENTRYP PFPVRFASTTYPELESSPROC) (const volatile pvr_void_t *a, const volatile pvr_void_t *b); 
typedef pvr_void_t (APIENTRYP PFPVRFASTTYPEGREATEREQUALPROC) (const volatile pvr_void_t *a, const volatile pvr_void_t *b); 
typedef pvr_void_t (APIENTRYP PFPVRFASTTYPELESSEQUALPROC) (const volatile pvr_void_t *a, const volatile pvr_void_t *b); 

VECTORAPI pvr_uchar_t APIENTRY pvr_fast_schar_create(pvr_fast_schar_t *type, const pvr_schar_t value);
VECTORAPI pvr_uchar_t APIENTRY pvr_fast_uchar_create(pvr_fast_uchar_t *type, const pvr_uchar_t value);
VECTORAPI pvr_uchar_t APIENTRY pvr_fast_sshort_create(pvr_fast_sshort_t *type, const pvr_sshort_t value);
VECTORAPI pvr_uchar_t APIENTRY pvr_fast_ushort_create(pvr_fast_ushort_t *type, const pvr_ushort_t value);
VECTORAPI pvr_uchar_t APIENTRY pvr_fast_sint_create(pvr_fast_sint_t *type, const pvr_sint_t value);
VECTORAPI pvr_uchar_t APIENTRY pvr_fast_uint_create(pvr_fast_uint_t *type, const pvr_uint_t value);
VECTORAPI pvr_uchar_t APIENTRY pvr_fast_float_create(pvr_fast_float_t *type, const pvr_float_t value);
VECTORAPI pvr_uchar_t APIENTRY pvr_fast_double_create(pvr_fast_double_t *type, const pvr_double_t value);
VECTORAPI pvr_uchar_t APIENTRY pvr_fast_slong_create(pvr_fast_slong_t *type, const pvr_slong_t value);
VECTORAPI pvr_uchar_t APIENTRY pvr_fast_ulong_create(pvr_fast_ulong_t *type, const pvr_ulong_t value);

VECTORAPI pvr_bool_t APIENTRY pvr_fast_type_equal(const volatile pvr_void_t *a, const volatile pvr_void_t *b);
VECTORAPI pvr_bool_t APIENTRY pvr_fast_type_greater(const volatile pvr_void_t *a, const volatile pvr_void_t *b);
VECTORAPI pvr_bool_t APIENTRY pvr_fast_type_less(const volatile pvr_void_t *a, const volatile pvr_void_t *b);
VECTORAPI pvr_bool_t APIENTRY pvr_fast_type_greater_eq(const volatile pvr_void_t *a, const volatile pvr_void_t *b);
VECTORAPI pvr_bool_t APIENTRY pvr_fast_type_less_eq(const volatile pvr_void_t *a, const volatile pvr_void_t *b);
#endif


#endif  //__vector_fast_type_h_