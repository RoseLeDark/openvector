#ifndef __vector_platform_h 
#define __vector_platform_h 1

#define PVCTR_TARGET_WINDOWS           0
#define PVCTR_TARGET_LINUX             1
#define PVCTR_TARGET_ANDROID           2

#define PVCTR_COMPILER_MSVC            1 
#define PVCTR_COMPILER_CLANGCL         2
#define PVCTR_COMPILER_INTEL           3
#define PVCTR_COMPILER_INTEL_LLVM      4
#define PVCTR_COMPILER_GCC             5

#define PVCTR_ARCH_X86_32              1
#define PVCTR_ARCH_X86_64              2
#define PVCTR_ARCH_PPC                 3
#define PVCTR_ARCH_PPC_64              4
#define PVCTR_ARCH_ARM                 5
#define PVCTR_ARCH_ARM64               6
#define PVCTR_ARCH_LOONGARCH64         7
#define PVCTR_ARCH_LOONGARCH32         8
#define PVCTR_ARCH_RISCV32             9
#define PVCTR_ARCH_RISCV64            10

#define PVCTR_LITTLE_ENDIAN            1
#define PVCTR_BIG_ENDIAN               0

#define PVCTR_TECHNIQ_FALLBACK      0

#define PVCTR_TECHNIQ_X64_NONE      PVCTR_TECHNIQ_FALLBACK
#define PVCTR_TECHNIQ_X64_SSE2      1
#define PVCTR_TECHNIQ_X64_SSE3      2
#define PVCTR_TECHNIQ_X64_SSE41     3
#define PVCTR_TECHNIQ_X64_SSE42     4
#define PVCTR_TECHNIQ_X64_AVX       5
#define PVCTR_TECHNIQ_X64_AVX2      6
#define PVCTR_TECHNIQ_X64_AVX512    7
//arm
#define PVCTR_TECHNIQ_ARM_NONE      PVCTR_TECHNIQ_FALLBACK
#define PVCTR_TECHNIQ_ARM_NEON      1
#define PVCTR_TECHNIQ_ARM_NEON64    2
#define PVCTR_TECHNIQ_ARM_SVE       3
#define PVCTR_TECHNIQ_ARM_SVE2      4

#define PVCTR_TECHNIQ_RISCV_NONE      PVCTR_TECHNIQ_FALLBACK

#define PVCTR_TECHNIQ_LARCH_NONE      PVCTR_TECHNIQ_FALLBACK

#define PVCTR_TECHNIQ_EXT_NONE      PVCTR_TECHNIQ_FALLBACK
#define PVCTR_TECHNIQ_EXT_VULKAN    1
#define PVCTR_TECHNIQ_EXT_OPENCL    2
#define PVCTR_TECHNIQ_EXT_USER      10

///////// DO NOT EDIT AFTER THIS!!!!! 

#if defined(_WIN32)
    #define PVCTR_TARGET_SYSTEM PVCTR_TARGET_WINDOWS
#elif defined(__ANDROID__)
    #define PVCTR_TARGET_SYSTEM PVCTR_TARGET_ANDROID
#elif (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__) || defined(__SCO__) || defined(__USLC__)
    #define PVCTR_TARGET_SYSTEM PVCTR_TARGET_LINUX
#endif

#if !defined(PVCTR_TARGET_SYSTEM)
#error "No compatibler OS found!"
#endif //!defined(PVCTR_TARGET_SYSTEM)

#if PVCTR_TARGET_SYSTEM == PVCTR_TARGET_WINDOWS && !defined(__clang__)
#define PVCTR_COMPILER_USED     PVCTR_COMPILER_MSVC
#endif //PVCTR_TARGET_SYSTEM == PVCTR_TARGET_WINDOWS && !defined(__clang__)

#if PVCTR_TARGET_SYSTEM == PVCTR_TARGET_WINDOWS && defined(__clang__)
#define PVCTR_COMPILER_USED     PVCTR_COMPILER_CLANGCL
#endif

#ifdef __INTEL_COMPILER
#define PVCTR_COMPILER_USED     PVCTR_COMPILER_INTEL
#endif

#ifdef __INTEL_LLVM_COMPILER
#define PVCTR_COMPILER_USED     PVCTR_COMPILER_INTEL_LLVM
#endif

#ifdef __GNUC__
#define PVCTR_COMPILER_USED     PVCTR_COMPILER_GCC
#endif


#if !defined(PVCTR_COMPILER_USED)
#error "No compatibler compiler found!"
#endif

// -- ARCH
#if defined(__i386__) || defined(_M_IX86)
#define PVCTR_ARCH_USED             PVCTR_ARCH_X86_32  
#endif

#if defined(__x86_64__) || defined(_M_X64)
#define PVCTR_ARCH_USED             PVCTR_ARCH_X86_64  
#endif


#if defined(__powerpc64__) || defined(_M_PPC) || defined(__powerpc__)
#define PVCTR_ARCH_USED             PVCTR_ARCH_PPC  
#endif

#if defined(__powerpc64__) || (PVCTR_ARCH_PPC && defined(__64BIT__))
#define PVCTR_ARCH_USED             PVCTR_ARCH_PPC_64  
#endif

#if defined(__arm__) 
#define PVCTR_ARCH_USED             PVCTR_ARCH_ARM
#endif

#if defined(__riscv) && __riscv_xlen == 32
#define PVCTR_ARCH_USED             PVCTR_ARCH_RISCV32
#endif

#if defined(__riscv) && __riscv_xlen == 64
#define PVCTR_ARCH_USED             PVCTR_ARCH_RISCV64
#endif


