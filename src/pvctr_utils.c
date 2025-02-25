//  SPDX-FileCopyrightText: 2025 Amber-Sophia Schröck 
//  SPDX-License-Identifier: MIT

#define PVCTR_PROTOTYPES 1
#include "PVCTR.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct name_address_pair
{
   pvr_string_t Name;
   pvr_pointer_t Address;
};
#define PVR_FUNCTIONS(TFUNC) { #TFUNC, (void*)TFUNC }
#define PVR_FUNCTIONSX(TFUNC, TORIGNAME) { TORIGNAME, (pvr_pointer_t)TFUNC }

static const struct name_address_pair OVTx_FUNCTIONs[] = {
   PVR_FUNCTIONS(pvr_main_init),
   PVR_FUNCTIONS(pvr_get_version_string),
   PVR_FUNCTIONS(pvr_get_version),
   PVR_FUNCTIONSX(pvr_get_proc_addressex, "pvr_get_proc_address"),

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

   PVR_FUNCTIONS(pvr_techniq_add),
   PVR_FUNCTIONS(pvr_techniq_avaible),
   PVR_FUNCTIONS(pvr_techniq_unset),
   PVR_FUNCTIONS(pvr_techniq_get),
   PVR_FUNCTIONS(pvr_techniq_get_func),

   PVR_FUNCTIONS(pvr_context_create),
   PVR_FUNCTIONS(pvr_context_createex),
   PVR_FUNCTIONS(pvr_context_api_geterror),
   PVR_FUNCTIONS(pvr_context_make_current),
#if 0
   PVR_FUNCTIONS(pvr_vector_create_vec2c),
   PVR_FUNCTIONS(pvr_vector_create_vec3c),
   PVR_FUNCTIONS(pvr_vector_create_vec4c),
   PVR_FUNCTIONS(pvr_vector_create_vec8c),
   PVR_FUNCTIONS(pvr_vector_create_vec2uc),
   PVR_FUNCTIONS(pvr_vector_create_vec3uc),
   PVR_FUNCTIONS(pvr_vector_create_vec4uc),
   PVR_FUNCTIONS(pvr_vector_create_vec8uc),
   PVR_FUNCTIONS(pvr_vector_create_vec2s),
   PVR_FUNCTIONS(pvr_vector_create_vec3s),
   PVR_FUNCTIONS(pvr_vector_create_vec4s),
   PVR_FUNCTIONS(pvr_vector_create_vec8s),
   PVR_FUNCTIONS(pvr_vector_create_vec2us),
   PVR_FUNCTIONS(pvr_vector_create_vec3us),
   PVR_FUNCTIONS(pvr_vector_create_vec4us),
   PVR_FUNCTIONS(pvr_vector_create_vec8us),
   PVR_FUNCTIONS(pvr_vector_create_vec2i),
   PVR_FUNCTIONS(pvr_vector_create_vec3i),
   PVR_FUNCTIONS(pvr_vector_create_vec4i),
   PVR_FUNCTIONS(pvr_vector_create_vec8i),
   PVR_FUNCTIONS(pvr_vector_create_vec2ui),
   PVR_FUNCTIONS(pvr_vector_create_vec3ui),
   PVR_FUNCTIONS(pvr_vector_create_vec4ui),
   PVR_FUNCTIONS(pvr_vector_create_vec8ui),
   PVR_FUNCTIONS(pvr_vector_create_vec2l),
   PVR_FUNCTIONS(pvr_vector_create_vec3l),
   PVR_FUNCTIONS(pvr_vector_create_vec4l),
   PVR_FUNCTIONS(pvr_vector_create_vec8l),
   PVR_FUNCTIONS(pvr_vector_create_vec2ul),
   PVR_FUNCTIONS(pvr_vector_create_vec3ul),
   PVR_FUNCTIONS(pvr_vector_create_vec4ul),
   PVR_FUNCTIONS(pvr_vector_create_vec8ul),

   PVR_FUNCTIONS(pvr_vector_create_vec2f),
   PVR_FUNCTIONS(pvr_vector_create_vec3f),
   PVR_FUNCTIONS(pvr_vector_create_vec4f),
   PVR_FUNCTIONS(pvr_vector_create_vec8f),
   PVR_FUNCTIONS(pvr_vector_create_vec2d),
   PVR_FUNCTIONS(pvr_vector_create_vec3d),
   PVR_FUNCTIONS(pvr_vector_create_vec4d),
   PVR_FUNCTIONS(pvr_vector_create_vec8d),


   PVR_FUNCTIONS(pvr_vector_create_mat44f),
   PVR_FUNCTIONS(pvr_vector_create_mat43f),
   PVR_FUNCTIONS(pvr_vector_create_mat34f),
   PVR_FUNCTIONS(pvr_vector_create_mat42f),
   PVR_FUNCTIONS(pvr_vector_create_mat24f),
   PVR_FUNCTIONS(pvr_vector_create_mat33f),
   PVR_FUNCTIONS(pvr_vector_create_mat32f),
   PVR_FUNCTIONS(pvr_vector_create_mat23f),
   PVR_FUNCTIONS(pvr_vector_create_mat22f),

   PVR_FUNCTIONS(pvr_vector_create_mat44d),
   PVR_FUNCTIONS(pvr_vector_create_mat43d),
   PVR_FUNCTIONS(pvr_vector_create_mat34d),
   PVR_FUNCTIONS(pvr_vector_create_mat42d),
   PVR_FUNCTIONS(pvr_vector_create_mat24d),
   PVR_FUNCTIONS(pvr_vector_create_mat33d),
   PVR_FUNCTIONS(pvr_vector_create_mat32d),
   PVR_FUNCTIONS(pvr_vector_create_mat23d),
   PVR_FUNCTIONS(pvr_vector_create_mat22d),
#endif
   {NULL, NULL}                 /* end of list */
};

VECTORAPI pvr_pointer_t pvr_get_proc_address(pvr_string_t funcName) {
   pvr_size_t i;

   for (i = 0; OVTx_FUNCTIONs[i].Name; i++) {
      if (strcmp(OVTx_FUNCTIONs[i].Name, funcName) == 0)
         return OVTx_FUNCTIONs[i].Address;
   }

   return NULL;
}
   
VECTORAPI pvr_funcptr pvr_get_proc_addressex (pvr_string_t funcName) {
    pvr_pointer_t f = (pvr_pointer_t) pvr_get_proc_address((pvr_string_t) funcName);

    return f;
}

VECTORAPI pvr_schar_t pvr_main_init(char ***argv, int *argc) {
   pvr_string_t *name;
   pvr_context_t *pvr_context = 0;

   if(argc && argv && *argc > 1 && strcmp((*argv)[0], "-api") == 0) {
         pvr_context = pvr_context_createex((*argv)[1], NULL, 0);
        if(!pvr_context) 
            fprintf(stderr, "Failed to use api \"%s\", trying default\n", (*argv)[1]);
        (*argv) += 2;
        (*argc) -= 2;
   }
   if(!pvr_context)
       pvr_context = pvr_context_create(PVCTR_TECHNIQ_USED, NULL, 0);
   if(!pvr_context) {
      fprintf(stderr, "Could not create default context!\n");
      return 1;
   }
   printf("Used \"%s\"\n", pvr_get_version_string());
   pvr_context_make_current(pvr_context);
   return 0;
}
