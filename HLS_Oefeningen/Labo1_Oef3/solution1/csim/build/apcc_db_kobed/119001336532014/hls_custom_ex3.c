/* Provide Declarations */
#include <stdarg.h>
#include <setjmp.h>
#include <limits.h>
#ifdef NEED_CBEAPINT
#include <autopilot_cbe.h>
#else
#define aesl_fopen fopen
#define aesl_freopen freopen
#define aesl_tmpfile tmpfile
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifdef __STRICT_ANSI__
#define inline __inline__
#define typeof __typeof__ 
#endif
#define __isoc99_fscanf fscanf
#define __isoc99_sscanf sscanf
#undef ferror
#undef feof
/* get a declaration for alloca */
#if defined(__CYGWIN__) || defined(__MINGW32__)
#define  alloca(x) __builtin_alloca((x))
#define _alloca(x) __builtin_alloca((x))
#elif defined(__APPLE__)
extern void *__builtin_alloca(unsigned long);
#define alloca(x) __builtin_alloca(x)
#define longjmp _longjmp
#define setjmp _setjmp
#elif defined(__sun__)
#if defined(__sparcv9)
extern void *__builtin_alloca(unsigned long);
#else
extern void *__builtin_alloca(unsigned int);
#endif
#define alloca(x) __builtin_alloca(x)
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__arm__)
#define alloca(x) __builtin_alloca(x)
#elif defined(_MSC_VER)
#define inline _inline
#define alloca(x) _alloca(x)
#else
#include <alloca.h>
#endif

#ifndef __GNUC__  /* Can only support "linkonce" vars with GCC */
#define __attribute__(X)
#endif

#if defined(__GNUC__) && defined(__APPLE_CC__)
#define __EXTERNAL_WEAK__ __attribute__((weak_import))
#elif defined(__GNUC__)
#define __EXTERNAL_WEAK__ __attribute__((weak))
#else
#define __EXTERNAL_WEAK__
#endif

#if defined(__GNUC__) && (defined(__APPLE_CC__) || defined(__CYGWIN__) || defined(__MINGW32__))
#define __ATTRIBUTE_WEAK__
#elif defined(__GNUC__)
#define __ATTRIBUTE_WEAK__ __attribute__((weak))
#else
#define __ATTRIBUTE_WEAK__
#endif

#if defined(__GNUC__)
#define __HIDDEN__ __attribute__((visibility("hidden")))
#endif

#ifdef __GNUC__
#define LLVM_NAN(NanStr)   __builtin_nan(NanStr)   /* Double */
#define LLVM_NANF(NanStr)  __builtin_nanf(NanStr)  /* Float */
#define LLVM_NANS(NanStr)  __builtin_nans(NanStr)  /* Double */
#define LLVM_NANSF(NanStr) __builtin_nansf(NanStr) /* Float */
#define LLVM_INF           __builtin_inf()         /* Double */
#define LLVM_INFF          __builtin_inff()        /* Float */
#define LLVM_PREFETCH(addr,rw,locality) __builtin_prefetch(addr,rw,locality)
#define __ATTRIBUTE_CTOR__ __attribute__((constructor))
#define __ATTRIBUTE_DTOR__ __attribute__((destructor))
#define LLVM_ASM           __asm__
#else
#define LLVM_NAN(NanStr)   ((double)0.0)           /* Double */
#define LLVM_NANF(NanStr)  0.0F                    /* Float */
#define LLVM_NANS(NanStr)  ((double)0.0)           /* Double */
#define LLVM_NANSF(NanStr) 0.0F                    /* Float */
#define LLVM_INF           ((double)0.0)           /* Double */
#define LLVM_INFF          0.0F                    /* Float */
#define LLVM_PREFETCH(addr,rw,locality)            /* PREFETCH */
#define __ATTRIBUTE_CTOR__
#define __ATTRIBUTE_DTOR__
#define LLVM_ASM(X)
#endif

