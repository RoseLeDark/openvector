#ifndef __vector_simd_h_
#define __vector_simd_h_ 1

//ARM

#if defined __ARM_NEON
#define PVCTR_SIMD_HAVE_NEON 1
#else
#define PVCTR_SIMD_HAVE_NEON 0
#endif
#if defined __ARM_NEON && (__ARM_ARCH >= 8 || defined __aarch64__)
#define PVCTR_SIMD_HAVE_NEON_A32 1
#else
#define PVCTR_SIMD_HAVE_NEON_A32 0
#endif
#if defined __ARM_NEON && defined __aarch64__
#define PVCTR_SIMD_HAVE_NEON_A64 1
#else
#define PVCTR_SIMD_HAVE_NEON_A64 0
#endif
#if (__ARM_FEATURE_SVE_BITS > 0 && __ARM_FEATURE_SVE_VECTOR_OPERATORS==1)
#define PVCTR_SIMD_HAVE_SVE 1
#else
#define PVCTR_SIMD_HAVE_SVE 0
#endif
#ifdef __ARM_FEATURE_SVE2
#define PVCTR_SIMD_HAVE_SVE2 1
#else
#define PVCTR_SIMD_HAVE_SVE2 0
#endif


#ifdef __MMX__
#define PVCTR_SIMD_HAVE_MMX 1
#else
#define PVCTR_SIMD_HAVE_MMX 0
#endif
#if defined __SSE__ || defined __x86_64__
#define PVCTR_SIMD_HAVE_SSE 1
#else
#define PVCTR_SIMD_HAVE_SSE 0
#endif
#if defined __SSE2__ || defined __x86_64__
#define PVCTR_SIMD_HAVE_SSE2 1
#else
#define PVCTR_SIMD_HAVE_SSE2 0
#endif
#ifdef __SSE3__
#define PVCTR_SIMD_HAVE_SSE3 1
#else
#define PVCTR_SIMD_HAVE_SSE3 0
#endif
#ifdef __SSSE3__
#define PVCTR_SIMD_HAVE_SSSE3 1
#else
#define PVCTR_SIMD_HAVE_SSSE3 0
#endif
#ifdef __SSE4_1__
#define PVCTR_SIMD_HAVE_SSE4_1 1
#else
#define PVCTR_SIMD_HAVE_SSE4_1 0
#endif
#ifdef __SSE4_2__
#define PVCTR_SIMD_HAVE_SSE4_2 1
#else
#define PVCTR_SIMD_HAVE_SSE4_2 0
#endif
#ifdef __XOP__
#define PVCTR_SIMD_HAVE_XOP 1
#else
#define PVCTR_SIMD_HAVE_XOP 0
#endif
#ifdef __AVX__
#define PVCTR_SIMD_HAVE_AVX 1
#else
#define PVCTR_SIMD_HAVE_AVX 0
#endif
#ifdef __AVX2__
#define PVCTR_SIMD_HAVE_AVX2 1
#else
#define PVCTR_SIMD_HAVE_AVX2 0
#endif
#ifdef __BMI__
#define PVCTR_SIMD_HAVE_BMI1 1
#else
#define PVCTR_SIMD_HAVE_BMI1 0
#endif
#ifdef __BMI2__
#define PVCTR_SIMD_HAVE_BMI2 1
#else
#define PVCTR_SIMD_HAVE_BMI2 0
#endif
#ifdef __LZCNT__
#define PVCTR_SIMD_HAVE_LZCNT 1
#else
#define PVCTR_SIMD_HAVE_LZCNT 0
#endif
#ifdef __SSE4A__
#define PVCTR_SIMD_HAVE_SSE4A 1
#else
#define PVCTR_SIMD_HAVE_SSE4A 0
#endif
#ifdef __FMA__
#define PVCTR_SIMD_HAVE_FMA 1
#else
#define PVCTR_SIMD_HAVE_FMA 0
#endif
#ifdef __FMA4__
#define PVCTR_SIMD_HAVE_FMA4 1
#else
#define PVCTR_SIMD_HAVE_FMA4 0
#endif
#ifdef __F16C__
#define PVCTR_SIMD_HAVE_F16C 1
#else
#define PVCTR_SIMD_HAVE_F16C 0
#endif
#ifdef __POPCNT__
#define PVCTR_SIMD_HAVE_POPCNT 1
#else
#define PVCTR_SIMD_HAVE_POPCNT 0
#endif
#ifdef __AVX512F__
#define PVCTR_SIMD_HAVE_AVX512F 1
#else
#define PVCTR_SIMD_HAVE_AVX512F 0
#endif
#ifdef __AVX512DQ__
#define PVCTR_SIMD_HAVE_AVX512DQ 1
#else
#define PVCTR_SIMD_HAVE_AVX512DQ 0
#endif
#ifdef __AVX512VL__
#define PVCTR_SIMD_HAVE_AVX512VL 1
#else
#define PVCTR_SIMD_HAVE_AVX512VL 0
#endif
#ifdef __AVX512BW__
#define PVCTR_SIMD_HAVE_AVX512BW 1
#else
#define PVCTR_SIMD_HAVE_AVX512BW 0
#endif
#ifdef __AVX512BITALG__
#define PVCTR_SIMD_HAVE_AVX512BITALG 1
#else
#define PVCTR_SIMD_HAVE_AVX512BITALG 0
#endif
#ifdef __AVX512VBMI2__
#define PVCTR_SIMD_HAVE_AVX512VBMI2 1
#else
#define PVCTR_SIMD_HAVE_AVX512VBMI2 0
#endif
#ifdef __AVX512VBMI__
#define PVCTR_SIMD_HAVE_AVX512VBMI 1
#else
#define PVCTR_SIMD_HAVE_AVX512VBMI 0
#endif
#ifdef __AVX512IFMA__
#define PVCTR_SIMD_HAVE_AVX512IFMA 1
#else
#define PVCTR_SIMD_HAVE_AVX512IFMA 0
#endif
#ifdef __AVX512CD__
#define PVCTR_SIMD_HAVE_AVX512CD 1
#else
#define PVCTR_SIMD_HAVE_AVX512CD 0
#endif
#ifdef __AVX512VNNI__
#define PVCTR_SIMD_HAVE_AVX512VNNI 1
#else
#define PVCTR_SIMD_HAVE_AVX512VNNI 0
#endif
#ifdef __AVX512VPOPCNTDQ__
#define PVCTR_SIMD_HAVE_AVX512VPOPCNTDQ 1
#else
#define PVCTR_SIMD_HAVE_AVX512VPOPCNTDQ 0
#endif
#ifdef __AVX512VP2INTERSECT__
#define PVCTR_SIMD_HAVE_AVX512VP2INTERSECT 1
#else
#define PVCTR_SIMD_HAVE_AVX512VP2INTERSECT 0
#endif

