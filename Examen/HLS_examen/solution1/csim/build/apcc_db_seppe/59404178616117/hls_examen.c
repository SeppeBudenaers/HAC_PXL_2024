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
void ImageTransform( char *llvm_cbe_imageRGBA,  char *llvm_cbe_output, signed int llvm_cbe_width, signed int llvm_cbe_height, signed int llvm_cbe_centerX, signed int llvm_cbe_centerY);


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

void ImageTransform( char *llvm_cbe_imageRGBA,  char *llvm_cbe_output, signed int llvm_cbe_width, signed int llvm_cbe_height, signed int llvm_cbe_centerX, signed int llvm_cbe_centerY) {
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
  unsigned int llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  unsigned int llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv53_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv53;
  unsigned int llvm_cbe_indvars_2e_iv53__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv51_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv51;
  unsigned int llvm_cbe_indvars_2e_iv51__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv49_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv49;
  unsigned int llvm_cbe_indvars_2e_iv49__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv47_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv47;
  unsigned int llvm_cbe_indvars_2e_iv47__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  static  unsigned long long aesl_llvm_cbe_smax55_count = 0;
  unsigned int llvm_cbe_smax55;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  unsigned int llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_umax56_count = 0;
  unsigned int llvm_cbe_umax56;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  unsigned int llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  unsigned int llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  double llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_pow25_count = 0;
  double llvm_cbe_pow25;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv34_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv34;
  unsigned int llvm_cbe_indvars_2e_iv34__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv32_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv32;
  unsigned int llvm_cbe_indvars_2e_iv32__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv30_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv30;
  unsigned int llvm_cbe_indvars_2e_iv30__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv;
  unsigned int llvm_cbe_indvars_2e_iv__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_smax_count = 0;
  unsigned int llvm_cbe_smax;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  unsigned int llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_umax_count = 0;
  unsigned int llvm_cbe_umax;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  unsigned int llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  unsigned int llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  double llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_pow2_count = 0;
  double llvm_cbe_pow2;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  double llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  double llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  unsigned int llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  unsigned int llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond46_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge311_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge311_2e_us;
  unsigned int llvm_cbe_storemerge311_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  unsigned int llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge217_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge217_2e_us;
  unsigned int llvm_cbe_storemerge217_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next31_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next31;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next33_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next33;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next35_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next35;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next48_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next48;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next50_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next50;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next52_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next52;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next54_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next54;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @ImageTransform\n");
  if ((((signed int )llvm_cbe_height) > ((signed int )0u))) {
    goto llvm_cbe__2e_preheader18_2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge26;
  }

llvm_cbe__2e_preheader18_2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = sub i32 0, %%width, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_34_count);
  llvm_cbe_tmp__1 = (unsigned int )-(llvm_cbe_width);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__1&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = sub i32 0, %%height, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_35_count);
  llvm_cbe_tmp__2 = (unsigned int )-(llvm_cbe_height);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__2&4294967295ull)));
  llvm_cbe_indvars_2e_iv53__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv51__PHI_TEMPORARY = (unsigned int )15u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv49__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__2;   /* for PHI node */
  llvm_cbe_indvars_2e_iv47__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader18;

  do {     /* Syntactic loop '.preheader18' to make GCC happy */
llvm_cbe__2e_preheader18:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv53 = phi i32 [ 1, %%.preheader18.lr.ph ], [ %%indvars.iv.next54, %%._crit_edge ], !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv53_count);
  llvm_cbe_indvars_2e_iv53 = (unsigned int )llvm_cbe_indvars_2e_iv53__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv53 = 0x%X",llvm_cbe_indvars_2e_iv53);
