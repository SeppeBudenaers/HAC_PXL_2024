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
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  unsigned int llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  unsigned int llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv117_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv117;
  unsigned int llvm_cbe_indvars_2e_iv117__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv115_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv115;
  unsigned int llvm_cbe_indvars_2e_iv115__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv113_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv113;
  unsigned int llvm_cbe_indvars_2e_iv113__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv111_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv111;
  unsigned int llvm_cbe_indvars_2e_iv111__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_smax119_count = 0;
  unsigned int llvm_cbe_smax119;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  unsigned int llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_umax120_count = 0;
  unsigned int llvm_cbe_umax120;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  unsigned int llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv84_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv84;
  unsigned int llvm_cbe_indvars_2e_iv84__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv82_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv82;
  unsigned int llvm_cbe_indvars_2e_iv82__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv80_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv80;
  unsigned int llvm_cbe_indvars_2e_iv80__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv78_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv78;
  unsigned int llvm_cbe_indvars_2e_iv78__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_smax86_count = 0;
  unsigned int llvm_cbe_smax86;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  unsigned int llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_umax87_count = 0;
  unsigned int llvm_cbe_umax87;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  unsigned int llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  unsigned int llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond77_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge726_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge726_2e_us;
  unsigned int llvm_cbe_storemerge726_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  unsigned int llvm_cbe_tmp__8;
  unsigned int llvm_cbe_tmp__8__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  unsigned int llvm_cbe_tmp__9;
  unsigned int llvm_cbe_tmp__9__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  unsigned int llvm_cbe_tmp__10;
  unsigned int llvm_cbe_tmp__10__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  unsigned int llvm_cbe_tmp__11;
  unsigned int llvm_cbe_tmp__11__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  unsigned int llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  unsigned int llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  unsigned long long llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
   char *llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  unsigned char llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  unsigned int llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  unsigned int llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  unsigned int llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  unsigned long long llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
   char *llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  unsigned char llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  unsigned int llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  unsigned int llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  unsigned int llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  unsigned long long llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
   char *llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  unsigned char llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  unsigned int llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  unsigned int llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  unsigned int llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  unsigned long long llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
   char *llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  unsigned char llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  unsigned int llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  unsigned int llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  unsigned int llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge440_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge440_2e_us;
  unsigned int llvm_cbe_storemerge440_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  unsigned int llvm_cbe_tmp__38;
  unsigned int llvm_cbe_tmp__38__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  unsigned int llvm_cbe_tmp__39;
  unsigned int llvm_cbe_tmp__39__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  unsigned int llvm_cbe_tmp__40;
  unsigned int llvm_cbe_tmp__40__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  unsigned int llvm_cbe_tmp__41;
  unsigned int llvm_cbe_tmp__41__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  unsigned int llvm_cbe_tmp__42;
  unsigned int llvm_cbe_tmp__42__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  unsigned int llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  unsigned int llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge440_count = 0;
  unsigned int llvm_cbe_storemerge440;
  unsigned int llvm_cbe_storemerge440__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  unsigned int llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond121_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa37_count = 0;
  unsigned int llvm_cbe__2e_lcssa37;
  unsigned int llvm_cbe__2e_lcssa37__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa36_count = 0;
  unsigned int llvm_cbe__2e_lcssa36;
  unsigned int llvm_cbe__2e_lcssa36__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa35_count = 0;
  unsigned int llvm_cbe__2e_lcssa35;
  unsigned int llvm_cbe__2e_lcssa35__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa34_count = 0;
  unsigned int llvm_cbe__2e_lcssa34;
  unsigned int llvm_cbe__2e_lcssa34__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa33_count = 0;
  unsigned int llvm_cbe__2e_lcssa33;
  unsigned int llvm_cbe__2e_lcssa33__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  unsigned int llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  unsigned char llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  unsigned int llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  unsigned char llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  unsigned int llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  unsigned char llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  unsigned int llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  unsigned char llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  unsigned int llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond99_count = 0;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge617_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge617_2e_us;
  unsigned int llvm_cbe_storemerge617_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  unsigned int llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  unsigned int llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  unsigned long long llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
   char *llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  unsigned int llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  unsigned long long llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
   char *llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  unsigned int llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  unsigned long long llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
   char *llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  unsigned int llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  unsigned long long llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
   char *llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
  unsigned int llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond88_count = 0;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge519_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge519_2e_us;
  unsigned int llvm_cbe_storemerge519_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  unsigned int llvm_cbe_tmp__69;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next79_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next79;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next81_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next81;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next83_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next83;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next85_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next85;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next112_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next112;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next114_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next114;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next116_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next116;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next118_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next118;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @ImageTransform\n");
  if ((((signed int )llvm_cbe_height) > ((signed int )0u))) {
    goto llvm_cbe__2e_preheader47_2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge55;
  }