#if PVCTR_SIMD_HAVE_SSE
#define PVCTR_SIMD_HAVE_SSE_ABI 1
#else
#define PVCTR_SIMD_HAVE_SSE_ABI 0
#endif
#if PVCTR_SIMD_HAVE_SSE2
#define PVCTR_SIMD_HAVE_FULL_SSE_ABI 1
#else
#define PVCTR_SIMD_HAVE_FULL_SSE_ABI 0
#endif

#if PVCTR_SIMD_HAVE_AVX
#define PVCTR_SIMD_HAVE_AVX_ABI 1
#else
#define PVCTR_SIMD_HAVE_AVX_ABI 0
#endif
#if PVCTR_SIMD_HAVE_AVX2
#define PVCTR_SIMD_HAVE_FULL_AVX_ABI 1
#else
#define PVCTR_SIMD_HAVE_FULL_AVX_ABI 0
#endif

#if PVCTR_SIMD_HAVE_AVX512F
#define PVCTR_SIMD_HAVE_AVX512_ABI 1
#else
#define PVCTR_SIMD_HAVE_AVX512_ABI 0
#endif
#if PVCTR_SIMD_HAVE_AVX512BW
#define PVCTR_SIMD_HAVE_FULL_AVX512_ABI 1
#else
#define PVCTR_SIMD_HAVE_FULL_AVX512_ABI 0
#endif


#endif