printf("\n = 0x%X",1u);
printf("\nindvars.iv.next54 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next54);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv51 = phi i32 [ 15, %%.preheader18.lr.ph ], [ %%indvars.iv.next52, %%._crit_edge ], !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv51_count);
  llvm_cbe_indvars_2e_iv51 = (unsigned int )llvm_cbe_indvars_2e_iv51__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv51 = 0x%X",llvm_cbe_indvars_2e_iv51);
printf("\n = 0x%X",15u);
printf("\nindvars.iv.next52 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next52);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv49 = phi i32 [ %%4, %%.preheader18.lr.ph ], [ %%indvars.iv.next50, %%._crit_edge ], !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv49_count);
  llvm_cbe_indvars_2e_iv49 = (unsigned int )llvm_cbe_indvars_2e_iv49__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv49 = 0x%X",llvm_cbe_indvars_2e_iv49);
printf("\n = 0x%X",llvm_cbe_tmp__2);
printf("\nindvars.iv.next50 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next50);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv47 = phi i32 [ 0, %%.preheader18.lr.ph ], [ %%indvars.iv.next48, %%._crit_edge  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv47_count);
  llvm_cbe_indvars_2e_iv47 = (unsigned int )llvm_cbe_indvars_2e_iv47__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv47 = 0x%X",llvm_cbe_indvars_2e_iv47);
printf("\n = 0x%X",0u);
printf("\nindvars.iv.next48 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next48);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%smax55 = select i1 %%5, i32 %%indvars.iv51, i32 %%indvars.iv53, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_smax55_count);
  llvm_cbe_smax55 = (unsigned int )(((((signed int )llvm_cbe_indvars_2e_iv51) > ((signed int )llvm_cbe_indvars_2e_iv53))) ? ((unsigned int )llvm_cbe_indvars_2e_iv51) : ((unsigned int )llvm_cbe_indvars_2e_iv53));
if (AESL_DEBUG_TRACE)
printf("\nsmax55 = 0x%X\n", llvm_cbe_smax55);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = sub i32 %%indvars.iv47, %%smax55, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_44_count);
  llvm_cbe_tmp__3 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv47&4294967295ull)) - ((unsigned int )(llvm_cbe_smax55&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__3&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%umax56 = select i1 %%7, i32 %%indvars.iv49, i32 %%6, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_umax56_count);
  llvm_cbe_umax56 = (unsigned int )(((((unsigned int )llvm_cbe_indvars_2e_iv49&4294967295U) > ((unsigned int )llvm_cbe_tmp__3&4294967295U))) ? ((unsigned int )llvm_cbe_indvars_2e_iv49) : ((unsigned int )llvm_cbe_tmp__3));
if (AESL_DEBUG_TRACE)
printf("\numax56 = 0x%X\n", llvm_cbe_umax56);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = sub i32 %%indvars.iv47, %%umax56, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_46_count);
  llvm_cbe_tmp__4 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv47&4294967295ull)) - ((unsigned int )(llvm_cbe_umax56&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__4&4294967295ull)));
  if ((((signed int )llvm_cbe_width) > ((signed int )0u))) {
    goto llvm_cbe__2e_lr_2e_ph23;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

llvm_cbe__2e__crit_edge:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next48 = add i32 %%indvars.iv47, 15, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next48_count);
  llvm_cbe_indvars_2e_iv_2e_next48 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv47&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next48 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next48&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next50 = add i32 %%indvars.iv49, 15, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next50_count);
  llvm_cbe_indvars_2e_iv_2e_next50 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv49&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next50 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next50&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next52 = add i32 %%indvars.iv51, 15, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next52_count);
  llvm_cbe_indvars_2e_iv_2e_next52 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv51&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next52 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next52&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next54 = add i32 %%indvars.iv53, 15, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next54_count);
  llvm_cbe_indvars_2e_iv_2e_next54 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv53&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next54 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next54&4294967295ull)));
  if ((((signed int )llvm_cbe_indvars_2e_iv_2e_next48) < ((signed int )llvm_cbe_height))) {
    llvm_cbe_indvars_2e_iv53__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next54;   /* for PHI node */
    llvm_cbe_indvars_2e_iv51__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next52;   /* for PHI node */
    llvm_cbe_indvars_2e_iv49__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next50;   /* for PHI node */
    llvm_cbe_indvars_2e_iv47__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next48;   /* for PHI node */
    goto llvm_cbe__2e_preheader18;
  } else {
    goto llvm_cbe__2e__crit_edge26;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__16:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv34 = phi i32 [ 1, %%.lr.ph23 ], [ %%indvars.iv.next35, %%.critedge ], !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv34_count);
  llvm_cbe_indvars_2e_iv34 = (unsigned int )llvm_cbe_indvars_2e_iv34__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv34 = 0x%X",llvm_cbe_indvars_2e_iv34);
