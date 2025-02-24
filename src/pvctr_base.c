//  SPDX-FileCopyrightText: 2025 Amber-Sophia Schröck 
//  SPDX-License-Identifier: MIT

#include <PVCTR.h>

extern pvr_string_t APIENTRY pvr_get_version_string (void) {
    return PVCTR_VERSION_STRING;
}
extern pvr_uint_t APIENTRY pvr_get_version(void) {
    return PVCTR_VERSION;
}