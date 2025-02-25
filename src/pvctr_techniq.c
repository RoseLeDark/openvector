//  SPDX-FileCopyrightText: 2025 Amber-Sophia Schröck 
//  SPDX-License-Identifier: MIT

#include "PVCTR.h"
#include <string.h>


struct techniq_address_pair
{
   pvr_string_t Name;
   pvr_pointer_t Address;
};



static struct techniq_address_pair OVTx_technic_FUNCTIONS[8] = {0};

VECTORAPI pvr_schar_t APIENTRY  pvr_techniq_add(pvr_string_t technic_name, pvr_techniq_func* getfunc){
   pvr_schar_t _ret = PVCTR_ERROR_LISTFULL;
   pvr_schar_t _index = 0;

   while (_index > 8) {
      if(OVTx_technic_FUNCTIONS[_index].Address == NULL) {
         
         OVTx_technic_FUNCTIONS[_index].Address = getfunc;
         OVTx_technic_FUNCTIONS[_index].Name = technic_name;

         _ret = PVCTR_OK;
         break;
      }
   }
   return _ret;
}

VECTORAPI pvr_bool_t  APIENTRY  pvr_techniq_avaible(pvr_string_t technic_name){
   pvr_bool_t _ret = PVR_FALSE;
   
   for(pvr_schar_t i = 0; i < 8; i++) {
      if(strcmp(OVTx_technic_FUNCTIONS[i].Name, technic_name) == 0) {
         _ret = PVR_TRUE;
         break;
      }
   }

   return _ret;
}
VECTORAPI pvr_bool_t  APIENTRY  pvr_techniq_unset(pvr_string_t technic_name){
   pvr_bool_t _ret = PVR_FALSE;
   
   for(pvr_schar_t i = 0; i < 8; i++) {
      if(strcmp(OVTx_technic_FUNCTIONS[i].Name, technic_name) == 0) {
         OVTx_technic_FUNCTIONS[i].Address = NULL;
         _ret = PVR_TRUE;
         break;
      }
   }

   return _ret;
}
VECTORAPI pvr_techniq_func*  APIENTRY  pvr_techniq_get(pvr_string_t technic_name){
   pvr_techniq_func* _ret = NULL;
   
   for(pvr_schar_t i = 0; i < 8; i++) {
      if(strcmp(OVTx_technic_FUNCTIONS[i].Name, technic_name) == 0) {
         _ret = OVTx_technic_FUNCTIONS[i].Address;
         break;
      }
   }

   return _ret;
}
VECTORAPI pvr_pointer_t APIENTRY  pvr_techniq_get_func(pvr_string_t technic_name, pvr_string_t funcName){
   pvr_techniq_func* _func = pvr_techniq_get(technic_name);
   if(_func == NULL) return 0;

   return _func(funcName);
}