#if __GNUC__ < 4 /* Old GCC's, or compilers not GCC */ 
#define __builtin_stack_save() 0   /* not implemented */
#define __builtin_stack_restore(X) /* noop */
#endif

#if __GNUC__ && __LP64__ /* 128-bit integer types */
typedef int __attribute__((mode(TI))) llvmInt128;
typedef unsigned __attribute__((mode(TI))) llvmUInt128;
#endif

#define CODE_FOR_MAIN() /* Any target-specific code for main()*/

#ifndef __cplusplus
typedef unsigned char bool;
#endif


/* Support for floating point constants */
typedef unsigned long long ConstantDoubleTy;
typedef unsigned int        ConstantFloatTy;
typedef struct { unsigned long long f1; unsigned short f2; unsigned short pad[3]; } ConstantFP80Ty;
typedef struct { unsigned long long f1; unsigned long long f2; } ConstantFP128Ty;


/* Global Declarations */
/* Helper union for bitcasts */
typedef union {
  unsigned int Int32;
  unsigned long long Int64;
  float Float;
  double Double;
} llvmBitCastUnion;

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
void CombLogic_Custom(bool llvm_cbe_A_in, bool llvm_cbe_B_in, bool llvm_cbe_C_in, bool *llvm_cbe_Out1, bool *llvm_cbe_Out2);