llvm_cbe__2e_preheader47_2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = sub i32 0, %%width, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_58_count);
  llvm_cbe_tmp__1 = (unsigned int )-(llvm_cbe_width);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__1&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = sub i32 0, %%height, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_59_count);
  llvm_cbe_tmp__2 = (unsigned int )-(llvm_cbe_height);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__2&4294967295ull)));
  llvm_cbe_indvars_2e_iv117__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv115__PHI_TEMPORARY = (unsigned int )15u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv113__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__2;   /* for PHI node */
  llvm_cbe_indvars_2e_iv111__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader47;

  do {     /* Syntactic loop '.preheader47' to make GCC happy */
llvm_cbe__2e_preheader47:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv117 = phi i32 [ 1, %%.preheader47.lr.ph ], [ %%indvars.iv.next118, %%._crit_edge ], !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv117_count);
  llvm_cbe_indvars_2e_iv117 = (unsigned int )llvm_cbe_indvars_2e_iv117__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv117 = 0x%X",llvm_cbe_indvars_2e_iv117);
printf("\n = 0x%X",1u);
printf("\nindvars.iv.next118 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next118);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv115 = phi i32 [ 15, %%.preheader47.lr.ph ], [ %%indvars.iv.next116, %%._crit_edge ], !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv115_count);
  llvm_cbe_indvars_2e_iv115 = (unsigned int )llvm_cbe_indvars_2e_iv115__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv115 = 0x%X",llvm_cbe_indvars_2e_iv115);
printf("\n = 0x%X",15u);
printf("\nindvars.iv.next116 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next116);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv113 = phi i32 [ %%4, %%.preheader47.lr.ph ], [ %%indvars.iv.next114, %%._crit_edge ], !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv113_count);
  llvm_cbe_indvars_2e_iv113 = (unsigned int )llvm_cbe_indvars_2e_iv113__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv113 = 0x%X",llvm_cbe_indvars_2e_iv113);
printf("\n = 0x%X",llvm_cbe_tmp__2);
printf("\nindvars.iv.next114 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next114);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv111 = phi i32 [ 0, %%.preheader47.lr.ph ], [ %%indvars.iv.next112, %%._crit_edge  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv111_count);
  llvm_cbe_indvars_2e_iv111 = (unsigned int )llvm_cbe_indvars_2e_iv111__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv111 = 0x%X",llvm_cbe_indvars_2e_iv111);
printf("\n = 0x%X",0u);
printf("\nindvars.iv.next112 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next112);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%smax119 = select i1 %%5, i32 %%indvars.iv115, i32 %%indvars.iv117, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_smax119_count);
  llvm_cbe_smax119 = (unsigned int )(((((signed int )llvm_cbe_indvars_2e_iv115) > ((signed int )llvm_cbe_indvars_2e_iv117))) ? ((unsigned int )llvm_cbe_indvars_2e_iv115) : ((unsigned int )llvm_cbe_indvars_2e_iv117));
if (AESL_DEBUG_TRACE)
printf("\nsmax119 = 0x%X\n", llvm_cbe_smax119);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = sub i32 %%indvars.iv111, %%smax119, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_73_count);
  llvm_cbe_tmp__3 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv111&4294967295ull)) - ((unsigned int )(llvm_cbe_smax119&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__3&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%umax120 = select i1 %%7, i32 %%indvars.iv113, i32 %%6, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_umax120_count);
  llvm_cbe_umax120 = (unsigned int )(((((unsigned int )llvm_cbe_indvars_2e_iv113&4294967295U) > ((unsigned int )llvm_cbe_tmp__3&4294967295U))) ? ((unsigned int )llvm_cbe_indvars_2e_iv113) : ((unsigned int )llvm_cbe_tmp__3));
if (AESL_DEBUG_TRACE)
printf("\numax120 = 0x%X\n", llvm_cbe_umax120);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = sub i32 %%indvars.iv111, %%umax120, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_75_count);
  llvm_cbe_tmp__4 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv111&4294967295ull)) - ((unsigned int )(llvm_cbe_umax120&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__4&4294967295ull)));
  if ((((signed int )llvm_cbe_width) > ((signed int )0u))) {
    goto llvm_cbe__2e_preheader32_2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

llvm_cbe__2e__crit_edge:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next112 = add i32 %%indvars.iv111, 15, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next112_count);
  llvm_cbe_indvars_2e_iv_2e_next112 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv111&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next112 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next112&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next114 = add i32 %%indvars.iv113, 15, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next114_count);
  llvm_cbe_indvars_2e_iv_2e_next114 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv113&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next114 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next114&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next116 = add i32 %%indvars.iv115, 15, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next116_count);
  llvm_cbe_indvars_2e_iv_2e_next116 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv115&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next116 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next116&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next118 = add i32 %%indvars.iv117, 15, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next118_count);
  llvm_cbe_indvars_2e_iv_2e_next118 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv117&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next118 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next118&4294967295ull)));
  if ((((signed int )llvm_cbe_indvars_2e_iv_2e_next112) < ((signed int )llvm_cbe_height))) {
    llvm_cbe_indvars_2e_iv117__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next118;   /* for PHI node */
    llvm_cbe_indvars_2e_iv115__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next116;   /* for PHI node */
    llvm_cbe_indvars_2e_iv113__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next114;   /* for PHI node */
    llvm_cbe_indvars_2e_iv111__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next112;   /* for PHI node */
    goto llvm_cbe__2e_preheader47;
  } else {
    goto llvm_cbe__2e__crit_edge55;
  }

  do {     /* Syntactic loop '.preheader32' to make GCC happy */
llvm_cbe__2e_preheader32:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv84 = phi i32 [ 1, %%.preheader32.lr.ph ], [ %%indvars.iv.next85, %%.critedge9 ], !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv84_count);
  llvm_cbe_indvars_2e_iv84 = (unsigned int )llvm_cbe_indvars_2e_iv84__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv84 = 0x%X",llvm_cbe_indvars_2e_iv84);