#if defined(__loongarch64__) || defined(__loongarch64) || \
    (defined(__loongarch_grlen) && __loongarch_grlen == 64)
    #define PVCTR_ARCH_USED             PVCTR_ARCH_LOONGARCH64
#endif

#if defined(__loongarch__) && PVCTR_ARCH_USED != PVCTR_ARCH_LOONGARCH64
#define PVCTR_ARCH_USED             PVCTR_ARCH_LOONGARCH32
#endif

#if !defined(PVCTR_ARCH_USED)
#error "Must not detect more than one architecture"
#endif

// ORDER
#if PVCTR_COMPILER_USED   ==  PVCTR_COMPILER_MSVC
#if PVCTR_ARCH_PPC && defined(_XBOX_VER) && _XBOX_VER >= 200
// XBox 360 is big-endian
    #define PVCTR_BYTE_ORDER   PVCTR_BIG_ENDIAN
#else
    #define PVCTR_BYTE_ORDER   PVCTR_LITTLE_ENDIAN
#endif  // PVCTR_ARCH_PPC && defined(_XBOX_VER) && _XBOX_VER >= 200
#elif defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define PVCTR_BYTE_ORDER   PVCTR_LITTLE_ENDIAN
#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    #define PVCTR_BYTE_ORDER   PVCTR_BIG_ENDIAN
#else
#error "Unable to detect endianness or unsupported byte order"
#endif

#if !defined(PVCTR_BYTE_ORDER )
#error "Must only detect one byte order"
#endif

// SIMD
#include "PVCTRTsimd.h"

// ------------------------------ HWY_ARCH_X86
#if (PVCTR_ARCH_USED == PVCTR_ARCH_X86_64) ||  (PVCTR_ARCH_USED == PVCTR_ARCH_X86_32)

#if (PVCTR_SIMD_HAVE_SSE2    == 1) 
#undef PVCTR_TECHNIQ_USED  
#define PVCTR_TECHNIQ_USED     PVCTR_TECHNIQ_X64_SSE2
#endif

#if (PVCTR_SIMD_HAVE_SSE3 == 1) 
#undef PVCTR_TECHNIQ_USED  
#define PVCTR_TECHNIQ_USED     PVCTR_TECHNIQ_X64_SSE3
#endif

#if (PVCTR_SIMD_HAVE_SSE4_1 == 1) 
#undef PVCTR_TECHNIQ_USED  
#define PVCTR_TECHNIQ_USED     PVCTR_TECHNIQ_X64_SSE41
#endif

#if (PVCTR_SIMD_HAVE_SSE4_2 == 1) 
#undef PVCTR_TECHNIQ_USED  
#define PVCTR_TECHNIQ_USED     PVCTR_TECHNIQ_X64_SSE42
#endif

#if (PVCTR_SIMD_HAVE_AVX == 1) 
#undef PVCTR_TECHNIQ_USED  
#define PVCTR_TECHNIQ_USED     PVCTR_TECHNIQ_X64_AVX
#endif

#if (PVCTR_SIMD_HAVE_AVX2 == 1) 
#undef PVCTR_TECHNIQ_USED  
#define PVCTR_TECHNIQ_USED     PVCTR_TECHNIQ_X64_AVX2
#endif

#if (PVCTR_SIMD_HAVE_AVX512BW == 1) 
#undef PVCTR_TECHNIQ_USED  
#define PVCTR_TECHNIQ_USED     PVCTR_TECHNIQ_X64_AVX512
#endif

#endif // (PVCTR_COMPILER_USED == PVCTR_ARCH_X86_64) ||  (PVCTR_COMPILER_USED == PVCTR_ARCH_X86_32)

// ARM
#if (PVCTR_ARCH_USED == PVCTR_ARCH_ARM) ||  (PVCTR_ARCH_USED == PVCTR_ARCH_ARM64)

#if (__ARM_NEON == 1) 
#undef PVCTR_TECHNIQ_USED  
    #if PVCTR_ARCH_USED == PVCTR_ARCH_ARM
        #define PVCTR_TECHNIQ_USED     PVCTR_TECHNIQ_ARM_NEON
    #else
        #define PVCTR_TECHNIQ_USED     PVCTR_TECHNIQ_ARM_NEON64
    #endif //  PVCTR_ARCH_USED == PVCTR_ARCH_ARM
#endif

#if (PVCTR_SIMD_HAVE_SVE == 1) 
#undef PVCTR_TECHNIQ_USED  
#define PVCTR_TECHNIQ_USED     PVCTR_TECHNIQ_ARM_SVE
#endif

#if (PVCTR_SIMD_HAVE_SVE2 == 1) 
#undef PVCTR_TECHNIQ_USED  
#define PVCTR_TECHNIQ_USED     PVCTR_TECHNIQ_ARM_SVE2
#endif

#endif // (PVCTR_ARCH_USED == PVCTR_ARCH_ARM) ||  (PVCTR_ARCH_USED == PVCTR_ARCH_ARM64)

#ifndef PVCTR_TECHNIQ_USED
#define PVCTR_TECHNIQ_USED PVCTR_TECHNIQ_FALLBACK
#endif



#if __cplusplus >= 201703L
# define PVCTR_DEFINE_STATIC_MEMBER_ inline
#elif (PVCTR_TARGET_SYSTEM == PVCTR_TARGET_WINDOWS) 
# define PVCTR_DEFINE_STATIC_MEMBER_ __declspec(selectany)
#elif defined(__MINGW32__)
# define PVCTR_EFINE_STATIC_MEMBER_ __attribute__((selectany))
#else
# define PVCTR_DEFINE_STATIC_MEMBER_ __attribute__((weak))
#endif // !_MSC_VER

#endif