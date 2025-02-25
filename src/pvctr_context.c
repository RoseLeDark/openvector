//  SPDX-FileCopyrightText: 2025 Amber-Sophia Schröck 
//  SPDX-License-Identifier: MIT

#define PVCTR_PROTOTYPES 1
#include "PVCTR.h"
#include <string.h>

#if (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_WINDOWS)
#include <stdio.h>
#include <intrin.h>  // Windows CPUID
#endif
#if (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_LINUX)
#include <cpuid.h>
#endif

struct pvr_context {
    pvr_string_t technic_name;
    pvr_techniq_func* techniq_proc;

    pvr_schar_t last_api_error;
};

#if (PVCTR_ARCH_USED == PVCTR_ARCH_X86_64) ||  (PVCTR_ARCH_USED == PVCTR_ARCH_X86_32)
// Funktion zum Testen der höchsten verfügbaren SIMD-Erweiterung
pvr_uchar_t pvr_context_highest_tech(const pvr_uchar_t requested_api) {
   
    unsigned int cpuInfo[4] = {0};

#if (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_LINUX)
    __get_cpuid(1, &cpuInfo[0], &cpuInfo[1], &cpuInfo[2], &cpuInfo[3]);
    int code = 1;
    // CPUID aufrufen
    __asm__ __volatile__("cpuid"
            : "=a"(cpuInfo[0]), "=b"(cpuInfo[1]), "=c"(cpuInfo[2]), "=d"(cpuInfo[3])  // Ausgabe in cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3]
            : "a"(code));  // Eingabewert für CPUID (1 für Feature-Flags)
#elif (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_WINDOWS)
    __cpuid(cpuInfo, 1);
#endif
    pvr_uchar_t _testval = requested_api;
    // Prüfen der verfügbaren Erweiterungen
    while (_testval > PVCTR_TECHNIQ_FALLBACK) {
        switch (_testval) {
            case PVCTR_TECHNIQ_X64_AVX512:if (cpuInfo[1] & bit_AVX512F) return PVCTR_TECHNIQ_X64_AVX512; break;
            case PVCTR_TECHNIQ_X64_AVX2:  if (cpuInfo[1] & bit_AVX2) return PVCTR_TECHNIQ_X64_AVX2; break;
            case PVCTR_TECHNIQ_X64_AVX:   if (cpuInfo[2] & bit_AVX) return PVCTR_TECHNIQ_X64_AVX; break;
            case PVCTR_TECHNIQ_X64_SSE42: if (cpuInfo[2] & bit_SSE4_2) return PVCTR_TECHNIQ_X64_SSE42; break;
            case PVCTR_TECHNIQ_X64_SSE41: if (cpuInfo[2] & bit_SSE4_1)  return PVCTR_TECHNIQ_X64_SSE41; break;
            case PVCTR_TECHNIQ_X64_SSE3:  if (cpuInfo[2] & bit_SSE3)  return PVCTR_TECHNIQ_X64_SSE3; break;
            case PVCTR_TECHNIQ_X64_SSE2:  if (cpuInfo[3] & bit_SSE2)  return PVCTR_TECHNIQ_X64_SSE2;  break;
            default: return PVCTR_TECHNIQ_FALLBACK;
        }
        _testval--;  // Wenn nicht unterstützt, zur nächstniedrigeren Version wechseln
    }
    
    // Wenn alle Erweiterungen überprüft wurden und keine unterstützt wird
    return PVCTR_TECHNIQ_FALLBACK;
}