printf("\n = 0x%X",1u);
printf("\nindvars.iv.next85 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next85);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv82 = phi i32 [ 15, %%.preheader32.lr.ph ], [ %%indvars.iv.next83, %%.critedge9 ], !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv82_count);
  llvm_cbe_indvars_2e_iv82 = (unsigned int )llvm_cbe_indvars_2e_iv82__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv82 = 0x%X",llvm_cbe_indvars_2e_iv82);
printf("\n = 0x%X",15u);
printf("\nindvars.iv.next83 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next83);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv80 = phi i32 [ %%3, %%.preheader32.lr.ph ], [ %%indvars.iv.next81, %%.critedge9 ], !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv80_count);
  llvm_cbe_indvars_2e_iv80 = (unsigned int )llvm_cbe_indvars_2e_iv80__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv80 = 0x%X",llvm_cbe_indvars_2e_iv80);
printf("\n = 0x%X",llvm_cbe_tmp__1);
printf("\nindvars.iv.next81 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next81);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv78 = phi i32 [ 0, %%.preheader32.lr.ph ], [ %%indvars.iv.next79, %%.critedge9  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv78_count);
  llvm_cbe_indvars_2e_iv78 = (unsigned int )llvm_cbe_indvars_2e_iv78__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv78 = 0x%X",llvm_cbe_indvars_2e_iv78);
printf("\n = 0x%X",0u);
printf("\nindvars.iv.next79 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next79);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%smax86 = select i1 %%10, i32 %%indvars.iv82, i32 %%indvars.iv84, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_smax86_count);
  llvm_cbe_smax86 = (unsigned int )(((((signed int )llvm_cbe_indvars_2e_iv82) > ((signed int )llvm_cbe_indvars_2e_iv84))) ? ((unsigned int )llvm_cbe_indvars_2e_iv82) : ((unsigned int )llvm_cbe_indvars_2e_iv84));
if (AESL_DEBUG_TRACE)
printf("\nsmax86 = 0x%X\n", llvm_cbe_smax86);
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = sub i32 %%indvars.iv78, %%smax86, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_80_count);
  llvm_cbe_tmp__5 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv78&4294967295ull)) - ((unsigned int )(llvm_cbe_smax86&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__5&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%umax87 = select i1 %%12, i32 %%indvars.iv80, i32 %%11, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_umax87_count);
  llvm_cbe_umax87 = (unsigned int )(((((unsigned int )llvm_cbe_indvars_2e_iv80&4294967295U) > ((unsigned int )llvm_cbe_tmp__5&4294967295U))) ? ((unsigned int )llvm_cbe_indvars_2e_iv80) : ((unsigned int )llvm_cbe_tmp__5));
if (AESL_DEBUG_TRACE)
printf("\numax87 = 0x%X\n", llvm_cbe_umax87);
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = sub i32 %%indvars.iv78, %%umax87, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_82_count);
  llvm_cbe_tmp__6 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv78&4294967295ull)) - ((unsigned int )(llvm_cbe_umax87&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__6&4294967295ull)));
  if ((((signed int )llvm_cbe_indvars_2e_iv111) < ((signed int )llvm_cbe_height))) {
    goto llvm_cbe__2e_preheader20_2e_lr_2e_ph;
  } else {
    llvm_cbe__2e_lcssa37__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa36__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa35__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa34__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa33__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_critedge;
  }

