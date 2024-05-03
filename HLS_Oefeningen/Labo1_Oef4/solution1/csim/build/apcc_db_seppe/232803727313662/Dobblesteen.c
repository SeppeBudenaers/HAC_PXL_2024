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
void Dobblesteen(bool llvm_cbe_BTN1, bool llvm_cbe_BTN2, bool llvm_cbe_BTN3, bool *llvm_cbe_LED4, bool *llvm_cbe_LED3, bool *llvm_cbe_LED2, bool *llvm_cbe_LED1);


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

void Dobblesteen(bool llvm_cbe_BTN1, bool llvm_cbe_BTN2, bool llvm_cbe_BTN3, bool *llvm_cbe_LED4, bool *llvm_cbe_LED3, bool *llvm_cbe_LED2, bool *llvm_cbe_LED1) {
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
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_28_2e_demorgan_count = 0;
  bool llvm_cbe__2e_28_2e_demorgan;
  static  unsigned long long aesl_llvm_cbe__2e_28_count = 0;
  bool llvm_cbe__2e_28;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_not_2e_BTN234_count = 0;
  bool llvm_cbe_not_2e_BTN234;
  static  unsigned long long aesl_llvm_cbe__2e__count = 0;
  bool llvm_cbe__2e_;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_BTN3_2e_not_count = 0;
  bool llvm_cbe_BTN3_2e_not;
  static  unsigned long long aesl_llvm_cbe_brmerge_count = 0;
  bool llvm_cbe_brmerge;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_brmerge50_2e_demorgan_count = 0;
  bool llvm_cbe_brmerge50_2e_demorgan;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_brmerge29_count = 0;
  bool llvm_cbe_brmerge29;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_not_2e_BTN233_count = 0;
  bool llvm_cbe_not_2e_BTN233;
  static  unsigned long long aesl_llvm_cbe__2e_1_count = 0;
  bool llvm_cbe__2e_1;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_BTN2_2e_not_count = 0;
  bool llvm_cbe_BTN2_2e_not;
  static  unsigned long long aesl_llvm_cbe_brmerge30_count = 0;
  bool llvm_cbe_brmerge30;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  static  unsigned long long aesl_llvm_cbe_brmerge53_2e_demorgan_count = 0;
  bool llvm_cbe_brmerge53_2e_demorgan;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_brmerge31_count = 0;
  bool llvm_cbe_brmerge31;
  static  unsigned long long aesl_llvm_cbe_brmerge31_2e_not_count = 0;
  bool llvm_cbe_brmerge31_2e_not;
  static  unsigned long long aesl_llvm_cbe_BTN1_2e_not_count = 0;
  bool llvm_cbe_BTN1_2e_not;
  static  unsigned long long aesl_llvm_cbe_brmerge32_count = 0;
  bool llvm_cbe_brmerge32;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_not_2e_BTN2_count = 0;
  bool llvm_cbe_not_2e_BTN2;
  static  unsigned long long aesl_llvm_cbe__2e_2_count = 0;
  bool llvm_cbe__2e_2;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  bool llvm_cbe_tmp__1;
  bool llvm_cbe_tmp__1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @Dobblesteen\n");
  if (llvm_cbe_BTN1) {
    goto llvm_cbe__2e_thread36;
  } else {
    goto llvm_cbe_tmp__2;
  }

llvm_cbe_tmp__2:
  if (llvm_cbe_BTN2) {
    goto llvm_cbe__2e_thread4;
  } else {
    goto llvm_cbe_tmp__3;
  }

llvm_cbe_tmp__3:
  if (llvm_cbe_BTN3) {
    goto llvm_cbe__2e_thread10;
  } else {
    goto llvm_cbe__2e_thread37;
  }

llvm_cbe__2e_thread37:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 true, i1* %%LED4, align  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_51_count);
  *llvm_cbe_LED4 = ((1) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 1);
  goto llvm_cbe__2e_thread10_2e_thread;

llvm_cbe__2e_thread4:
  if (llvm_cbe_BTN3) {
    goto llvm_cbe__2e_thread10_2e_thread40;
  } else {
    goto llvm_cbe_tmp__4;
  }

llvm_cbe__2e_thread10_2e_thread40:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 false, i1* %%LED4, align  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_54_count);
  *llvm_cbe_LED4 = ((0) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 0);
  goto llvm_cbe_tmp__5;

