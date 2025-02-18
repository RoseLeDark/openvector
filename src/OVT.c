//  SPDX-FileCopyrightText: 2025 Amber-Sophia Schröck 
//  SPDX-License-Identifier: MIT

#include <OVT.h>

extern const char* APIENTRY ovt_get_version_string (void) {
    return OVECTOR_VERSION_STRING;
}
extern ovt_uint_t APIENTRY ovt_get_version(void) {
    return OVECTOR_VERSION;
}