llvm_cbe__2e_critedge9:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next79 = add i32 %%indvars.iv78, 15, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next79_count);
  llvm_cbe_indvars_2e_iv_2e_next79 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv78&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next79 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next79&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next81 = add i32 %%indvars.iv80, 15, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next81_count);
  llvm_cbe_indvars_2e_iv_2e_next81 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv80&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next81 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next81&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next83 = add i32 %%indvars.iv82, 15, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next83_count);
  llvm_cbe_indvars_2e_iv_2e_next83 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv82&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next83 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next83&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next85 = add i32 %%indvars.iv84, 15, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next85_count);
  llvm_cbe_indvars_2e_iv_2e_next85 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv84&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next85 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next85&4294967295ull)));
  if ((((signed int )llvm_cbe_indvars_2e_iv_2e_next79) < ((signed int )llvm_cbe_width))) {
    llvm_cbe_indvars_2e_iv84__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next85;   /* for PHI node */
    llvm_cbe_indvars_2e_iv82__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next83;   /* for PHI node */
    llvm_cbe_indvars_2e_iv80__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next81;   /* for PHI node */
    llvm_cbe_indvars_2e_iv78__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next79;   /* for PHI node */
    goto llvm_cbe__2e_preheader32;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

llvm_cbe__2e_critedge:
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa37 = phi i32 [ 0, %%.preheader32 ], [ %%27, %%.critedge8.us ], [ 0, %%.critedge8  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe__2e_lcssa37_count);
  llvm_cbe__2e_lcssa37 = (unsigned int )llvm_cbe__2e_lcssa37__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa37 = 0x%X",llvm_cbe__2e_lcssa37);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__18);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa36 = phi i32 [ 0, %%.preheader32 ], [ %%33, %%.critedge8.us ], [ 0, %%.critedge8  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe__2e_lcssa36_count);
  llvm_cbe__2e_lcssa36 = (unsigned int )llvm_cbe__2e_lcssa36__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa36 = 0x%X",llvm_cbe__2e_lcssa36);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__24);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa35 = phi i32 [ 0, %%.preheader32 ], [ %%39, %%.critedge8.us ], [ 0, %%.critedge8  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe__2e_lcssa35_count);
  llvm_cbe__2e_lcssa35 = (unsigned int )llvm_cbe__2e_lcssa35__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa35 = 0x%X",llvm_cbe__2e_lcssa35);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__30);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa34 = phi i32 [ 0, %%.preheader32 ], [ %%45, %%.critedge8.us ], [ 0, %%.critedge8  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe__2e_lcssa34_count);
  llvm_cbe__2e_lcssa34 = (unsigned int )llvm_cbe__2e_lcssa34__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa34 = 0x%X",llvm_cbe__2e_lcssa34);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__36);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa33 = phi i32 [ 0, %%.preheader32 ], [ %%53, %%.critedge8.us ], [ 0, %%.critedge8  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe__2e_lcssa33_count);
  llvm_cbe__2e_lcssa33 = (unsigned int )llvm_cbe__2e_lcssa33__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa33 = 0x%X",llvm_cbe__2e_lcssa33);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__44);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = sdiv i32 %%.lcssa37, %%.lcssa33, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_162_count);
  llvm_cbe_tmp__46 = (unsigned int )((signed int )(((signed int )llvm_cbe__2e_lcssa37) / ((signed int )llvm_cbe__2e_lcssa33)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__46));
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = trunc i32 %%55 to i8, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_163_count);
  llvm_cbe_tmp__47 = (unsigned char )((unsigned char )llvm_cbe_tmp__46&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n  %%57 = sdiv i32 %%.lcssa36, %%.lcssa33, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_166_count);
  llvm_cbe_tmp__48 = (unsigned int )((signed int )(((signed int )llvm_cbe__2e_lcssa36) / ((signed int )llvm_cbe__2e_lcssa33)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__48));