printf("\n = 0x%X",1u);
printf("\nindvars.iv.next35 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next35);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv32 = phi i32 [ 15, %%.lr.ph23 ], [ %%indvars.iv.next33, %%.critedge ], !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv32_count);
  llvm_cbe_indvars_2e_iv32 = (unsigned int )llvm_cbe_indvars_2e_iv32__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv32 = 0x%X",llvm_cbe_indvars_2e_iv32);
printf("\n = 0x%X",15u);
printf("\nindvars.iv.next33 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next33);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv30 = phi i32 [ 0, %%.lr.ph23 ], [ %%indvars.iv.next31, %%.critedge ], !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv30_count);
  llvm_cbe_indvars_2e_iv30 = (unsigned int )llvm_cbe_indvars_2e_iv30__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv30 = 0x%X",llvm_cbe_indvars_2e_iv30);
printf("\n = 0x%X",0u);
printf("\nindvars.iv.next31 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next31);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv = phi i32 [ %%3, %%.lr.ph23 ], [ %%indvars.iv.next, %%.critedge  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_count);
  llvm_cbe_indvars_2e_iv = (unsigned int )llvm_cbe_indvars_2e_iv__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv = 0x%X",llvm_cbe_indvars_2e_iv);
printf("\n = 0x%X",llvm_cbe_tmp__1);
printf("\nindvars.iv.next = 0x%X",llvm_cbe_indvars_2e_iv_2e_next);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%smax = select i1 %%13, i32 %%indvars.iv32, i32 %%indvars.iv34, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_smax_count);
  llvm_cbe_smax = (unsigned int )(((((signed int )llvm_cbe_indvars_2e_iv32) > ((signed int )llvm_cbe_indvars_2e_iv34))) ? ((unsigned int )llvm_cbe_indvars_2e_iv32) : ((unsigned int )llvm_cbe_indvars_2e_iv34));
if (AESL_DEBUG_TRACE)
printf("\nsmax = 0x%X\n", llvm_cbe_smax);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = sub i32 %%indvars.iv30, %%smax, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_53_count);
  llvm_cbe_tmp__7 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv30&4294967295ull)) - ((unsigned int )(llvm_cbe_smax&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__7&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%umax = select i1 %%15, i32 %%indvars.iv, i32 %%14, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_umax_count);
  llvm_cbe_umax = (unsigned int )(((((unsigned int )llvm_cbe_indvars_2e_iv&4294967295U) > ((unsigned int )llvm_cbe_tmp__7&4294967295U))) ? ((unsigned int )llvm_cbe_indvars_2e_iv) : ((unsigned int )llvm_cbe_tmp__7));
if (AESL_DEBUG_TRACE)
printf("\numax = 0x%X\n", llvm_cbe_umax);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = sub i32 %%indvars.iv30, %%umax, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_55_count);
  llvm_cbe_tmp__8 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv30&4294967295ull)) - ((unsigned int )(llvm_cbe_umax&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__8&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = sub nsw i32 %%indvars.iv30, %%centerX, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_56_count);
  llvm_cbe_tmp__9 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv30&4294967295ull)) - ((unsigned int )(llvm_cbe_centerX&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__9&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = sitofp i32 %%17 to double, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_57_count);
  llvm_cbe_tmp__10 = (double )((double )(signed int )llvm_cbe_tmp__9);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__10, *(long long*)(&llvm_cbe_tmp__10));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow2 = fmul double %%18, %%18, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_pow2_count);
  llvm_cbe_pow2 = (double )llvm_cbe_tmp__10 * llvm_cbe_tmp__10;
if (AESL_DEBUG_TRACE)
printf("\npow2 = %lf,  0x%llx\n", llvm_cbe_pow2, *(long long*)(&llvm_cbe_pow2));
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = fadd double %%pow2, %%pow25, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_58_count);
  llvm_cbe_tmp__11 = (double )llvm_cbe_pow2 + llvm_cbe_pow25;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__11, *(long long*)(&llvm_cbe_tmp__11));
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = tail call double @sqrt(double %%19) nounwind readnone, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_59_count);
  llvm_cbe_tmp__12 = (double ) /*tail*/ sqrt(llvm_cbe_tmp__11);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__11, *(long long*)(&llvm_cbe_tmp__11));
printf("\nReturn  = %lf",llvm_cbe_tmp__12);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = fptosi double %%20 to i32, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_60_count);
  llvm_cbe_tmp__13 = (unsigned int )((signed int )llvm_cbe_tmp__12&4294967295U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__13);
  if ((((signed int )llvm_cbe_tmp__13) < ((signed int )120u))) {
    goto llvm_cbe__2e_preheader15;
  } else {
    goto llvm_cbe__2e_critedge;
  }