/* Function Bodies */
static inline int llvm_fcmp_ord(double X, double Y) { return X == X && Y == Y; }
static inline int llvm_fcmp_uno(double X, double Y) { return X != X || Y != Y; }
static inline int llvm_fcmp_ueq(double X, double Y) { return X == Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_une(double X, double Y) { return X != Y; }
static inline int llvm_fcmp_ult(double X, double Y) { return X <  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ugt(double X, double Y) { return X >  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ule(double X, double Y) { return X <= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_uge(double X, double Y) { return X >= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_oeq(double X, double Y) { return X == Y ; }
static inline int llvm_fcmp_one(double X, double Y) { return X != Y && llvm_fcmp_ord(X, Y); }
static inline int llvm_fcmp_olt(double X, double Y) { return X <  Y ; }
static inline int llvm_fcmp_ogt(double X, double Y) { return X >  Y ; }
static inline int llvm_fcmp_ole(double X, double Y) { return X <= Y ; }
static inline int llvm_fcmp_oge(double X, double Y) { return X >= Y ; }

void CombLogic_Custom(bool llvm_cbe_A_in, bool llvm_cbe_B_in, bool llvm_cbe_C_in, bool *llvm_cbe_Out1, bool *llvm_cbe_Out2) {
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_brmerge17_count = 0;
  bool llvm_cbe_brmerge17;
  static  unsigned long long aesl_llvm_cbe_brmerge_2e_not18_count = 0;
  bool llvm_cbe_brmerge_2e_not18;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  bool llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe__2e__count = 0;
  bool llvm_cbe__2e_;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  static  unsigned long long aesl_llvm_cbe_brmerge12_count = 0;
  bool llvm_cbe_brmerge12;
  static  unsigned long long aesl_llvm_cbe_brmerge_2e_not13_count = 0;
  bool llvm_cbe_brmerge_2e_not13;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_brmerge_count = 0;
  bool llvm_cbe_brmerge;
  static  unsigned long long aesl_llvm_cbe_brmerge_2e_not_count = 0;
  bool llvm_cbe_brmerge_2e_not;
  static  unsigned long long aesl_llvm_cbe_A_in_2e_not_count = 0;
  bool llvm_cbe_A_in_2e_not;
  static  unsigned long long aesl_llvm_cbe_brmerge8_count = 0;
  bool llvm_cbe_brmerge8;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_9_2e_demorgan_count = 0;
  bool llvm_cbe__2e_9_2e_demorgan;
  static  unsigned long long aesl_llvm_cbe__2e_9_count = 0;
  bool llvm_cbe__2e_9;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  bool llvm_cbe_tmp__2;
  bool llvm_cbe_tmp__2__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  bool llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @CombLogic_Custom\n");
  if (llvm_cbe_A_in) {
    goto llvm_cbe__2e_thread;
  } else {
    goto llvm_cbe_tmp__4;
  }

llvm_cbe_tmp__4:
  if (llvm_cbe_B_in) {
    goto llvm_cbe__2e_thread2;
  } else {
    goto llvm_cbe_tmp__5;
  }

llvm_cbe_tmp__5:
  if (llvm_cbe_C_in) {
    goto llvm_cbe__2e_thread10;
  } else {
    goto llvm_cbe__2e_thread16;
  }

llvm_cbe__2e_thread16:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 false, i1* %%Out1, align  for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_26_count);
  *llvm_cbe_Out1 = ((0) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 0);
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge17 = or i1 %%B_in, %%C_in, !dbg !2 for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_brmerge17_count);
  llvm_cbe_brmerge17 = (bool )((llvm_cbe_B_in | llvm_cbe_C_in)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge17 = 0x%X\n", llvm_cbe_brmerge17);
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge.not18 = xor i1 %%brmerge17, true, !dbg !2 for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_brmerge_2e_not18_count);
  llvm_cbe_brmerge_2e_not18 = (bool )((llvm_cbe_brmerge17 ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge.not18 = 0x%X\n", llvm_cbe_brmerge_2e_not18);
  llvm_cbe_tmp__2__PHI_TEMPORARY = (bool )llvm_cbe_brmerge_2e_not18;   /* for PHI node */
  goto llvm_cbe_tmp__6;

llvm_cbe__2e_thread10:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 true, i1* %%Out1, align  for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_28_count);
  *llvm_cbe_Out1 = ((1) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 1);
  goto llvm_cbe__2e_thread11;

llvm_cbe__2e_thread2:
  if (llvm_cbe_C_in) {
    goto llvm_cbe_tmp__7;
  } else {
    goto llvm_cbe_tmp__8;
  }

llvm_cbe__2e_thread:
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = xor i1 %%C_in, true, !dbg !2 for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_31_count);
  llvm_cbe_tmp__1 = (bool )((llvm_cbe_C_in ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__1);
if (AESL_DEBUG_TRACE)
printf("\n  %%. = and i1 %%B_in, %%3, !dbg !2 for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe__2e__count);
  llvm_cbe__2e_ = (bool )((llvm_cbe_B_in & llvm_cbe_tmp__1)&1);
if (AESL_DEBUG_TRACE)
printf("\n. = 0x%X\n", llvm_cbe__2e_);
if (AESL_DEBUG_TRACE)
printf("\n  store i1 %%., i1* %%Out1, align  for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_32_count);
  *llvm_cbe_Out1 = ((llvm_cbe__2e_) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n. = 0x%X\n", llvm_cbe__2e_);
  goto llvm_cbe__2e_thread7;

llvm_cbe_tmp__8:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 true, i1* %%Out1, align  for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_34_count);
  *llvm_cbe_Out1 = ((1) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 1);
  if (llvm_cbe_A_in) {
    goto llvm_cbe__2e_thread7;
  } else {
    goto llvm_cbe__2e_thread11;
  }

llvm_cbe__2e_thread11:
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge12 = or i1 %%B_in, %%C_in, !dbg !2 for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_brmerge12_count);
  llvm_cbe_brmerge12 = (bool )((llvm_cbe_B_in | llvm_cbe_C_in)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge12 = 0x%X\n", llvm_cbe_brmerge12);
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge.not13 = xor i1 %%brmerge12, true, !dbg !2 for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_brmerge_2e_not13_count);
  llvm_cbe_brmerge_2e_not13 = (bool )((llvm_cbe_brmerge12 ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge.not13 = 0x%X\n", llvm_cbe_brmerge_2e_not13);
  llvm_cbe_tmp__2__PHI_TEMPORARY = (bool )llvm_cbe_brmerge_2e_not13;   /* for PHI node */
  goto llvm_cbe_tmp__6;

llvm_cbe_tmp__7:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 false, i1* %%Out1, align  for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_37_count);
  *llvm_cbe_Out1 = ((0) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 0);
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge = or i1 %%B_in, %%C_in, !dbg !2 for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_brmerge_count);
  llvm_cbe_brmerge = (bool )((llvm_cbe_B_in | llvm_cbe_C_in)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge = 0x%X\n", llvm_cbe_brmerge);
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge.not = xor i1 %%brmerge, true, !dbg !2 for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_brmerge_2e_not_count);
  llvm_cbe_brmerge_2e_not = (bool )((llvm_cbe_brmerge ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge.not = 0x%X\n", llvm_cbe_brmerge_2e_not);
if (AESL_DEBUG_TRACE)
printf("\n  %%A_in.not = xor i1 %%A_in, true, !dbg !2 for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_A_in_2e_not_count);
  llvm_cbe_A_in_2e_not = (bool )((llvm_cbe_A_in ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\nA_in.not = 0x%X\n", llvm_cbe_A_in_2e_not);
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge8 = or i1 %%brmerge.not, %%A_in.not, !dbg !2 for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_brmerge8_count);
  llvm_cbe_brmerge8 = (bool )((llvm_cbe_brmerge_2e_not | llvm_cbe_A_in_2e_not)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge8 = 0x%X\n", llvm_cbe_brmerge8);
  if (llvm_cbe_brmerge8) {
    llvm_cbe_tmp__2__PHI_TEMPORARY = (bool )llvm_cbe_brmerge_2e_not;   /* for PHI node */
    goto llvm_cbe_tmp__6;
  } else {
    goto llvm_cbe__2e_thread7;
  }

llvm_cbe__2e_thread7:
if (AESL_DEBUG_TRACE)
printf("\n  %%.9.demorgan = or i1 %%B_in, %%C_in, !dbg !2 for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe__2e_9_2e_demorgan_count);
  llvm_cbe__2e_9_2e_demorgan = (bool )((llvm_cbe_B_in | llvm_cbe_C_in)&1);
if (AESL_DEBUG_TRACE)
printf("\n.9.demorgan = 0x%X\n", llvm_cbe__2e_9_2e_demorgan);
if (AESL_DEBUG_TRACE)
printf("\n  %%.9 = xor i1 %%.9.demorgan, true, !dbg !2 for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe__2e_9_count);
  llvm_cbe__2e_9 = (bool )((llvm_cbe__2e_9_2e_demorgan ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\n.9 = 0x%X\n", llvm_cbe__2e_9);
  llvm_cbe_tmp__2__PHI_TEMPORARY = (bool )llvm_cbe__2e_9;   /* for PHI node */
  goto llvm_cbe_tmp__6;

llvm_cbe_tmp__6:
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = phi i1 [ %%brmerge.not, %%5 ], [ %%.9, %%.thread7 ], [ %%brmerge.not13, %%.thread11 ], [ %%brmerge.not18, %%.thread16  for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_40_count);
  llvm_cbe_tmp__2 = (bool )((llvm_cbe_tmp__2__PHI_TEMPORARY)&1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__2);
printf("\nbrmerge.not = 0x%X",llvm_cbe_brmerge_2e_not);
printf("\n.9 = 0x%X",llvm_cbe__2e_9);
printf("\nbrmerge.not13 = 0x%X",llvm_cbe_brmerge_2e_not13);
printf("\nbrmerge.not18 = 0x%X",llvm_cbe_brmerge_2e_not18);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = xor i1 %%7, tru for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_41_count);
  llvm_cbe_tmp__3 = (bool )((llvm_cbe_tmp__2 ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__3);
if (AESL_DEBUG_TRACE)
printf("\n  store i1 %%8, i1* %%Out2, align  for 0x%I64xth hint within @CombLogic_Custom  --> \n", ++aesl_llvm_cbe_42_count);
  *llvm_cbe_Out2 = ((llvm_cbe_tmp__3) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__3);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @CombLogic_Custom}\n");
  return;
}