if (AESL_DEBUG_TRACE)
printf("\n  %%58 = trunc i32 %%57 to i8, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_167_count);
  llvm_cbe_tmp__49 = (unsigned char )((unsigned char )llvm_cbe_tmp__48&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__49);
if (AESL_DEBUG_TRACE)
printf("\n  %%59 = sdiv i32 %%.lcssa35, %%.lcssa33, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_170_count);
  llvm_cbe_tmp__50 = (unsigned int )((signed int )(((signed int )llvm_cbe__2e_lcssa35) / ((signed int )llvm_cbe__2e_lcssa33)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__50));
if (AESL_DEBUG_TRACE)
printf("\n  %%60 = trunc i32 %%59 to i8, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_171_count);
  llvm_cbe_tmp__51 = (unsigned char )((unsigned char )llvm_cbe_tmp__50&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__51);
if (AESL_DEBUG_TRACE)
printf("\n  %%61 = sdiv i32 %%.lcssa34, %%.lcssa33, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_174_count);
  llvm_cbe_tmp__52 = (unsigned int )((signed int )(((signed int )llvm_cbe__2e_lcssa34) / ((signed int )llvm_cbe__2e_lcssa33)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__52));
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = trunc i32 %%61 to i8, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_175_count);
  llvm_cbe_tmp__53 = (unsigned char )((unsigned char )llvm_cbe_tmp__52&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__53);
  if ((((signed int )llvm_cbe_indvars_2e_iv111) < ((signed int )llvm_cbe_height))) {
    goto llvm_cbe__2e_preheader_2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e_critedge9;
  }

  do {     /* Syntactic loop '.lr.ph27.us' to make GCC happy */
llvm_cbe__2e_lr_2e_ph27_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge440.us = phi i32 [ %%15, %%.critedge8.us ], [ %%indvars.iv111, %%.preheader20.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge440_2e_us_count);
  llvm_cbe_storemerge440_2e_us = (unsigned int )llvm_cbe_storemerge440_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge440.us = 0x%X",llvm_cbe_storemerge440_2e_us);
printf("\n = 0x%X",llvm_cbe_tmp__7);
printf("\nindvars.iv111 = 0x%X",llvm_cbe_indvars_2e_iv111);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = phi i32 [ %%27, %%.critedge8.us ], [ 0, %%.preheader20.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_146_count);
  llvm_cbe_tmp__38 = (unsigned int )llvm_cbe_tmp__38__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__38);
printf("\n = 0x%X",llvm_cbe_tmp__18);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%48 = phi i32 [ %%33, %%.critedge8.us ], [ 0, %%.preheader20.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_147_count);
  llvm_cbe_tmp__39 = (unsigned int )llvm_cbe_tmp__39__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__39);
printf("\n = 0x%X",llvm_cbe_tmp__24);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%49 = phi i32 [ %%39, %%.critedge8.us ], [ 0, %%.preheader20.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_148_count);
  llvm_cbe_tmp__40 = (unsigned int )llvm_cbe_tmp__40__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__40);
printf("\n = 0x%X",llvm_cbe_tmp__30);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%50 = phi i32 [ %%45, %%.critedge8.us ], [ 0, %%.preheader20.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_149_count);
  llvm_cbe_tmp__41 = (unsigned int )llvm_cbe_tmp__41__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__41);
printf("\n = 0x%X",llvm_cbe_tmp__36);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%51 = phi i32 [ %%53, %%.critedge8.us ], [ 0, %%.preheader20.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_150_count);
  llvm_cbe_tmp__42 = (unsigned int )llvm_cbe_tmp__42__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__42);
printf("\n = 0x%X",llvm_cbe_tmp__44);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%52 = mul nsw i32 %%storemerge440.us, %%width, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_151_count);
  llvm_cbe_tmp__43 = (unsigned int )((unsigned int )(llvm_cbe_storemerge440_2e_us&4294967295ull)) * ((unsigned int )(llvm_cbe_width&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__43&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = sub i32 %%51, %%umax87, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_152_count);
  llvm_cbe_tmp__44 = (unsigned int )((unsigned int )(llvm_cbe_tmp__42&4294967295ull)) - ((unsigned int )(llvm_cbe_umax87&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__44&4294967295ull)));
  llvm_cbe_storemerge726_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv78;   /* for PHI node */
  llvm_cbe_tmp__8__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__38;   /* for PHI node */
  llvm_cbe_tmp__9__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__39;   /* for PHI node */
  llvm_cbe_tmp__10__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__40;   /* for PHI node */
  llvm_cbe_tmp__11__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__41;   /* for PHI node */
  goto llvm_cbe_tmp__70;

llvm_cbe__2e_critedge8_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = add nsw i32 %%storemerge440.us, 1, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_86_count);
  llvm_cbe_tmp__7 = (unsigned int )((unsigned int )(llvm_cbe_storemerge440_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__7&4294967295ull)));
  if (((llvm_cbe_tmp__7&4294967295U) == (llvm_cbe_tmp__4&4294967295U))) {
    llvm_cbe__2e_lcssa37__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__18;   /* for PHI node */
    llvm_cbe__2e_lcssa36__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__24;   /* for PHI node */
    llvm_cbe__2e_lcssa35__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__30;   /* for PHI node */
    llvm_cbe__2e_lcssa34__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__36;   /* for PHI node */
    llvm_cbe__2e_lcssa33__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__44;   /* for PHI node */
    goto llvm_cbe__2e_critedge;
  } else {
    llvm_cbe_storemerge440_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__7;   /* for PHI node */
    llvm_cbe_tmp__38__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__18;   /* for PHI node */
    llvm_cbe_tmp__39__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__24;   /* for PHI node */
    llvm_cbe_tmp__40__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__30;   /* for PHI node */
    llvm_cbe_tmp__41__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__36;   /* for PHI node */
    llvm_cbe_tmp__42__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__44;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph27_2e_us;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__70:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge726.us = phi i32 [ %%indvars.iv78, %%.lr.ph27.us ], [ %%46, %%16  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge726_2e_us_count);
  llvm_cbe_storemerge726_2e_us = (unsigned int )llvm_cbe_storemerge726_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge726.us = 0x%X",llvm_cbe_storemerge726_2e_us);
printf("\nindvars.iv78 = 0x%X",llvm_cbe_indvars_2e_iv78);
printf("\n = 0x%X",llvm_cbe_tmp__37);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = phi i32 [ %%47, %%.lr.ph27.us ], [ %%27, %%16  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_93_count);
  llvm_cbe_tmp__8 = (unsigned int )llvm_cbe_tmp__8__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__8);