llvm_cbe__2e_thread36:
if (AESL_DEBUG_TRACE)
printf("\n  %%.28.demorgan = or i1 %%BTN2, %%BTN3, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe__2e_28_2e_demorgan_count);
  llvm_cbe__2e_28_2e_demorgan = (bool )((llvm_cbe_BTN2 | llvm_cbe_BTN3)&1);
if (AESL_DEBUG_TRACE)
printf("\n.28.demorgan = 0x%X\n", llvm_cbe__2e_28_2e_demorgan);
if (AESL_DEBUG_TRACE)
printf("\n  %%.28 = xor i1 %%.28.demorgan, true, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe__2e_28_count);
  llvm_cbe__2e_28 = (bool )((llvm_cbe__2e_28_2e_demorgan ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\n.28 = 0x%X\n", llvm_cbe__2e_28);
if (AESL_DEBUG_TRACE)
printf("\n  store i1 %%.28, i1* %%LED4, align  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_56_count);
  *llvm_cbe_LED4 = ((llvm_cbe__2e_28) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n.28 = 0x%X\n", llvm_cbe__2e_28);
  goto llvm_cbe__2e_thread13;

llvm_cbe_tmp__4:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 true, i1* %%LED4, align  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_58_count);
  *llvm_cbe_LED4 = ((1) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 1);
  if (llvm_cbe_BTN1) {
    goto llvm_cbe__2e_thread13;
  } else {
    goto llvm_cbe__2e_thread10_2e_thread;
  }

llvm_cbe__2e_thread13:
if (AESL_DEBUG_TRACE)
printf("\n  %%not.BTN234 = xor i1 %%BTN2, true, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_not_2e_BTN234_count);
  llvm_cbe_not_2e_BTN234 = (bool )((llvm_cbe_BTN2 ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\nnot.BTN234 = 0x%X\n", llvm_cbe_not_2e_BTN234);
if (AESL_DEBUG_TRACE)
printf("\n  %%. = and i1 %%not.BTN234, %%BTN3, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe__2e__count);
  llvm_cbe__2e_ = (bool )((llvm_cbe_not_2e_BTN234 & llvm_cbe_BTN3)&1);
if (AESL_DEBUG_TRACE)
printf("\n. = 0x%X\n", llvm_cbe__2e_);
if (AESL_DEBUG_TRACE)
printf("\n  store i1 %%., i1* %%LED3, align  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_60_count);
  *llvm_cbe_LED3 = ((llvm_cbe__2e_) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n. = 0x%X\n", llvm_cbe__2e_);
  goto llvm_cbe_tmp__6;

llvm_cbe__2e_thread10_2e_thread:
  goto llvm_cbe_tmp__5;

llvm_cbe__2e_thread10:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 false, i1* %%LED4, align  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_63_count);
  *llvm_cbe_LED4 = ((0) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 0);
if (AESL_DEBUG_TRACE)
printf("\n  store i1 false, i1* %%LED3, align  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_64_count);
  *llvm_cbe_LED3 = ((0) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 0);
if (AESL_DEBUG_TRACE)
printf("\n  %%BTN3.not = xor i1 %%BTN3, true, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_BTN3_2e_not_count);
  llvm_cbe_BTN3_2e_not = (bool )((llvm_cbe_BTN3 ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\nBTN3.not = 0x%X\n", llvm_cbe_BTN3_2e_not);
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge = or i1 %%BTN2, %%BTN3.not, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_brmerge_count);
  llvm_cbe_brmerge = (bool )((llvm_cbe_BTN2 | llvm_cbe_BTN3_2e_not)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge = 0x%X\n", llvm_cbe_brmerge);
  if (llvm_cbe_brmerge) {
    goto llvm_cbe__2e_thread;
  } else {
    goto llvm_cbe__2e_thread45;
  }

llvm_cbe__2e_thread45:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 true, i1* %%LED2, align  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_66_count);
  *llvm_cbe_LED2 = ((1) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 1);
  goto llvm_cbe_tmp__7;

llvm_cbe_tmp__5:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 false, i1* %%LED3, align  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_68_count);
  *llvm_cbe_LED3 = ((0) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 0);
  if (llvm_cbe_BTN1) {
    goto llvm_cbe_tmp__6;
  } else {
    goto llvm_cbe__2e_thread43;
  }

llvm_cbe__2e_thread43:
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge50.demorgan = and i1 %%BTN2, %%BTN3, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_brmerge50_2e_demorgan_count);
  llvm_cbe_brmerge50_2e_demorgan = (bool )((llvm_cbe_BTN2 & llvm_cbe_BTN3)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge50.demorgan = 0x%X\n", llvm_cbe_brmerge50_2e_demorgan);
  if (llvm_cbe_brmerge50_2e_demorgan) {
    goto llvm_cbe_tmp__8;
  } else {
    goto llvm_cbe__2e_thread;
  }

llvm_cbe_tmp__6:
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge29 = or i1 %%BTN2, %%BTN3, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_brmerge29_count);
  llvm_cbe_brmerge29 = (bool )((llvm_cbe_BTN2 | llvm_cbe_BTN3)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge29 = 0x%X\n", llvm_cbe_brmerge29);
  if (llvm_cbe_brmerge29) {
    goto llvm_cbe_tmp__9;
  } else {
    goto llvm_cbe_tmp__8;
  }

llvm_cbe__2e_thread:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 false, i1* %%LED2, align  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_72_count);
  *llvm_cbe_LED2 = ((0) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 0);
  goto llvm_cbe_tmp__10;

llvm_cbe_tmp__9:
  if (llvm_cbe_BTN1) {
    goto llvm_cbe__2e_thread19;
  } else {
    goto llvm_cbe__2e_thread20;
  }

llvm_cbe__2e_thread20:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 false, i1* %%LED2, align  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_75_count);
  *llvm_cbe_LED2 = ((0) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 0);
  goto llvm_cbe_tmp__10;

llvm_cbe__2e_thread19:
if (AESL_DEBUG_TRACE)
printf("\n  %%not.BTN233 = xor i1 %%BTN2, true, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_not_2e_BTN233_count);
  llvm_cbe_not_2e_BTN233 = (bool )((llvm_cbe_BTN2 ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\nnot.BTN233 = 0x%X\n", llvm_cbe_not_2e_BTN233);
if (AESL_DEBUG_TRACE)
printf("\n  %%.1 = and i1 %%not.BTN233, %%BTN3, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe__2e_1_count);
  llvm_cbe__2e_1 = (bool )((llvm_cbe_not_2e_BTN233 & llvm_cbe_BTN3)&1);
if (AESL_DEBUG_TRACE)
printf("\n.1 = 0x%X\n", llvm_cbe__2e_1);
if (AESL_DEBUG_TRACE)
printf("\n  store i1 %%.1, i1* %%LED2, align  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_77_count);
  *llvm_cbe_LED2 = ((llvm_cbe__2e_1) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n.1 = 0x%X\n", llvm_cbe__2e_1);
  goto llvm_cbe__2e_thread27;

llvm_cbe_tmp__8:
if (AESL_DEBUG_TRACE)
printf("\n  store i1 true, i1* %%LED2, align  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_79_count);
  *llvm_cbe_LED2 = ((1) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 1);
  if (llvm_cbe_BTN1) {
    goto llvm_cbe__2e_thread27;
  } else {
    goto llvm_cbe_tmp__10;
  }

llvm_cbe_tmp__10:
if (AESL_DEBUG_TRACE)
printf("\n  %%BTN2.not = xor i1 %%BTN2, true, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_BTN2_2e_not_count);
  llvm_cbe_BTN2_2e_not = (bool )((llvm_cbe_BTN2 ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\nBTN2.not = 0x%X\n", llvm_cbe_BTN2_2e_not);
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge30 = or i1 %%BTN2.not, %%BTN3, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_brmerge30_count);
  llvm_cbe_brmerge30 = (bool )((llvm_cbe_BTN2_2e_not | llvm_cbe_BTN3)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge30 = 0x%X\n", llvm_cbe_brmerge30);
  if (llvm_cbe_brmerge30) {
    goto llvm_cbe_tmp__7;
  } else {
    llvm_cbe_tmp__1__PHI_TEMPORARY = (bool )1;   /* for PHI node */
    goto llvm_cbe__2e_thread26;
  }

llvm_cbe__2e_thread27:
  goto llvm_cbe__2e_thread23;

llvm_cbe_tmp__7:
  if (llvm_cbe_BTN1) {
    goto llvm_cbe__2e_thread23;
  } else {
    goto llvm_cbe_tmp__11;
  }

llvm_cbe_tmp__11:
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge53.demorgan = and i1 %%BTN2, %%BTN3, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_brmerge53_2e_demorgan_count);
  llvm_cbe_brmerge53_2e_demorgan = (bool )((llvm_cbe_BTN2 & llvm_cbe_BTN3)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge53.demorgan = 0x%X\n", llvm_cbe_brmerge53_2e_demorgan);
  llvm_cbe_tmp__1__PHI_TEMPORARY = (bool )llvm_cbe_brmerge53_2e_demorgan;   /* for PHI node */
  goto llvm_cbe__2e_thread26;

llvm_cbe__2e_thread23:
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge31 = or i1 %%BTN2, %%BTN3, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_brmerge31_count);
  llvm_cbe_brmerge31 = (bool )((llvm_cbe_BTN2 | llvm_cbe_BTN3)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge31 = 0x%X\n", llvm_cbe_brmerge31);
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge31.not = xor i1 %%brmerge31, true, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_brmerge31_2e_not_count);
  llvm_cbe_brmerge31_2e_not = (bool )((llvm_cbe_brmerge31 ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge31.not = 0x%X\n", llvm_cbe_brmerge31_2e_not);
if (AESL_DEBUG_TRACE)
printf("\n  %%BTN1.not = xor i1 %%BTN1, true, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_BTN1_2e_not_count);
  llvm_cbe_BTN1_2e_not = (bool )((llvm_cbe_BTN1 ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\nBTN1.not = 0x%X\n", llvm_cbe_BTN1_2e_not);
if (AESL_DEBUG_TRACE)
printf("\n  %%brmerge32 = or i1 %%brmerge31.not, %%BTN1.not, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_brmerge32_count);
  llvm_cbe_brmerge32 = (bool )((llvm_cbe_brmerge31_2e_not | llvm_cbe_BTN1_2e_not)&1);
if (AESL_DEBUG_TRACE)
printf("\nbrmerge32 = 0x%X\n", llvm_cbe_brmerge32);
  if (llvm_cbe_brmerge32) {
    llvm_cbe_tmp__1__PHI_TEMPORARY = (bool )llvm_cbe_brmerge31_2e_not;   /* for PHI node */
    goto llvm_cbe__2e_thread26;
  } else {
    goto llvm_cbe_tmp__12;
  }

llvm_cbe_tmp__12:
if (AESL_DEBUG_TRACE)
printf("\n  %%not.BTN2 = xor i1 %%BTN2, true, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_not_2e_BTN2_count);
  llvm_cbe_not_2e_BTN2 = (bool )((llvm_cbe_BTN2 ^ 1)&1);
if (AESL_DEBUG_TRACE)
printf("\nnot.BTN2 = 0x%X\n", llvm_cbe_not_2e_BTN2);
if (AESL_DEBUG_TRACE)
printf("\n  %%.2 = and i1 %%not.BTN2, %%BTN3, !dbg !2 for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe__2e_2_count);
  llvm_cbe__2e_2 = (bool )((llvm_cbe_not_2e_BTN2 & llvm_cbe_BTN3)&1);
if (AESL_DEBUG_TRACE)
printf("\n.2 = 0x%X\n", llvm_cbe__2e_2);
  llvm_cbe_tmp__1__PHI_TEMPORARY = (bool )llvm_cbe__2e_2;   /* for PHI node */
  goto llvm_cbe__2e_thread26;

llvm_cbe__2e_thread26:
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = phi i1 [ %%.2, %%11 ], [ true, %%8 ], [ %%brmerge31.not, %%.thread23 ], [ %%brmerge53.demorgan, %%10  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_87_count);
  llvm_cbe_tmp__1 = (bool )((llvm_cbe_tmp__1__PHI_TEMPORARY)&1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__1);
printf("\n.2 = 0x%X",llvm_cbe__2e_2);
printf("\n = 0x%X",1);
printf("\nbrmerge31.not = 0x%X",llvm_cbe_brmerge31_2e_not);
printf("\nbrmerge53.demorgan = 0x%X",llvm_cbe_brmerge53_2e_demorgan);
}
if (AESL_DEBUG_TRACE)
printf("\n  store i1 %%12, i1* %%LED1, align  for 0x%I64xth hint within @Dobblesteen  --> \n", ++aesl_llvm_cbe_88_count);
  *llvm_cbe_LED1 = ((llvm_cbe_tmp__1) & 1ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__1);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @Dobblesteen}\n");
  return;
}

