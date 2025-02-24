//  SPDX-FileCopyrightText: 2025 Amber-Sophia Schröck 
//  SPDX-License-Identifier: MIT

#include "PVCTR.h"
#include "PVCTRUtils.h"

#include <string.h>

struct name_address_pair
{
   pvr_string_t Name;
   pvr_pointer_t Address;
};
#define PVR_FUNCTIONS(TFUNC) { #TFUNC, (pvr_pointer_t)TFUNC }
#define PVR_FUNCTIONSX(TFUNC, TORIGNAME) { TORIGNAME, (pvr_pointer_t)TFUNC }

static const struct name_address_pair OVTx_FUNCTIONs[] = {
   PVR_FUNCTIONS(pvr_get_version_string),
   PVR_FUNCTIONS(pvr_get_version),
   PVR_FUNCTIONSX(pvrx_get_proc_addressex, "pvrx_get_proc_address"),
#if PVCTRUTILS_VERSION_1_0 == 1
   
   PVR_FUNCTIONS(pvr_fast_schar_create),
   PVR_FUNCTIONS(pvr_fast_uchar_create),
   PVR_FUNCTIONS(pvr_fast_sshort_create),
   PVR_FUNCTIONS(pvr_fast_ushort_create),
   PVR_FUNCTIONS(pvr_fast_sint_create),
   PVR_FUNCTIONS(pvr_fast_uint_create),

   PVR_FUNCTIONS(pvr_fast_float_create),

   PVR_FUNCTIONS(pvr_fast_type_equal),
   PVR_FUNCTIONS(pvr_fast_type_greater),
   PVR_FUNCTIONS(pvr_fast_type_less),
   PVR_FUNCTIONS(pvr_fast_type_greater_eq),
   PVR_FUNCTIONS(pvr_fast_type_less_eq),
#endif 

   {NULL, NULL}                 /* end of list */
};

VECTORAPI pvr_pointer_t pvrx_get_proc_address(pvr_string_t funcName) {
   pvr_size_t i;

   for (i = 0; OVTx_FUNCTIONs[i].Name; i++) {
      if (strcmp(OVTx_FUNCTIONs[i].Name, funcName) == 0)
         return OVTx_FUNCTIONs[i].Address;
   }

   return NULL;
}
   
VECTORAPI pvrx_funcptr pvrx_get_proc_addressex (pvr_string_t funcName) {
    pvr_pointer_t f = (pvr_pointer_t) pvrx_get_proc_address((pvr_string_t) funcName);

    return f;
}