printf("\n = 0x%X",llvm_cbe_tmp__38);
printf("\n = 0x%X",llvm_cbe_tmp__18);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = phi i32 [ %%48, %%.lr.ph27.us ], [ %%33, %%16  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_94_count);
  llvm_cbe_tmp__9 = (unsigned int )llvm_cbe_tmp__9__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__9);
printf("\n = 0x%X",llvm_cbe_tmp__39);
printf("\n = 0x%X",llvm_cbe_tmp__24);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = phi i32 [ %%49, %%.lr.ph27.us ], [ %%39, %%16  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_95_count);
  llvm_cbe_tmp__10 = (unsigned int )llvm_cbe_tmp__10__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__10);
printf("\n = 0x%X",llvm_cbe_tmp__40);
printf("\n = 0x%X",llvm_cbe_tmp__30);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = phi i32 [ %%50, %%.lr.ph27.us ], [ %%45, %%16  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_96_count);
  llvm_cbe_tmp__11 = (unsigned int )llvm_cbe_tmp__11__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__11);
printf("\n = 0x%X",llvm_cbe_tmp__41);
printf("\n = 0x%X",llvm_cbe_tmp__36);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = add nsw i32 %%storemerge726.us, %%52, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_97_count);
  llvm_cbe_tmp__12 = (unsigned int )((unsigned int )(llvm_cbe_storemerge726_2e_us&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__43&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__12&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = shl nsw i32 %%21, 2, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_98_count);
  llvm_cbe_tmp__13 = (unsigned int )llvm_cbe_tmp__12 << 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = sext i32 %%22 to i64, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_104_count);
  llvm_cbe_tmp__14 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__14);
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = getelementptr inbounds i8* %%imageRGBA, i64 %%23, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_105_count);
  llvm_cbe_tmp__15 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__14))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__14));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = load i8* %%24, align 1, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_106_count);
  llvm_cbe_tmp__16 = (unsigned char )*llvm_cbe_tmp__15;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__16);
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = zext i8 %%25 to i32, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_107_count);
  llvm_cbe_tmp__17 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__16&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__17);
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = add nsw i32 %%26, %%17, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_108_count);
  llvm_cbe_tmp__18 = (unsigned int )((unsigned int )(llvm_cbe_tmp__17&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__8&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__18&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = or i32 %%22, 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_112_count);
  llvm_cbe_tmp__19 = (unsigned int )llvm_cbe_tmp__13 | 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__19);
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = sext i32 %%28 to i64, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_113_count);
  llvm_cbe_tmp__20 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__19);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = getelementptr inbounds i8* %%imageRGBA, i64 %%29, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_114_count);
  llvm_cbe_tmp__21 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__20))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__20));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = load i8* %%30, align 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_115_count);
  llvm_cbe_tmp__22 = (unsigned char )*llvm_cbe_tmp__21;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__22);
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = zext i8 %%31 to i32, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_116_count);
  llvm_cbe_tmp__23 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__22&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__23);
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = add nsw i32 %%32, %%18, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_117_count);
  llvm_cbe_tmp__24 = (unsigned int )((unsigned int )(llvm_cbe_tmp__23&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__9&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__24&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = or i32 %%22, 2, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_121_count);
  llvm_cbe_tmp__25 = (unsigned int )llvm_cbe_tmp__13 | 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__25);
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = sext i32 %%34 to i64, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_122_count);
  llvm_cbe_tmp__26 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__25);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__26);
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = getelementptr inbounds i8* %%imageRGBA, i64 %%35, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_123_count);
  llvm_cbe_tmp__27 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__26))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__26));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = load i8* %%36, align 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_124_count);
  llvm_cbe_tmp__28 = (unsigned char )*llvm_cbe_tmp__27;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__28);
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = zext i8 %%37 to i32, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_125_count);
  llvm_cbe_tmp__29 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__28&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__29);
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = add nsw i32 %%38, %%19, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_126_count);
  llvm_cbe_tmp__30 = (unsigned int )((unsigned int )(llvm_cbe_tmp__29&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__10&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__30&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = or i32 %%22, 3, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_130_count);
  llvm_cbe_tmp__31 = (unsigned int )llvm_cbe_tmp__13 | 3u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__31);
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = sext i32 %%40 to i64, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_131_count);
  llvm_cbe_tmp__32 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__31);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__32);
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = getelementptr inbounds i8* %%imageRGBA, i64 %%41, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_132_count);
  llvm_cbe_tmp__33 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__32))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__32));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = load i8* %%42, align 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_133_count);
  llvm_cbe_tmp__34 = (unsigned char )*llvm_cbe_tmp__33;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__34);
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = zext i8 %%43 to i32, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_134_count);
  llvm_cbe_tmp__35 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__34&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__35);
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = add nsw i32 %%44, %%20, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_135_count);
  llvm_cbe_tmp__36 = (unsigned int )((unsigned int )(llvm_cbe_tmp__35&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__11&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__36&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = add nsw i32 %%storemerge726.us, 1, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_139_count);
  llvm_cbe_tmp__37 = (unsigned int )((unsigned int )(llvm_cbe_storemerge726_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__37&4294967295ull)));
  if (((llvm_cbe_tmp__37&4294967295U) == (llvm_cbe_tmp__6&4294967295U))) {
    goto llvm_cbe__2e_critedge8_2e_us;
  } else {
    llvm_cbe_storemerge726_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__37;   /* for PHI node */
    llvm_cbe_tmp__8__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__18;   /* for PHI node */
    llvm_cbe_tmp__9__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__24;   /* for PHI node */
    llvm_cbe_tmp__10__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__30;   /* for PHI node */
    llvm_cbe_tmp__11__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__36;   /* for PHI node */
    goto llvm_cbe_tmp__70;
  }

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.lr.ph27.us' */
llvm_cbe__2e_preheader20_2e_lr_2e_ph:
  if ((((signed int )llvm_cbe_indvars_2e_iv78) < ((signed int )llvm_cbe_width))) {
    llvm_cbe_storemerge440_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv111;   /* for PHI node */
    llvm_cbe_tmp__38__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe_tmp__39__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe_tmp__40__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe_tmp__41__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe_tmp__42__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph27_2e_us;
  } else {
    llvm_cbe_storemerge440__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv111;   /* for PHI node */
    goto llvm_cbe__2e_critedge8;
  }

  do {     /* Syntactic loop '.critedge8' to make GCC happy */
llvm_cbe__2e_critedge8:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge440 = phi i32 [ %%54, %%.critedge8 ], [ %%indvars.iv111, %%.preheader20.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge440_count);
  llvm_cbe_storemerge440 = (unsigned int )llvm_cbe_storemerge440__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge440 = 0x%X",llvm_cbe_storemerge440);
printf("\n = 0x%X",llvm_cbe_tmp__45);
printf("\nindvars.iv111 = 0x%X",llvm_cbe_indvars_2e_iv111);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = add nsw i32 %%storemerge440, 1, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_155_count);
  llvm_cbe_tmp__45 = (unsigned int )((unsigned int )(llvm_cbe_storemerge440&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__45&4294967295ull)));
  if (((llvm_cbe_tmp__45&4294967295U) == (llvm_cbe_tmp__4&4294967295U))) {
    llvm_cbe__2e_lcssa37__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa36__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa35__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa34__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa33__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_critedge;
  } else {
    llvm_cbe_storemerge440__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__45;   /* for PHI node */
    goto llvm_cbe__2e_critedge8;
  }

  } while (1); /* end of syntactic loop '.critedge8' */
