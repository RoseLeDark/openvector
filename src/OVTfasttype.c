#include <OVTfasttype.h>
#include <string.h>

#define OVT_FAST_TYPE_CREATE(TName, TFunc, TVal) \
VECTORAPI void TFunc(TName *type, const TVal value) { \
    type->value = value; \
    type->count = sizeof(value) * CHAR_BIT; \
}

OVT_FAST_TYPE_CREATE(ovt_fast_schar_t,     ovt_fast_schar_create, ovt_schar_t);
OVT_FAST_TYPE_CREATE(ovt_fast_uchar_t,     ovt_fast_uchar_create, ovt_uchar_t);
OVT_FAST_TYPE_CREATE(ovt_fast_sshort_t,    ovt_fast_sshort_create, ovt_sshort_t);
OVT_FAST_TYPE_CREATE(ovt_fast_ushort_t,    ovt_fast_ushort_create, ovt_ushort_t);
OVT_FAST_TYPE_CREATE(ovt_fast_sint_t,      ovt_fast_sint_create, ovt_sint_t);
OVT_FAST_TYPE_CREATE(ovt_fast_uint_t,      ovt_fast_uint_create, ovt_uint_t);

#if OPENVECTOR_SUPPORT_INT64 == 1
OVT_FAST_TYPE_CREATE(ovt_fast_slong_t,     ovt_fast_slong_create, ovt_slong_t);
OVT_FAST_TYPE_CREATE(ovt_fast_ulong_t,     ovt_fast_ulong_create, ovt_ulong_t);
#endif //OPENVECTOR_SUPPORT_INT64


OVT_FAST_TYPE(MB_LEN_MAX*CHAR_BIT, void*,   ovt_voidp_t);

VECTORAPI ovt_size_t APIENTRY ovt_fast_type_reset(volatile ovt_void_t *type, const ovt_void_t* value, const ovt_size_t vsize) {
    ovt_size_t required_size = ((ovt_voidp_t*)type)->count;
    ovt_size_t written = (vsize < required_size)  ? vsize : required_size;

    memcpy(((ovt_voidp_t*)type)->value, value, written);


    return written;
}
VECTORAPI ovt_bool_t APIENTRY ovt_fast_type_set_bit(volatile ovt_void_t *type, ovt_size_t pos, ovt_bit_t value) {
    ovt_size_t max_size = ((ovt_voidp_t*)type)->count;

    if (max_size > pos) {
        ((ovt_voidp_t *)type)->bits[pos] = value;
        return OVT_TRUE;
    } 
    return OVT_FALSE;
}
VECTORAPI ovt_bool_t  APIENTRY ovt_fast_type_get_bit(volatile ovt_void_t *type, ovt_size_t pos, ovt_bit_t* value) {
    ovt_size_t max_size = ((ovt_voidp_t*)type)->count;
    
    if (max_size > pos) {
        *value = ((ovt_voidp_t *)type)->bits[pos];
        return OVT_TRUE;
    } 
    return OVT_FALSE;
}
VECTORAPI ovt_bool_t APIENTRY ovt_fast_type_equal(const volatile ovt_void_t *a, const volatile ovt_void_t *b) {
    if(a == NULL || b == NULL) return OVT_FALSE;

    ovt_voidp_t* _a = ((ovt_voidp_t*)a);
    ovt_voidp_t* _b = ((ovt_voidp_t*)b);

    ovt_size_t min_count = (_a->count < _b->count) ? _a->count : _b->count;  // Kleinste Anzahl Bits
    for(ovt_size_t i = 0; i < min_count; i++) {
        if(_a->bits[i].bit != _b->bits[i].bit) {
            return OVT_FALSE;
        }
    }
    // Falls der kleinere Typ mit den Bits übereinstimmt, prüfe die restlichen Bits des größeren Datentyps
    if (_a->count != _b->count) {
        ovt_size_t max_count = (_a->count > _b->count) ? _a->count : _b->count;
        for(ovt_size_t i = min_count; i < max_count; i++) {
            if (_a->count > _b->count) {
                if (_a->bits[i].bit != 0) {
                    return OVT_FALSE;
                }
            } else {
                if (_b->bits[i].bit != 0) {
                    return OVT_FALSE;
                }
            }
        }
    }
    return OVT_TRUE;
}