#elif (PVCTR_ARCH_USED == PVCTR_ARCH_ARM) ||  (PVCTR_ARCH_USED == PVCTR_ARCH_ARM64)
pvr_uchar_t pvr_context_highest_tech(const pvr_uchar_t requested_api) {
    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo == NULL) {
        return PVCTR_TECHNIQ_ARM_NONE; // Keine CPU-Informationen verfügbar
    }

    char line[256];
    int neon32_supported = 0;
    int neon64_supported = 0;
    int sve_supported = 0;
    int sve2_supported = 0;
    int armv8_supported = 0;  // ARMv8+ für NEON64 und SVE

    // Durchlaufe jede Zeile von cpuinfo
    while (fgets(line, sizeof(line), cpuinfo)) {
        // Prüfen auf ARMv8 und höher (NEON64, SVE)
        if (strstr(line, "AArch64") != NULL) {
            armv8_supported = 1;  // 64-Bit-Architektur ARMv8 oder höher gefunden
        }

        // Prüfen, ob NEON32 (32-Bit) verfügbar ist
        if (strstr(line, "neon") != NULL && !armv8_supported) {
            neon32_supported = 1;
        }

        // Prüfen, ob NEON64 verfügbar ist (falls ARMv8 oder höher)
        if (strstr(line, "neon") != NULL && armv8_supported) {
            neon64_supported = 1;
        }

        // Prüfen auf SVE-Unterstützung (ARMv8.2+)
        if (strstr(line, "sve") != NULL) {
            sve_supported = 1;
        }

        // Prüfen auf SVE2-Unterstützung
        if (strstr(line, "sve2") != NULL) {
            sve2_supported = 1;
        }
    }

    fclose(cpuinfo);

    pvr_schar_t _ret = -1;
    pvr_uchar_t _testval = requested_api;
    // Prüfen der gewünschten Technik und Rückgabe
    while (_testval > PVCTR_TECHNIQ_ARM_NONE) {
        switch (_testval) {
            case PVCTR_TECHNIQ_ARM_SVE2:
                if (sve2_supported) return PVCTR_TECHNIQ_ARM_SVE2;
                break;
            case PVCTR_TECHNIQ_ARM_SVE:
                if (sve_supported) return PVCTR_TECHNIQ_ARM_SVE;
                break;
            case PVCTR_TECHNIQ_ARM_NEON64:
                if (neon64_supported) return PVCTR_TECHNIQ_ARM_NEON64;
                break;
            case PVCTR_TECHNIQ_ARM_NEON32:
                if (neon32_supported) return PVCTR_TECHNIQ_ARM_NEON32;
                break;
            default:
                return PVCTR_TECHNIQ_ARM_NONE;  // Wenn keine Unterstützung gefunden, zurück zum Fallback
        };
        _testval--;
    }

    // Wenn keine Technik unterstützt wird, zurück zum Fallback
    return PVCTR_TECHNIQ_ARM_NONE;
}
#endif 

VECTORAPI pvr_schar_t APIENTRY pvr_context_create(const pvr_uchar_t id,  const void* args, pvr_context_t* context) {
    if(context == NULL) return PVCTR_ERROR_NULL_PTR;
    pvr_schar_t used  = pvr_context_highest_tech(id);
    pvr_schar_t _ret = 0;
    switch (used)  {
    case PVCTR_TECHNIQ_X64_AVX512:
        _ret = pvr_context_createex("AVX2-System", args, context); break;
    case PVCTR_TECHNIQ_X64_AVX2:
        _ret = pvr_context_createex("AVX2-System", args, context); break;
    case PVCTR_TECHNIQ_X64_AVX:
        _ret = pvr_context_createex("AVX-System", args, context); break;
    case PVCTR_TECHNIQ_X64_SSE42:
        _ret = pvr_context_createex("SSE42-System", args, context); break;
    case PVCTR_TECHNIQ_X64_SSE41:
        _ret = pvr_context_createex("SSE41-System", args, context); break;
    case PVCTR_TECHNIQ_X64_SSE3:
        _ret = pvr_context_createex("SSE3-System", args, context); break;
    case PVCTR_TECHNIQ_X64_SSE2:
        _ret = pvr_context_createex("SSE2-System", args, context); break;
    default:
        _ret =pvr_context_createex("CPU", args, context); break;
    }
    return _ret;
}

VECTORAPI pvr_schar_t APIENTRY pvr_context_createex(const pvr_string_t technic_name, const void* args, pvr_context_t* context) {
    if(context == NULL) return PVCTR_ERROR_NULL_PTR;
    if(pvr_techniq_avaible(technic_name) != PVR_TRUE) { return PVCTR_ERROR_NSUPPORT; }

    pvr_techniq_func* techniq_proc = pvr_techniq_get(technic_name);
    if(techniq_proc == NULL) { return PVCTR_ERROR_NSUPPORT; }

    pvr_techniq_create_simd *tech_create = techniq_proc("pvr_techniq_create");
    if(tech_create != NULL) { 
        context->last_api_error = tech_create(args);
    }

    context->technic_name = technic_name;
    context->techniq_proc = techniq_proc;

    return  PVCTR_OK;
}

VECTORAPI pvr_schar_t APIENTRY pvr_context_api_geterror(const pvr_context_t* context) {
    if(context == NULL) return PVCTR_ERROR_NULL_PTR;

    return context->last_api_error;
}