llvm_cbe__2e__2e_critedge9_crit_edge:
  goto llvm_cbe__2e_critedge9;

llvm_cbe__2e_preheader_2e_lr_2e_ph:
  if ((((signed int )llvm_cbe_indvars_2e_iv78) < ((signed int )llvm_cbe_width))) {
    llvm_cbe_storemerge519_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv111;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  } else {
    goto llvm_cbe__2e__2e_critedge9_crit_edge;
  }

  do {     /* Syntactic loop '.lr.ph.us' to make GCC happy */
llvm_cbe__2e_lr_2e_ph_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge519.us = phi i32 [ %%64, %%.critedge10.us ], [ %%indvars.iv111, %%.preheader.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge519_2e_us_count);
  llvm_cbe_storemerge519_2e_us = (unsigned int )llvm_cbe_storemerge519_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge519.us = 0x%X",llvm_cbe_storemerge519_2e_us);
printf("\n = 0x%X",llvm_cbe_tmp__54);
printf("\nindvars.iv111 = 0x%X",llvm_cbe_indvars_2e_iv111);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%80 = mul nsw i32 %%storemerge519.us, %%width, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_217_count);
  llvm_cbe_tmp__69 = (unsigned int )((unsigned int )(llvm_cbe_storemerge519_2e_us&4294967295ull)) * ((unsigned int )(llvm_cbe_width&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__69&4294967295ull)));
  llvm_cbe_storemerge617_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv78;   /* for PHI node */
  goto llvm_cbe_tmp__71;