VECTORAPI ovt_bool_t APIENTRY ovt_fast_type_greater(const volatile ovt_void_t *a, const volatile ovt_void_t *b) {
    if(a == NULL || b == NULL) return OVT_FALSE;

    ovt_voidp_t* _a = ((ovt_voidp_t*)a);
    ovt_voidp_t* _b = ((ovt_voidp_t*)b);

    ovt_size_t min_count = (_a->count < _b->count) ? _a->count : _b->count;

    for (ovt_size_t i = 0; i < min_count; i++) {
        if (_a->bits[i].bit > _b->bits[i].bit) {
            return OVT_TRUE; // Wenn A's Bit größer ist als B's Bit, A > B
        } else if (_a->bits[i].bit < _b->bits[i].bit) {
            return OVT_FALSE; // Wenn A's Bit kleiner ist als B's Bit, A < B
        }
    }

    // Wenn sie bis hier kommen, sind die Bits gleich, also prüfe die restlichen Bits
    if (_a->count != _b->count) {
        ovt_size_t max_count = (_a->count > _b->count) ? _a->count : _b->count;
        for (ovt_size_t i = min_count; i < max_count; i++) {
            if (_a->count > _b->count) {
                if (_a->bits[i].bit != 0) {
                    return OVT_TRUE; // Falls A mehr Bits hat, aber A's Bit > 0, dann A > B
                }
            } else {
                if (_b->bits[i].bit != 0) {
                    return OVT_FALSE; // Falls B mehr Bits hat und B's Bit > 0, dann A < B
                }
            }
        }
    }
    return OVT_FALSE; // Wenn keine der Bedingungen zutrifft, ist A nicht größer als B
}


VECTORAPI ovt_bool_t APIENTRY ovt_fast_type_less(const volatile ovt_void_t *a, const volatile ovt_void_t *b) {
    if(a == NULL || b == NULL) return OVT_FALSE;

    ovt_voidp_t* _a = ((ovt_voidp_t*)a);
    ovt_voidp_t* _b = ((ovt_voidp_t*)b);

    ovt_size_t min_count = (_a->count < _b->count) ? _a->count : _b->count;

    for (ovt_size_t i = 0; i < min_count; i++) {
        if (_a->bits[i].bit < _b->bits[i].bit) {
            return OVT_TRUE; // Wenn A's Bit kleiner ist als B's Bit, A < B
        } else if (_a->bits[i].bit > _b->bits[i].bit) {
            return OVT_FALSE; // Wenn A's Bit größer ist als B's Bit, A > B
        }
    }

    // Wenn sie bis hier kommen, sind die Bits gleich, also prüfe die restlichen Bits
    if (_a->count != _b->count) {
        ovt_size_t max_count = (_a->count > _b->count) ? _a->count : _b->count;
        for (ovt_size_t i = min_count; i < max_count; i++) {
            if (_a->count > _b->count) {
                if (_a->bits[i].bit != 0) {
                    return OVT_FALSE; // Falls A mehr Bits hat, aber A's Bit > 0, dann A > B
                }
            } else {
                if (_b->bits[i].bit != 0) {
                    return OVT_TRUE; // Falls B mehr Bits hat und B's Bit > 0, dann A < B
                }
            }
        }
    }
    return OVT_FALSE; // Wenn keine der Bedingungen zutrifft, ist A nicht kleiner als B
}

VECTORAPI ovt_bool_t APIENTRY ovt_fast_type_greater_eq(const volatile ovt_void_t *a, const volatile ovt_void_t *b) {
    ovt_bool_t _equal =  ovt_fast_type_equal(a, b);
    ovt_bool_t _greater = ovt_fast_type_greater(a, b);

    return _equal == OVT_TRUE && _greater == OVT_TRUE;
}

VECTORAPI ovt_bool_t APIENTRY ovt_fast_type_less_eq(const volatile ovt_void_t *a, const volatile ovt_void_t *b) {
    ovt_bool_t _equal =  ovt_fast_type_equal(a, b);
    ovt_bool_t _less= ovt_fast_type_less(a, b);

    return _equal == OVT_TRUE && _greater == OVT_TRUE;
}