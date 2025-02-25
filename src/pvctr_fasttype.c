//  SPDX-FileCopyrightText: 2025 Amber-Sophia Schröck 
//  SPDX-License-Identifier: MIT


#include "PVCTRfasttype.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define PVR_FAST_TYPE_CREATE(TName, TFunc, TVal) \
VECTORAPI pvr_uchar_t TFunc##_create(TName *type, const TVal value) { \
    if (type == NULL) {  return PVCTR_ERROR_INVALID_ARG; } \
    type->count = sizeof(value) * CHAR_BIT; \
    type->value = value; \
    return PVCTR_OK; \
} 

PVR_FAST_TYPE_CREATE(pvr_fast_schar_t,     pvr_fast_schar, pvr_schar_t)
PVR_FAST_TYPE_CREATE(pvr_fast_uchar_t,     pvr_fast_uchar, pvr_uchar_t)
PVR_FAST_TYPE_CREATE(pvr_fast_sshort_t,    pvr_fast_sshort, pvr_sshort_t)
PVR_FAST_TYPE_CREATE(pvr_fast_ushort_t,    pvr_fast_ushort, pvr_ushort_t)
PVR_FAST_TYPE_CREATE(pvr_fast_sint_t,      pvr_fast_sint, pvr_sint_t)
PVR_FAST_TYPE_CREATE(pvr_fast_uint_t,      pvr_fast_uint, pvr_uint_t)
PVR_FAST_TYPE_CREATE(pvr_fast_float_t,     pvr_fast_float, pvr_float_t)
PVR_FAST_TYPE_CREATE(pvr_fast_double_t,    pvr_fast_double, pvr_double_t)
PVR_FAST_TYPE_CREATE(pvr_fast_slong_t,     pvr_fast_slong, pvr_slong_t)
PVR_FAST_TYPE_CREATE(pvr_fast_ulong_t,     pvr_fast_ulong, pvr_ulong_t)


PVCTR_FAST_TYPE(MB_LEN_MAX * CHAR_BIT, void*,   pvr_fast_voidp_t);

VECTORAPI pvr_bool_t APIENTRY pvr_fast_type_equal(const volatile pvr_void_t *a, const volatile pvr_void_t *b) {
    if(a == NULL || b == NULL) return PVR_FALSE;

    pvr_fast_voidp_t* _a = ((pvr_fast_voidp_t*)a);
    pvr_fast_voidp_t* _b = ((pvr_fast_voidp_t*)b);

    pvr_size_t min_count = (_a->count < _b->count) ? _a->count : _b->count;  // Kleinste Anzahl Bits
    for(pvr_size_t i = 0; i < min_count; i++) {
        if(_a->bits[i].bit != _b->bits[i].bit) {
            return PVR_FALSE;
        }
    }
    // Falls der kleinere Typ mit den Bits übereinstimmt, prüfe die restlichen Bits des größeren Datentyps
    if (_a->count != _b->count) {
        pvr_size_t max_count = (_a->count > _b->count) ? _a->count : _b->count;
        for(pvr_size_t i = min_count; i < max_count; i++) {
            if (_a->count > _b->count) {
                if (_a->bits[i].bit != 0) {
                    return PVR_FALSE;
                }
            } else {
                if (_b->bits[i].bit != 0) {
                    return PVR_FALSE;
                }
            }
        }
    }
    return PVR_TRUE;
}

VECTORAPI pvr_bool_t APIENTRY pvr_fast_type_greater(const volatile pvr_void_t *a, const volatile pvr_void_t *b) {
    if(a == NULL || b == NULL) return PVR_FALSE;

    pvr_fast_voidp_t* _a = ((pvr_fast_voidp_t*)a);
    pvr_fast_voidp_t* _b = ((pvr_fast_voidp_t*)b);

    pvr_size_t min_count = (_a->count < _b->count) ? _a->count : _b->count;

    for (pvr_size_t i = 0; i < min_count; i++) {
        if (_a->bits[i].bit > _b->bits[i].bit) {
            return PVR_TRUE; // Wenn A's Bit größer ist als B's Bit, A > B
        } else if (_a->bits[i].bit < _b->bits[i].bit) {
            return PVR_FALSE; // Wenn A's Bit kleiner ist als B's Bit, A < B
        }
    }

    // Wenn sie bis hier kommen, sind die Bits gleich, also prüfe die restlichen Bits
    if (_a->count != _b->count) {
        pvr_size_t max_count = (_a->count > _b->count) ? _a->count : _b->count;
        for (pvr_size_t i = min_count; i < max_count; i++) {
            if (_a->count > _b->count) {
                if (_a->bits[i].bit != 0) {
                    return PVR_TRUE; // Falls A mehr Bits hat, aber A's Bit > 0, dann A > B
                }
            } else {
                if (_b->bits[i].bit != 0) {
                    return PVR_FALSE; // Falls B mehr Bits hat und B's Bit > 0, dann A < B
                }
            }
        }
    }
    return PVR_FALSE; // Wenn keine der Bedingungen zutrifft, ist A nicht größer als B
}


VECTORAPI pvr_bool_t APIENTRY pvr_fast_type_less(const volatile pvr_void_t *a, const volatile pvr_void_t *b) {
    if(a == NULL || b == NULL) return PVR_FALSE;

    pvr_fast_voidp_t* _a = ((pvr_fast_voidp_t*)a);
    pvr_fast_voidp_t* _b = ((pvr_fast_voidp_t*)b);

    pvr_size_t min_count = (_a->count < _b->count) ? _a->count : _b->count;

    for (pvr_size_t i = 0; i < min_count; i++) {
        if (_a->bits[i].bit < _b->bits[i].bit) {
            return PVR_TRUE; // Wenn A's Bit kleiner ist als B's Bit, A < B
        } else if (_a->bits[i].bit > _b->bits[i].bit) {
            return PVR_FALSE; // Wenn A's Bit größer ist als B's Bit, A > B
        }
    }

    // Wenn sie bis hier kommen, sind die Bits gleich, also prüfe die restlichen Bits
    if (_a->count != _b->count) {
        pvr_size_t max_count = (_a->count > _b->count) ? _a->count : _b->count;
        for (pvr_size_t i = min_count; i < max_count; i++) {
            if (_a->count > _b->count) {
                if (_a->bits[i].bit != 0) {
                    return PVR_FALSE; // Falls A mehr Bits hat, aber A's Bit > 0, dann A > B
                }
            } else {
                if (_b->bits[i].bit != 0) {
                    return PVR_TRUE; // Falls B mehr Bits hat und B's Bit > 0, dann A < B
                }
            }
        }
    }
    return PVR_FALSE; // Wenn keine der Bedingungen zutrifft, ist A nicht kleiner als B
}

VECTORAPI pvr_bool_t APIENTRY pvr_fast_type_greater_eq(const volatile pvr_void_t *a, const volatile pvr_void_t *b) {
    pvr_bool_t _equal =  pvr_fast_type_equal(a, b);
    pvr_bool_t _greater = pvr_fast_type_greater(a, b);

    return _equal == PVR_TRUE && _greater == PVR_TRUE;
}

VECTORAPI pvr_bool_t APIENTRY pvr_fast_type_less_eq(const volatile pvr_void_t *a, const volatile pvr_void_t *b) {
    pvr_bool_t _equal =  pvr_fast_type_equal(a, b);
    pvr_bool_t _less= pvr_fast_type_less(a, b);

    return _equal == PVR_TRUE && _less == PVR_TRUE;
}