llvm_cbe__2e_critedge10_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%64 = add nsw i32 %%storemerge519.us, 1, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_181_count);
  llvm_cbe_tmp__54 = (unsigned int )((unsigned int )(llvm_cbe_storemerge519_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__54&4294967295ull)));
  if (((llvm_cbe_tmp__54&4294967295U) == (llvm_cbe_tmp__4&4294967295U))) {
    goto llvm_cbe__2e__2e_critedge9_crit_edge;
  } else {
    llvm_cbe_storemerge519_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__54;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__71:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge617.us = phi i32 [ %%indvars.iv78, %%.lr.ph.us ], [ %%79, %%65  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge617_2e_us_count);
  llvm_cbe_storemerge617_2e_us = (unsigned int )llvm_cbe_storemerge617_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge617.us = 0x%X",llvm_cbe_storemerge617_2e_us);
printf("\nindvars.iv78 = 0x%X",llvm_cbe_indvars_2e_iv78);
printf("\n = 0x%X",llvm_cbe_tmp__68);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%66 = add nsw i32 %%storemerge617.us, %%80, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_188_count);
  llvm_cbe_tmp__55 = (unsigned int )((unsigned int )(llvm_cbe_storemerge617_2e_us&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__69&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__55&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%67 = shl nsw i32 %%66, 2, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_189_count);
  llvm_cbe_tmp__56 = (unsigned int )llvm_cbe_tmp__55 << 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__56);
if (AESL_DEBUG_TRACE)
printf("\n  %%68 = sext i32 %%67 to i64, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_195_count);
  llvm_cbe_tmp__57 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__56);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__57);
if (AESL_DEBUG_TRACE)
printf("\n  %%69 = getelementptr inbounds i8* %%output, i64 %%68, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_196_count);
  llvm_cbe_tmp__58 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__57))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__57));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%56, i8* %%69, align 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_197_count);
  *llvm_cbe_tmp__58 = llvm_cbe_tmp__47;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n  %%70 = or i32 %%67, 1, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_198_count);
  llvm_cbe_tmp__59 = (unsigned int )llvm_cbe_tmp__56 | 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__59);
if (AESL_DEBUG_TRACE)
printf("\n  %%71 = sext i32 %%70 to i64, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_199_count);
  llvm_cbe_tmp__60 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__59);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__60);
if (AESL_DEBUG_TRACE)
printf("\n  %%72 = getelementptr inbounds i8* %%output, i64 %%71, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_200_count);
  llvm_cbe_tmp__61 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__60))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__60));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%58, i8* %%72, align 1, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_201_count);
  *llvm_cbe_tmp__61 = llvm_cbe_tmp__49;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__49);
if (AESL_DEBUG_TRACE)
printf("\n  %%73 = or i32 %%67, 2, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_202_count);
  llvm_cbe_tmp__62 = (unsigned int )llvm_cbe_tmp__56 | 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__62);
if (AESL_DEBUG_TRACE)
printf("\n  %%74 = sext i32 %%73 to i64, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_203_count);
  llvm_cbe_tmp__63 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__62);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__63);
if (AESL_DEBUG_TRACE)
printf("\n  %%75 = getelementptr inbounds i8* %%output, i64 %%74, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_204_count);
  llvm_cbe_tmp__64 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__63))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__63));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%60, i8* %%75, align 1, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_205_count);
  *llvm_cbe_tmp__64 = llvm_cbe_tmp__51;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__51);
if (AESL_DEBUG_TRACE)
printf("\n  %%76 = or i32 %%67, 3, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_206_count);
  llvm_cbe_tmp__65 = (unsigned int )llvm_cbe_tmp__56 | 3u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__65);
if (AESL_DEBUG_TRACE)
printf("\n  %%77 = sext i32 %%76 to i64, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_207_count);
  llvm_cbe_tmp__66 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__65);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__66);
if (AESL_DEBUG_TRACE)
printf("\n  %%78 = getelementptr inbounds i8* %%output, i64 %%77, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_208_count);
  llvm_cbe_tmp__67 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__66))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__66));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%62, i8* %%78, align 1, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_209_count);
  *llvm_cbe_tmp__67 = llvm_cbe_tmp__53;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__53);
if (AESL_DEBUG_TRACE)
printf("\n  %%79 = add nsw i32 %%storemerge617.us, 1, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_210_count);
  llvm_cbe_tmp__68 = (unsigned int )((unsigned int )(llvm_cbe_storemerge617_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__68&4294967295ull)));
  if (((llvm_cbe_tmp__68&4294967295U) == (llvm_cbe_tmp__6&4294967295U))) {
    goto llvm_cbe__2e_critedge10_2e_us;
  } else {
    llvm_cbe_storemerge617_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__68;   /* for PHI node */
    goto llvm_cbe_tmp__71;
  }

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.lr.ph.us' */
  } while (1); /* end of syntactic loop '.preheader32' */
llvm_cbe__2e_preheader32_2e_lr_2e_ph:
  llvm_cbe_indvars_2e_iv84__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv82__PHI_TEMPORARY = (unsigned int )15u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv80__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__1;   /* for PHI node */
  llvm_cbe_indvars_2e_iv78__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader32;

  } while (1); /* end of syntactic loop '.preheader47' */
llvm_cbe__2e__crit_edge55:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @ImageTransform}\n");
  return;
}

