#include "OVTUtils.h"

#include <string.h>

struct name_address_pair
{
   ovt_string_t Name;
   ovt_pointer_t Address;
};
#define OVT_FUNCTIONS(TFUNC) { #TFUNC, (ovt_pointer_t)TFUNC }
#define OVT_FUNCTIONSX(TFUNC, TORIGNAME) { TORIGNAME, (ovt_pointer_t)TFUNC }

static const struct name_address_pair OVTx_FUNCTIONs[] = {
   OVT_FUNCTIONS(ovt_get_version_string),
   OVT_FUNCTIONS(ovt_get_version),
   OVT_FUNCTIONSX(ovtx_get_proc_addressex, "ovtx_get_proc_address"),
#if OVECTOR_VERSION_1_0 == 1
   
   OVT_FUNCTIONS(ovt_fast_schar_create),
   OVT_FUNCTIONS(ovt_fast_uchar_create),
   OVT_FUNCTIONS(ovt_fast_sshort_create),
   OVT_FUNCTIONS(ovt_fast_ushort_create),
   OVT_FUNCTIONS(ovt_fast_sint_create),
   OVT_FUNCTIONS(ovt_fast_uint_create),
#if OPENVECTOR_SUPPORT_INT64 == 1
   OVT_FUNCTIONS(ovt_fast_slong_create),
   OVT_FUNCTIONS(ovt_fast_ulong_create),
#endif // OPENVECTOR_SUPPORT_INT64 == 1

   OVT_FUNCTIONS(ovt_fast_type_reset),
   OVT_FUNCTIONS(ovt_fast_type_set_bit),
   OVT_FUNCTIONS(ovt_fast_type_get_bit),
   OVT_FUNCTIONS(ovt_fast_type_equal),
   OVT_FUNCTIONS(ovt_fast_type_greater),
   OVT_FUNCTIONS(ovt_fast_type_less),
   OVT_FUNCTIONS(ovt_fast_type_greater_eq),
   OVT_FUNCTIONS(ovt_fast_type_less_eq),


#endif // OVECTOR_VERSION_1_0 == 1

#if OVECTOR_VERSION_1_1 == 1
   OVT_FUNCTIONS(ovt_fast_float_create),
   OVT_FUNCTIONS(ovt_fast_double_create),
#endif

   {NULL, NULL}                 /* end of list */
};


VECTORAPI ovtx_funcptr ovtx_get_proc_addressex (ovt_string_t funcName) {
    ovt_pointer_t f = (ovt_pointer_t) ovtx_get_proc_address((ovt_string_t) funcName);

    return f;
}
VECTORAPI ovt_pointer_t ovtx_get_proc_address(ovt_string_t funcName) {
   ovt_size_t i;

   for (i = 0; OVTx_FUNCTIONs[i].Name; i++) {
      if (strcmp(OVTx_FUNCTIONs[i].Name, funcName) == 0)
         return OVTx_FUNCTIONs[i].Address;
   }

   return NULL;
}