llvm_cbe__2e_critedge:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next31 = add i32 %%indvars.iv30, 15, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next31_count);
  llvm_cbe_indvars_2e_iv_2e_next31 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv30&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next31 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next31&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next = add i32 %%indvars.iv, 15, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next_count);
  llvm_cbe_indvars_2e_iv_2e_next = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next33 = add i32 %%indvars.iv32, 15, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next33_count);
  llvm_cbe_indvars_2e_iv_2e_next33 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv32&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next33 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next33&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next35 = add i32 %%indvars.iv34, 15, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next35_count);
  llvm_cbe_indvars_2e_iv_2e_next35 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv34&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next35 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next35&4294967295ull)));
  if ((((signed int )llvm_cbe_indvars_2e_iv_2e_next31) < ((signed int )llvm_cbe_width))) {
    llvm_cbe_indvars_2e_iv34__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next35;   /* for PHI node */
    llvm_cbe_indvars_2e_iv32__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next33;   /* for PHI node */
    llvm_cbe_indvars_2e_iv30__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next31;   /* for PHI node */
    llvm_cbe_indvars_2e_iv__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next;   /* for PHI node */
    goto llvm_cbe_tmp__16;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

llvm_cbe__2e_critedge_2e_loopexit:
  goto llvm_cbe__2e_critedge;

llvm_cbe__2e_preheader15:
  if ((((signed int )llvm_cbe_indvars_2e_iv47) < ((signed int )llvm_cbe_height))) {
    goto llvm_cbe__2e_preheader_2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e_critedge_2e_loopexit;
  }

llvm_cbe__2e__2e_critedge_2e_loopexit_crit_edge:
  goto llvm_cbe__2e_critedge_2e_loopexit;

llvm_cbe__2e_preheader_2e_lr_2e_ph:
  if ((((signed int )llvm_cbe_indvars_2e_iv30) < ((signed int )llvm_cbe_width))) {
    llvm_cbe_storemerge217_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv47;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  } else {
    goto llvm_cbe__2e__2e_critedge_2e_loopexit_crit_edge;
  }

  do {     /* Syntactic loop '.lr.ph.us' to make GCC happy */
llvm_cbe__2e_lr_2e_ph_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge217.us = phi i32 [ %%24, %%.critedge4.us ], [ %%indvars.iv47, %%.preheader.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge217_2e_us_count);
  llvm_cbe_storemerge217_2e_us = (unsigned int )llvm_cbe_storemerge217_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge217.us = 0x%X",llvm_cbe_storemerge217_2e_us);
printf("\n = 0x%X",llvm_cbe_tmp__14);
printf("\nindvars.iv47 = 0x%X",llvm_cbe_indvars_2e_iv47);
}
  llvm_cbe_storemerge311_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv30;   /* for PHI node */
  goto llvm_cbe_tmp__17;

llvm_cbe__2e_critedge4_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = add nsw i32 %%storemerge217.us, 1, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_68_count);
  llvm_cbe_tmp__14 = (unsigned int )((unsigned int )(llvm_cbe_storemerge217_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__14&4294967295ull)));
  if (((llvm_cbe_tmp__14&4294967295U) == (llvm_cbe_tmp__4&4294967295U))) {
    goto llvm_cbe__2e__2e_critedge_2e_loopexit_crit_edge;
  } else {
    llvm_cbe_storemerge217_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__14;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__17:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge311.us = phi i32 [ %%indvars.iv30, %%.lr.ph.us ], [ %%26, %%25  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge311_2e_us_count);
  llvm_cbe_storemerge311_2e_us = (unsigned int )llvm_cbe_storemerge311_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge311.us = 0x%X",llvm_cbe_storemerge311_2e_us);
printf("\nindvars.iv30 = 0x%X",llvm_cbe_indvars_2e_iv30);
printf("\n = 0x%X",llvm_cbe_tmp__15);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = add nsw i32 %%storemerge311.us, 1, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_75_count);
  llvm_cbe_tmp__15 = (unsigned int )((unsigned int )(llvm_cbe_storemerge311_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__15&4294967295ull)));
  if (((llvm_cbe_tmp__15&4294967295U) == (llvm_cbe_tmp__8&4294967295U))) {
    goto llvm_cbe__2e_critedge4_2e_us;
  } else {
    llvm_cbe_storemerge311_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__15;   /* for PHI node */
    goto llvm_cbe_tmp__17;
  }

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.lr.ph.us' */
  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e_lr_2e_ph23:
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = sub nsw i32 %%indvars.iv47, %%centerY, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_48_count);
  llvm_cbe_tmp__5 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv47&4294967295ull)) - ((unsigned int )(llvm_cbe_centerY&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__5&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = sitofp i32 %%9 to double, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_49_count);
  llvm_cbe_tmp__6 = (double )((double )(signed int )llvm_cbe_tmp__5);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__6, *(long long*)(&llvm_cbe_tmp__6));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow25 = fmul double %%10, %%10, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_pow25_count);
  llvm_cbe_pow25 = (double )llvm_cbe_tmp__6 * llvm_cbe_tmp__6;
if (AESL_DEBUG_TRACE)
printf("\npow25 = %lf,  0x%llx\n", llvm_cbe_pow25, *(long long*)(&llvm_cbe_pow25));
  llvm_cbe_indvars_2e_iv34__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv32__PHI_TEMPORARY = (unsigned int )15u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv30__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__1;   /* for PHI node */
  goto llvm_cbe_tmp__16;

  } while (1); /* end of syntactic loop '.preheader18' */
llvm_cbe__2e__crit_edge26:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @ImageTransform}\n");
  return;
}

