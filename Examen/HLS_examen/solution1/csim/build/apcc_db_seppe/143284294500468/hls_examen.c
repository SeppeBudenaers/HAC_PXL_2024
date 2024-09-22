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
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv160_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv160;
  unsigned int llvm_cbe_indvars_2e_iv160__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv158_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv158;
  unsigned int llvm_cbe_indvars_2e_iv158__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv156_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv156;
  unsigned int llvm_cbe_indvars_2e_iv156__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv154_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv154;
  unsigned int llvm_cbe_indvars_2e_iv154__PHI_TEMPORARY;
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
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_smax162_count = 0;
  unsigned int llvm_cbe_smax162;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  unsigned int llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_umax163_count = 0;
  unsigned int llvm_cbe_umax163;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  unsigned int llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  unsigned int llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  double llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_pow213_count = 0;
  double llvm_cbe_pow213;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv116_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv116;
  unsigned int llvm_cbe_indvars_2e_iv116__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv114_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv114;
  unsigned int llvm_cbe_indvars_2e_iv114__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv112_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv112;
  unsigned int llvm_cbe_indvars_2e_iv112__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv110_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv110;
  unsigned int llvm_cbe_indvars_2e_iv110__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_smax118_count = 0;
  unsigned int llvm_cbe_smax118;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  unsigned int llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_umax119_count = 0;
  unsigned int llvm_cbe_umax119;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  unsigned int llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  unsigned int llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  double llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_pow2_count = 0;
  double llvm_cbe_pow2;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  double llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  double llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  unsigned int llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  unsigned int llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond87_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge736_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge736_2e_us;
  unsigned int llvm_cbe_storemerge736_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  unsigned int llvm_cbe_tmp__15;
  unsigned int llvm_cbe_tmp__15__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  unsigned int llvm_cbe_tmp__16;
  unsigned int llvm_cbe_tmp__16__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  unsigned int llvm_cbe_tmp__17;
  unsigned int llvm_cbe_tmp__17__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  unsigned int llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  unsigned int llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  unsigned long long llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
   char *llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  unsigned char llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  unsigned int llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  unsigned int llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  unsigned int llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  unsigned long long llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
   char *llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  unsigned char llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  unsigned int llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  unsigned int llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  unsigned int llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  unsigned long long llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
   char *llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  unsigned char llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  unsigned int llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  unsigned int llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  unsigned int llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge448_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge448_2e_us;
  unsigned int llvm_cbe_storemerge448_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  unsigned int llvm_cbe_tmp__38;
  unsigned int llvm_cbe_tmp__38__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  unsigned int llvm_cbe_tmp__39;
  unsigned int llvm_cbe_tmp__39__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  unsigned int llvm_cbe_tmp__40;
  unsigned int llvm_cbe_tmp__40__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  unsigned int llvm_cbe_tmp__41;
  unsigned int llvm_cbe_tmp__41__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  unsigned int llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  unsigned int llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  unsigned int llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond131_count = 0;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge320_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge320_2e_us;
  unsigned int llvm_cbe_storemerge320_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  unsigned int llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  unsigned int llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  unsigned long long llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
   char *llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  unsigned char llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
   char *llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  unsigned int llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  unsigned long long llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
   char *llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  unsigned char llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
   char *llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  unsigned int llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  unsigned long long llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
   char *llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  unsigned char llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
   char *llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  unsigned int llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond120_count = 0;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge223_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge223_2e_us;
  unsigned int llvm_cbe_storemerge223_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  unsigned int llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge448_count = 0;
  unsigned int llvm_cbe_storemerge448;
  unsigned int llvm_cbe_storemerge448__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  unsigned int llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond164_count = 0;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa45_count = 0;
  unsigned int llvm_cbe__2e_lcssa45;
  unsigned int llvm_cbe__2e_lcssa45__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa44_count = 0;
  unsigned int llvm_cbe__2e_lcssa44;
  unsigned int llvm_cbe__2e_lcssa44__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa43_count = 0;
  unsigned int llvm_cbe__2e_lcssa43;
  unsigned int llvm_cbe__2e_lcssa43__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa42_count = 0;
  unsigned int llvm_cbe__2e_lcssa42;
  unsigned int llvm_cbe__2e_lcssa42__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  unsigned int llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  unsigned char llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  unsigned int llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  unsigned char llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  unsigned int llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  unsigned char llvm_cbe_tmp__69;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  unsigned int llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond109_count = 0;
  static  unsigned long long aesl_llvm_cbe_234_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge626_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge626_2e_us;
  unsigned int llvm_cbe_storemerge626_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_235_count = 0;
  unsigned int llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_236_count = 0;
  unsigned int llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_237_count = 0;
  static  unsigned long long aesl_llvm_cbe_238_count = 0;
  static  unsigned long long aesl_llvm_cbe_239_count = 0;
  static  unsigned long long aesl_llvm_cbe_240_count = 0;
  static  unsigned long long aesl_llvm_cbe_241_count = 0;
  unsigned long long llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_242_count = 0;
   char *llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_243_count = 0;
  static  unsigned long long aesl_llvm_cbe_244_count = 0;
  unsigned int llvm_cbe_tmp__75;
  static  unsigned long long aesl_llvm_cbe_245_count = 0;
  unsigned long long llvm_cbe_tmp__76;
  static  unsigned long long aesl_llvm_cbe_246_count = 0;
   char *llvm_cbe_tmp__77;
  static  unsigned long long aesl_llvm_cbe_247_count = 0;
  static  unsigned long long aesl_llvm_cbe_248_count = 0;
  unsigned int llvm_cbe_tmp__78;
  static  unsigned long long aesl_llvm_cbe_249_count = 0;
  unsigned long long llvm_cbe_tmp__79;
  static  unsigned long long aesl_llvm_cbe_250_count = 0;
   char *llvm_cbe_tmp__80;
  static  unsigned long long aesl_llvm_cbe_251_count = 0;
  static  unsigned long long aesl_llvm_cbe_252_count = 0;
  unsigned int llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_253_count = 0;
  static  unsigned long long aesl_llvm_cbe_254_count = 0;
  static  unsigned long long aesl_llvm_cbe_255_count = 0;
  static  unsigned long long aesl_llvm_cbe_256_count = 0;
  static  unsigned long long aesl_llvm_cbe_257_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond98_count = 0;
  static  unsigned long long aesl_llvm_cbe_258_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge530_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge530_2e_us;
  unsigned int llvm_cbe_storemerge530_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_259_count = 0;
  unsigned int llvm_cbe_tmp__82;
  static  unsigned long long aesl_llvm_cbe_260_count = 0;
  static  unsigned long long aesl_llvm_cbe_261_count = 0;
  static  unsigned long long aesl_llvm_cbe_262_count = 0;
  static  unsigned long long aesl_llvm_cbe_263_count = 0;
  static  unsigned long long aesl_llvm_cbe_264_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next111_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next111;
  static  unsigned long long aesl_llvm_cbe_265_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next113_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next113;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next115_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next115;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next117_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next117;
  static  unsigned long long aesl_llvm_cbe_266_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next155_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next155;
  static  unsigned long long aesl_llvm_cbe_267_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next157_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next157;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next159_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next159;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next161_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next161;
  static  unsigned long long aesl_llvm_cbe_268_count = 0;
  static  unsigned long long aesl_llvm_cbe_269_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @ImageTransform\n");
  if ((((signed int )llvm_cbe_height) > ((signed int )0u))) {
    goto llvm_cbe__2e_preheader54_2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge66;
  }

llvm_cbe__2e_preheader54_2e_lr_2e_ph:
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
  llvm_cbe_indvars_2e_iv160__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv158__PHI_TEMPORARY = (unsigned int )15u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv156__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__2;   /* for PHI node */
  llvm_cbe_indvars_2e_iv154__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader54;

  do {     /* Syntactic loop '.preheader54' to make GCC happy */
llvm_cbe__2e_preheader54:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv160 = phi i32 [ 1, %%.preheader54.lr.ph ], [ %%indvars.iv.next161, %%._crit_edge ], !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv160_count);
  llvm_cbe_indvars_2e_iv160 = (unsigned int )llvm_cbe_indvars_2e_iv160__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv160 = 0x%X",llvm_cbe_indvars_2e_iv160);
printf("\n = 0x%X",1u);
printf("\nindvars.iv.next161 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next161);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv158 = phi i32 [ 15, %%.preheader54.lr.ph ], [ %%indvars.iv.next159, %%._crit_edge ], !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv158_count);
  llvm_cbe_indvars_2e_iv158 = (unsigned int )llvm_cbe_indvars_2e_iv158__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv158 = 0x%X",llvm_cbe_indvars_2e_iv158);
printf("\n = 0x%X",15u);
printf("\nindvars.iv.next159 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next159);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv156 = phi i32 [ %%4, %%.preheader54.lr.ph ], [ %%indvars.iv.next157, %%._crit_edge ], !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv156_count);
  llvm_cbe_indvars_2e_iv156 = (unsigned int )llvm_cbe_indvars_2e_iv156__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv156 = 0x%X",llvm_cbe_indvars_2e_iv156);
printf("\n = 0x%X",llvm_cbe_tmp__2);
printf("\nindvars.iv.next157 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next157);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv154 = phi i32 [ 0, %%.preheader54.lr.ph ], [ %%indvars.iv.next155, %%._crit_edge  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv154_count);
  llvm_cbe_indvars_2e_iv154 = (unsigned int )llvm_cbe_indvars_2e_iv154__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv154 = 0x%X",llvm_cbe_indvars_2e_iv154);
printf("\n = 0x%X",0u);
printf("\nindvars.iv.next155 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next155);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%smax162 = select i1 %%5, i32 %%indvars.iv158, i32 %%indvars.iv160, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_smax162_count);
  llvm_cbe_smax162 = (unsigned int )(((((signed int )llvm_cbe_indvars_2e_iv158) > ((signed int )llvm_cbe_indvars_2e_iv160))) ? ((unsigned int )llvm_cbe_indvars_2e_iv158) : ((unsigned int )llvm_cbe_indvars_2e_iv160));
if (AESL_DEBUG_TRACE)
printf("\nsmax162 = 0x%X\n", llvm_cbe_smax162);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = sub i32 %%indvars.iv154, %%smax162, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_74_count);
  llvm_cbe_tmp__3 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv154&4294967295ull)) - ((unsigned int )(llvm_cbe_smax162&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__3&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%umax163 = select i1 %%7, i32 %%indvars.iv156, i32 %%6, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_umax163_count);
  llvm_cbe_umax163 = (unsigned int )(((((unsigned int )llvm_cbe_indvars_2e_iv156&4294967295U) > ((unsigned int )llvm_cbe_tmp__3&4294967295U))) ? ((unsigned int )llvm_cbe_indvars_2e_iv156) : ((unsigned int )llvm_cbe_tmp__3));
if (AESL_DEBUG_TRACE)
printf("\numax163 = 0x%X\n", llvm_cbe_umax163);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = sub i32 %%indvars.iv154, %%umax163, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_76_count);
  llvm_cbe_tmp__4 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv154&4294967295ull)) - ((unsigned int )(llvm_cbe_umax163&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__4&4294967295ull)));
  if ((((signed int )llvm_cbe_width) > ((signed int )0u))) {
    goto llvm_cbe__2e_lr_2e_ph63;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

llvm_cbe__2e__crit_edge:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next155 = add i32 %%indvars.iv154, 15, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next155_count);
  llvm_cbe_indvars_2e_iv_2e_next155 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv154&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next155 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next155&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next157 = add i32 %%indvars.iv156, 15, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next157_count);
  llvm_cbe_indvars_2e_iv_2e_next157 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv156&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next157 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next157&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next159 = add i32 %%indvars.iv158, 15, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next159_count);
  llvm_cbe_indvars_2e_iv_2e_next159 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv158&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next159 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next159&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next161 = add i32 %%indvars.iv160, 15, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next161_count);
  llvm_cbe_indvars_2e_iv_2e_next161 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv160&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next161 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next161&4294967295ull)));
  if ((((signed int )llvm_cbe_indvars_2e_iv_2e_next155) < ((signed int )llvm_cbe_height))) {
    llvm_cbe_indvars_2e_iv160__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next161;   /* for PHI node */
    llvm_cbe_indvars_2e_iv158__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next159;   /* for PHI node */
    llvm_cbe_indvars_2e_iv156__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next157;   /* for PHI node */
    llvm_cbe_indvars_2e_iv154__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next155;   /* for PHI node */
    goto llvm_cbe__2e_preheader54;
  } else {
    goto llvm_cbe__2e__crit_edge66;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__83:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv116 = phi i32 [ 1, %%.lr.ph63 ], [ %%indvars.iv.next117, %%.critedge9 ], !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv116_count);
  llvm_cbe_indvars_2e_iv116 = (unsigned int )llvm_cbe_indvars_2e_iv116__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv116 = 0x%X",llvm_cbe_indvars_2e_iv116);
printf("\n = 0x%X",1u);
printf("\nindvars.iv.next117 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next117);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv114 = phi i32 [ 15, %%.lr.ph63 ], [ %%indvars.iv.next115, %%.critedge9 ], !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv114_count);
  llvm_cbe_indvars_2e_iv114 = (unsigned int )llvm_cbe_indvars_2e_iv114__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv114 = 0x%X",llvm_cbe_indvars_2e_iv114);
printf("\n = 0x%X",15u);
printf("\nindvars.iv.next115 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next115);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv112 = phi i32 [ %%3, %%.lr.ph63 ], [ %%indvars.iv.next113, %%.critedge9 ], !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv112_count);
  llvm_cbe_indvars_2e_iv112 = (unsigned int )llvm_cbe_indvars_2e_iv112__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv112 = 0x%X",llvm_cbe_indvars_2e_iv112);
printf("\n = 0x%X",llvm_cbe_tmp__1);
printf("\nindvars.iv.next113 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next113);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv110 = phi i32 [ 0, %%.lr.ph63 ], [ %%indvars.iv.next111, %%.critedge9  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv110_count);
  llvm_cbe_indvars_2e_iv110 = (unsigned int )llvm_cbe_indvars_2e_iv110__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv110 = 0x%X",llvm_cbe_indvars_2e_iv110);
printf("\n = 0x%X",0u);
printf("\nindvars.iv.next111 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next111);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%smax118 = select i1 %%13, i32 %%indvars.iv114, i32 %%indvars.iv116, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_smax118_count);
  llvm_cbe_smax118 = (unsigned int )(((((signed int )llvm_cbe_indvars_2e_iv114) > ((signed int )llvm_cbe_indvars_2e_iv116))) ? ((unsigned int )llvm_cbe_indvars_2e_iv114) : ((unsigned int )llvm_cbe_indvars_2e_iv116));
if (AESL_DEBUG_TRACE)
printf("\nsmax118 = 0x%X\n", llvm_cbe_smax118);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = sub i32 %%indvars.iv110, %%smax118, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_83_count);
  llvm_cbe_tmp__7 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv110&4294967295ull)) - ((unsigned int )(llvm_cbe_smax118&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__7&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%umax119 = select i1 %%15, i32 %%indvars.iv112, i32 %%14, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_umax119_count);
  llvm_cbe_umax119 = (unsigned int )(((((unsigned int )llvm_cbe_indvars_2e_iv112&4294967295U) > ((unsigned int )llvm_cbe_tmp__7&4294967295U))) ? ((unsigned int )llvm_cbe_indvars_2e_iv112) : ((unsigned int )llvm_cbe_tmp__7));
if (AESL_DEBUG_TRACE)
printf("\numax119 = 0x%X\n", llvm_cbe_umax119);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = sub i32 %%indvars.iv110, %%umax119, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_85_count);
  llvm_cbe_tmp__8 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv110&4294967295ull)) - ((unsigned int )(llvm_cbe_umax119&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__8&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = sub nsw i32 %%indvars.iv110, %%centerX, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_86_count);
  llvm_cbe_tmp__9 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv110&4294967295ull)) - ((unsigned int )(llvm_cbe_centerX&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__9&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = sitofp i32 %%17 to double, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_87_count);
  llvm_cbe_tmp__10 = (double )((double )(signed int )llvm_cbe_tmp__9);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__10, *(long long*)(&llvm_cbe_tmp__10));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow2 = fmul double %%18, %%18, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_pow2_count);
  llvm_cbe_pow2 = (double )llvm_cbe_tmp__10 * llvm_cbe_tmp__10;
if (AESL_DEBUG_TRACE)
printf("\npow2 = %lf,  0x%llx\n", llvm_cbe_pow2, *(long long*)(&llvm_cbe_pow2));
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = fadd double %%pow2, %%pow213, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_88_count);
  llvm_cbe_tmp__11 = (double )llvm_cbe_pow2 + llvm_cbe_pow213;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__11, *(long long*)(&llvm_cbe_tmp__11));
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = tail call double @sqrt(double %%19) nounwind readnone, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_89_count);
  llvm_cbe_tmp__12 = (double ) /*tail*/ sqrt(llvm_cbe_tmp__11);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__11, *(long long*)(&llvm_cbe_tmp__11));
printf("\nReturn  = %lf",llvm_cbe_tmp__12);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = fptosi double %%20 to i32, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_90_count);
  llvm_cbe_tmp__13 = (unsigned int )((signed int )llvm_cbe_tmp__12&4294967295U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__13);
  if ((((signed int )llvm_cbe_tmp__13) < ((signed int )120u))) {
    goto llvm_cbe__2e_preheader41;
  } else {
    goto llvm_cbe__2e_preheader21;
  }

llvm_cbe__2e_critedge9:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next111 = add i32 %%indvars.iv110, 15, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next111_count);
  llvm_cbe_indvars_2e_iv_2e_next111 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv110&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next111 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next111&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next113 = add i32 %%indvars.iv112, 15, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next113_count);
  llvm_cbe_indvars_2e_iv_2e_next113 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv112&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next113 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next113&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next115 = add i32 %%indvars.iv114, 15, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next115_count);
  llvm_cbe_indvars_2e_iv_2e_next115 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv114&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next115 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next115&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next117 = add i32 %%indvars.iv116, 15, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next117_count);
  llvm_cbe_indvars_2e_iv_2e_next117 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv116&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next117 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next117&4294967295ull)));
  if ((((signed int )llvm_cbe_indvars_2e_iv_2e_next111) < ((signed int )llvm_cbe_width))) {
    llvm_cbe_indvars_2e_iv116__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next117;   /* for PHI node */
    llvm_cbe_indvars_2e_iv114__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next115;   /* for PHI node */
    llvm_cbe_indvars_2e_iv112__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next113;   /* for PHI node */
    llvm_cbe_indvars_2e_iv110__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next111;   /* for PHI node */
    goto llvm_cbe_tmp__83;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

llvm_cbe__2e_critedge9_2e_loopexit:
  goto llvm_cbe__2e_critedge9;

llvm_cbe__2e_preheader21:
  if ((((signed int )llvm_cbe_indvars_2e_iv154) < ((signed int )llvm_cbe_height))) {
    goto llvm_cbe__2e_preheader_2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e_critedge9_2e_loopexit;
  }

llvm_cbe__2e__2e_critedge9_2e_loopexit_crit_edge:
  goto llvm_cbe__2e_critedge9_2e_loopexit;

llvm_cbe__2e_preheader_2e_lr_2e_ph:
  if ((((signed int )llvm_cbe_indvars_2e_iv110) < ((signed int )llvm_cbe_width))) {
    llvm_cbe_storemerge223_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv154;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  } else {
    goto llvm_cbe__2e__2e_critedge9_2e_loopexit_crit_edge;
  }

  do {     /* Syntactic loop '.lr.ph.us' to make GCC happy */
llvm_cbe__2e_lr_2e_ph_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge223.us = phi i32 [ %%56, %%.critedge12.us ], [ %%indvars.iv154, %%.preheader.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge223_2e_us_count);
  llvm_cbe_storemerge223_2e_us = (unsigned int )llvm_cbe_storemerge223_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge223.us = 0x%X",llvm_cbe_storemerge223_2e_us);
printf("\n = 0x%X",llvm_cbe_tmp__44);
printf("\nindvars.iv154 = 0x%X",llvm_cbe_indvars_2e_iv154);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%75 = mul nsw i32 %%storemerge223.us, %%width, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_198_count);
  llvm_cbe_tmp__62 = (unsigned int )((unsigned int )(llvm_cbe_storemerge223_2e_us&4294967295ull)) * ((unsigned int )(llvm_cbe_width&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__62&4294967295ull)));
  llvm_cbe_storemerge320_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv110;   /* for PHI node */
  goto llvm_cbe_tmp__84;

llvm_cbe__2e_critedge12_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = add nsw i32 %%storemerge223.us, 1, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_158_count);
  llvm_cbe_tmp__44 = (unsigned int )((unsigned int )(llvm_cbe_storemerge223_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__44&4294967295ull)));
  if (((llvm_cbe_tmp__44&4294967295U) == (llvm_cbe_tmp__4&4294967295U))) {
    goto llvm_cbe__2e__2e_critedge9_2e_loopexit_crit_edge;
  } else {
    llvm_cbe_storemerge223_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__44;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__84:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge320.us = phi i32 [ %%indvars.iv110, %%.lr.ph.us ], [ %%74, %%57  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge320_2e_us_count);
  llvm_cbe_storemerge320_2e_us = (unsigned int )llvm_cbe_storemerge320_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge320.us = 0x%X",llvm_cbe_storemerge320_2e_us);
printf("\nindvars.iv110 = 0x%X",llvm_cbe_indvars_2e_iv110);
printf("\n = 0x%X",llvm_cbe_tmp__61);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%58 = add nsw i32 %%storemerge320.us, %%75, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_165_count);
  llvm_cbe_tmp__45 = (unsigned int )((unsigned int )(llvm_cbe_storemerge320_2e_us&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__62&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__45&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%59 = mul nsw i32 %%58, 3, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_166_count);
  llvm_cbe_tmp__46 = (unsigned int )((unsigned int )(llvm_cbe_tmp__45&4294967295ull)) * ((unsigned int )(3u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__46&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%60 = sext i32 %%59 to i64, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_174_count);
  llvm_cbe_tmp__47 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__46);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n  %%61 = getelementptr inbounds i8* %%imageRGBA, i64 %%60, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_175_count);
  llvm_cbe_tmp__48 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__47))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__47));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = load i8* %%61, align 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_176_count);
  llvm_cbe_tmp__49 = (unsigned char )*llvm_cbe_tmp__48;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__49);
if (AESL_DEBUG_TRACE)
printf("\n  %%63 = getelementptr inbounds i8* %%output, i64 %%60, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_177_count);
  llvm_cbe_tmp__50 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__47))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__47));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%62, i8* %%63, align 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_178_count);
  *llvm_cbe_tmp__50 = llvm_cbe_tmp__49;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__49);
if (AESL_DEBUG_TRACE)
printf("\n  %%64 = add nsw i32 %%59, 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_179_count);
  llvm_cbe_tmp__51 = (unsigned int )((unsigned int )(llvm_cbe_tmp__46&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__51&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%65 = sext i32 %%64 to i64, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_180_count);
  llvm_cbe_tmp__52 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__51);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__52);
if (AESL_DEBUG_TRACE)
printf("\n  %%66 = getelementptr inbounds i8* %%imageRGBA, i64 %%65, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_181_count);
  llvm_cbe_tmp__53 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__52))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__52));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%67 = load i8* %%66, align 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_182_count);
  llvm_cbe_tmp__54 = (unsigned char )*llvm_cbe_tmp__53;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__54);
if (AESL_DEBUG_TRACE)
printf("\n  %%68 = getelementptr inbounds i8* %%output, i64 %%65, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_183_count);
  llvm_cbe_tmp__55 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__52))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__52));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%67, i8* %%68, align 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_184_count);
  *llvm_cbe_tmp__55 = llvm_cbe_tmp__54;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__54);
if (AESL_DEBUG_TRACE)
printf("\n  %%69 = add nsw i32 %%59, 2, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_185_count);
  llvm_cbe_tmp__56 = (unsigned int )((unsigned int )(llvm_cbe_tmp__46&4294967295ull)) + ((unsigned int )(2u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__56&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%70 = sext i32 %%69 to i64, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_186_count);
  llvm_cbe_tmp__57 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__56);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__57);
if (AESL_DEBUG_TRACE)
printf("\n  %%71 = getelementptr inbounds i8* %%imageRGBA, i64 %%70, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_187_count);
  llvm_cbe_tmp__58 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__57))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__57));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%72 = load i8* %%71, align 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_188_count);
  llvm_cbe_tmp__59 = (unsigned char )*llvm_cbe_tmp__58;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__59);
if (AESL_DEBUG_TRACE)
printf("\n  %%73 = getelementptr inbounds i8* %%output, i64 %%70, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_189_count);
  llvm_cbe_tmp__60 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__57))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__57));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%72, i8* %%73, align 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_190_count);
  *llvm_cbe_tmp__60 = llvm_cbe_tmp__59;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__59);
if (AESL_DEBUG_TRACE)
printf("\n  %%74 = add nsw i32 %%storemerge320.us, 1, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_191_count);
  llvm_cbe_tmp__61 = (unsigned int )((unsigned int )(llvm_cbe_storemerge320_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__61&4294967295ull)));
  if (((llvm_cbe_tmp__61&4294967295U) == (llvm_cbe_tmp__8&4294967295U))) {
    goto llvm_cbe__2e_critedge12_2e_us;
  } else {
    llvm_cbe_storemerge320_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__61;   /* for PHI node */
    goto llvm_cbe_tmp__84;
  }

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.lr.ph.us' */
llvm_cbe__2e_critedge9_2e_loopexit28:
  goto llvm_cbe__2e_critedge9;

llvm_cbe__2e_preheader41:
  if ((((signed int )llvm_cbe_indvars_2e_iv154) < ((signed int )llvm_cbe_height))) {
    goto llvm_cbe__2e_preheader31_2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e_critedge9_2e_loopexit28;
  }

llvm_cbe__2e_critedge:
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa45 = phi i32 [ %%35, %%.critedge8.us ], [ 0, %%.critedge8  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe__2e_lcssa45_count);
  llvm_cbe__2e_lcssa45 = (unsigned int )llvm_cbe__2e_lcssa45__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa45 = 0x%X",llvm_cbe__2e_lcssa45);
printf("\n = 0x%X",llvm_cbe_tmp__24);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa44 = phi i32 [ %%41, %%.critedge8.us ], [ 0, %%.critedge8  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe__2e_lcssa44_count);
  llvm_cbe__2e_lcssa44 = (unsigned int )llvm_cbe__2e_lcssa44__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa44 = 0x%X",llvm_cbe__2e_lcssa44);
printf("\n = 0x%X",llvm_cbe_tmp__30);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa43 = phi i32 [ %%47, %%.critedge8.us ], [ 0, %%.critedge8  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe__2e_lcssa43_count);
  llvm_cbe__2e_lcssa43 = (unsigned int )llvm_cbe__2e_lcssa43__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa43 = 0x%X",llvm_cbe__2e_lcssa43);
printf("\n = 0x%X",llvm_cbe_tmp__36);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa42 = phi i32 [ %%54, %%.critedge8.us ], [ 0, %%.critedge8  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe__2e_lcssa42_count);
  llvm_cbe__2e_lcssa42 = (unsigned int )llvm_cbe__2e_lcssa42__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa42 = 0x%X",llvm_cbe__2e_lcssa42);
printf("\n = 0x%X",llvm_cbe_tmp__43);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%77 = sdiv i32 %%.lcssa45, %%.lcssa42, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_207_count);
  llvm_cbe_tmp__64 = (unsigned int )((signed int )(((signed int )llvm_cbe__2e_lcssa45) / ((signed int )llvm_cbe__2e_lcssa42)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__64));
if (AESL_DEBUG_TRACE)
printf("\n  %%78 = trunc i32 %%77 to i8, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_208_count);
  llvm_cbe_tmp__65 = (unsigned char )((unsigned char )llvm_cbe_tmp__64&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__65);
if (AESL_DEBUG_TRACE)
printf("\n  %%79 = sdiv i32 %%.lcssa44, %%.lcssa42, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_213_count);
  llvm_cbe_tmp__66 = (unsigned int )((signed int )(((signed int )llvm_cbe__2e_lcssa44) / ((signed int )llvm_cbe__2e_lcssa42)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__66));
if (AESL_DEBUG_TRACE)
printf("\n  %%80 = trunc i32 %%79 to i8, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_214_count);
  llvm_cbe_tmp__67 = (unsigned char )((unsigned char )llvm_cbe_tmp__66&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__67);
if (AESL_DEBUG_TRACE)
printf("\n  %%81 = sdiv i32 %%.lcssa43, %%.lcssa42, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_219_count);
  llvm_cbe_tmp__68 = (unsigned int )((signed int )(((signed int )llvm_cbe__2e_lcssa43) / ((signed int )llvm_cbe__2e_lcssa42)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__68));
if (AESL_DEBUG_TRACE)
printf("\n  %%82 = trunc i32 %%81 to i8, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_220_count);
  llvm_cbe_tmp__69 = (unsigned char )((unsigned char )llvm_cbe_tmp__68&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__69);
  if ((((signed int )llvm_cbe_indvars_2e_iv154) < ((signed int )llvm_cbe_height))) {
    goto llvm_cbe__2e_preheader24_2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e_critedge9_2e_loopexit28;
  }

  do {     /* Syntactic loop '.lr.ph37.us' to make GCC happy */
llvm_cbe__2e_lr_2e_ph37_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge448.us = phi i32 [ %%24, %%.critedge8.us ], [ %%indvars.iv154, %%.preheader31.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge448_2e_us_count);
  llvm_cbe_storemerge448_2e_us = (unsigned int )llvm_cbe_storemerge448_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge448.us = 0x%X",llvm_cbe_storemerge448_2e_us);
printf("\n = 0x%X",llvm_cbe_tmp__14);
printf("\nindvars.iv154 = 0x%X",llvm_cbe_indvars_2e_iv154);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%49 = phi i32 [ %%35, %%.critedge8.us ], [ 0, %%.preheader31.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_147_count);
  llvm_cbe_tmp__38 = (unsigned int )llvm_cbe_tmp__38__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__38);
printf("\n = 0x%X",llvm_cbe_tmp__24);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%50 = phi i32 [ %%41, %%.critedge8.us ], [ 0, %%.preheader31.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_148_count);
  llvm_cbe_tmp__39 = (unsigned int )llvm_cbe_tmp__39__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__39);
printf("\n = 0x%X",llvm_cbe_tmp__30);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%51 = phi i32 [ %%47, %%.critedge8.us ], [ 0, %%.preheader31.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_149_count);
  llvm_cbe_tmp__40 = (unsigned int )llvm_cbe_tmp__40__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__40);
printf("\n = 0x%X",llvm_cbe_tmp__36);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%52 = phi i32 [ %%54, %%.critedge8.us ], [ 0, %%.preheader31.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_150_count);
  llvm_cbe_tmp__41 = (unsigned int )llvm_cbe_tmp__41__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__41);
printf("\n = 0x%X",llvm_cbe_tmp__43);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = mul nsw i32 %%storemerge448.us, %%width, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_151_count);
  llvm_cbe_tmp__42 = (unsigned int )((unsigned int )(llvm_cbe_storemerge448_2e_us&4294967295ull)) * ((unsigned int )(llvm_cbe_width&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__42&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = sub i32 %%52, %%umax119, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_152_count);
  llvm_cbe_tmp__43 = (unsigned int )((unsigned int )(llvm_cbe_tmp__41&4294967295ull)) - ((unsigned int )(llvm_cbe_umax119&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__43&4294967295ull)));
  llvm_cbe_storemerge736_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv110;   /* for PHI node */
  llvm_cbe_tmp__15__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__38;   /* for PHI node */
  llvm_cbe_tmp__16__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__39;   /* for PHI node */
  llvm_cbe_tmp__17__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__40;   /* for PHI node */
  goto llvm_cbe_tmp__85;

llvm_cbe__2e_critedge8_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = add nsw i32 %%storemerge448.us, 1, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_98_count);
  llvm_cbe_tmp__14 = (unsigned int )((unsigned int )(llvm_cbe_storemerge448_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__14&4294967295ull)));
  if (((llvm_cbe_tmp__14&4294967295U) == (llvm_cbe_tmp__4&4294967295U))) {
    llvm_cbe__2e_lcssa45__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__24;   /* for PHI node */
    llvm_cbe__2e_lcssa44__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__30;   /* for PHI node */
    llvm_cbe__2e_lcssa43__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__36;   /* for PHI node */
    llvm_cbe__2e_lcssa42__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__43;   /* for PHI node */
    goto llvm_cbe__2e_critedge;
  } else {
    llvm_cbe_storemerge448_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__14;   /* for PHI node */
    llvm_cbe_tmp__38__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__24;   /* for PHI node */
    llvm_cbe_tmp__39__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__30;   /* for PHI node */
    llvm_cbe_tmp__40__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__36;   /* for PHI node */
    llvm_cbe_tmp__41__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__43;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph37_2e_us;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__85:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge736.us = phi i32 [ %%indvars.iv110, %%.lr.ph37.us ], [ %%48, %%25  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge736_2e_us_count);
  llvm_cbe_storemerge736_2e_us = (unsigned int )llvm_cbe_storemerge736_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge736.us = 0x%X",llvm_cbe_storemerge736_2e_us);
printf("\nindvars.iv110 = 0x%X",llvm_cbe_indvars_2e_iv110);
printf("\n = 0x%X",llvm_cbe_tmp__37);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = phi i32 [ %%49, %%.lr.ph37.us ], [ %%35, %%25  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_105_count);
  llvm_cbe_tmp__15 = (unsigned int )llvm_cbe_tmp__15__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__15);
printf("\n = 0x%X",llvm_cbe_tmp__38);
printf("\n = 0x%X",llvm_cbe_tmp__24);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = phi i32 [ %%50, %%.lr.ph37.us ], [ %%41, %%25  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_106_count);
  llvm_cbe_tmp__16 = (unsigned int )llvm_cbe_tmp__16__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__16);
printf("\n = 0x%X",llvm_cbe_tmp__39);
printf("\n = 0x%X",llvm_cbe_tmp__30);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = phi i32 [ %%51, %%.lr.ph37.us ], [ %%47, %%25  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_107_count);
  llvm_cbe_tmp__17 = (unsigned int )llvm_cbe_tmp__17__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__17);
printf("\n = 0x%X",llvm_cbe_tmp__40);
printf("\n = 0x%X",llvm_cbe_tmp__36);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = add nsw i32 %%storemerge736.us, %%53, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_108_count);
  llvm_cbe_tmp__18 = (unsigned int )((unsigned int )(llvm_cbe_storemerge736_2e_us&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__42&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__18&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = mul nsw i32 %%29, 3, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_109_count);
  llvm_cbe_tmp__19 = (unsigned int )((unsigned int )(llvm_cbe_tmp__18&4294967295ull)) * ((unsigned int )(3u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__19&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = sext i32 %%30 to i64, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_114_count);
  llvm_cbe_tmp__20 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__19);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = getelementptr inbounds i8* %%imageRGBA, i64 %%31, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_115_count);
  llvm_cbe_tmp__21 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__20))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__20));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = load i8* %%32, align 1, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_116_count);
  llvm_cbe_tmp__22 = (unsigned char )*llvm_cbe_tmp__21;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__22);
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = zext i8 %%33 to i32, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_117_count);
  llvm_cbe_tmp__23 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__22&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__23);
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = add nsw i32 %%34, %%26, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_118_count);
  llvm_cbe_tmp__24 = (unsigned int )((unsigned int )(llvm_cbe_tmp__23&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__15&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__24&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = add nsw i32 %%30, 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_122_count);
  llvm_cbe_tmp__25 = (unsigned int )((unsigned int )(llvm_cbe_tmp__19&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__25&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = sext i32 %%36 to i64, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_123_count);
  llvm_cbe_tmp__26 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__25);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__26);
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = getelementptr inbounds i8* %%imageRGBA, i64 %%37, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_124_count);
  llvm_cbe_tmp__27 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__26))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__26));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = load i8* %%38, align 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_125_count);
  llvm_cbe_tmp__28 = (unsigned char )*llvm_cbe_tmp__27;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__28);
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = zext i8 %%39 to i32, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_126_count);
  llvm_cbe_tmp__29 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__28&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__29);
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = add nsw i32 %%40, %%27, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_127_count);
  llvm_cbe_tmp__30 = (unsigned int )((unsigned int )(llvm_cbe_tmp__29&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__16&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__30&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = add nsw i32 %%30, 2, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_131_count);
  llvm_cbe_tmp__31 = (unsigned int )((unsigned int )(llvm_cbe_tmp__19&4294967295ull)) + ((unsigned int )(2u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__31&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = sext i32 %%42 to i64, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_132_count);
  llvm_cbe_tmp__32 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__31);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__32);
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = getelementptr inbounds i8* %%imageRGBA, i64 %%43, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_133_count);
  llvm_cbe_tmp__33 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__32))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__32));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = load i8* %%44, align 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_134_count);
  llvm_cbe_tmp__34 = (unsigned char )*llvm_cbe_tmp__33;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__34);
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = zext i8 %%45 to i32, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_135_count);
  llvm_cbe_tmp__35 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__34&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__35);
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = add nsw i32 %%46, %%28, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_136_count);
  llvm_cbe_tmp__36 = (unsigned int )((unsigned int )(llvm_cbe_tmp__35&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__17&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__36&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%48 = add nsw i32 %%storemerge736.us, 1, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_140_count);
  llvm_cbe_tmp__37 = (unsigned int )((unsigned int )(llvm_cbe_storemerge736_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__37&4294967295ull)));
  if (((llvm_cbe_tmp__37&4294967295U) == (llvm_cbe_tmp__8&4294967295U))) {
    goto llvm_cbe__2e_critedge8_2e_us;
  } else {
    llvm_cbe_storemerge736_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__37;   /* for PHI node */
    llvm_cbe_tmp__15__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__24;   /* for PHI node */
    llvm_cbe_tmp__16__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__30;   /* for PHI node */
    llvm_cbe_tmp__17__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__36;   /* for PHI node */
    goto llvm_cbe_tmp__85;
  }

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.lr.ph37.us' */
llvm_cbe__2e_preheader31_2e_lr_2e_ph:
  if ((((signed int )llvm_cbe_indvars_2e_iv110) < ((signed int )llvm_cbe_width))) {
    llvm_cbe_storemerge448_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv154;   /* for PHI node */
    llvm_cbe_tmp__38__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe_tmp__39__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe_tmp__40__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe_tmp__41__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph37_2e_us;
  } else {
    llvm_cbe_storemerge448__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv154;   /* for PHI node */
    goto llvm_cbe__2e_critedge8;
  }

  do {     /* Syntactic loop '.critedge8' to make GCC happy */
llvm_cbe__2e_critedge8:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge448 = phi i32 [ %%76, %%.critedge8 ], [ %%indvars.iv154, %%.preheader31.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge448_count);
  llvm_cbe_storemerge448 = (unsigned int )llvm_cbe_storemerge448__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge448 = 0x%X",llvm_cbe_storemerge448);
printf("\n = 0x%X",llvm_cbe_tmp__63);
printf("\nindvars.iv154 = 0x%X",llvm_cbe_indvars_2e_iv154);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%76 = add nsw i32 %%storemerge448, 1, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_200_count);
  llvm_cbe_tmp__63 = (unsigned int )((unsigned int )(llvm_cbe_storemerge448&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__63&4294967295ull)));
  if (((llvm_cbe_tmp__63&4294967295U) == (llvm_cbe_tmp__4&4294967295U))) {
    llvm_cbe__2e_lcssa45__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa44__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa43__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa42__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_critedge;
  } else {
    llvm_cbe_storemerge448__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__63;   /* for PHI node */
    goto llvm_cbe__2e_critedge8;
  }

  } while (1); /* end of syntactic loop '.critedge8' */
llvm_cbe__2e__2e_critedge9_2e_loopexit28_crit_edge:
  goto llvm_cbe__2e_critedge9_2e_loopexit28;

llvm_cbe__2e_preheader24_2e_lr_2e_ph:
  if ((((signed int )llvm_cbe_indvars_2e_iv110) < ((signed int )llvm_cbe_width))) {
    llvm_cbe_storemerge530_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv154;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph27_2e_us;
  } else {
    goto llvm_cbe__2e__2e_critedge9_2e_loopexit28_crit_edge;
  }

  do {     /* Syntactic loop '.lr.ph27.us' to make GCC happy */
llvm_cbe__2e_lr_2e_ph27_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge530.us = phi i32 [ %%84, %%.critedge10.us ], [ %%indvars.iv154, %%.preheader24.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge530_2e_us_count);
  llvm_cbe_storemerge530_2e_us = (unsigned int )llvm_cbe_storemerge530_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge530.us = 0x%X",llvm_cbe_storemerge530_2e_us);
printf("\n = 0x%X",llvm_cbe_tmp__70);
printf("\nindvars.iv154 = 0x%X",llvm_cbe_indvars_2e_iv154);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%97 = mul nsw i32 %%storemerge530.us, %%width, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_259_count);
  llvm_cbe_tmp__82 = (unsigned int )((unsigned int )(llvm_cbe_storemerge530_2e_us&4294967295ull)) * ((unsigned int )(llvm_cbe_width&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__82&4294967295ull)));
  llvm_cbe_storemerge626_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv110;   /* for PHI node */
  goto llvm_cbe_tmp__86;

llvm_cbe__2e_critedge10_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%84 = add nsw i32 %%storemerge530.us, 1, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_228_count);
  llvm_cbe_tmp__70 = (unsigned int )((unsigned int )(llvm_cbe_storemerge530_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__70&4294967295ull)));
  if (((llvm_cbe_tmp__70&4294967295U) == (llvm_cbe_tmp__4&4294967295U))) {
    goto llvm_cbe__2e__2e_critedge9_2e_loopexit28_crit_edge;
  } else {
    llvm_cbe_storemerge530_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__70;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph27_2e_us;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__86:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge626.us = phi i32 [ %%indvars.iv110, %%.lr.ph27.us ], [ %%96, %%85  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge626_2e_us_count);
  llvm_cbe_storemerge626_2e_us = (unsigned int )llvm_cbe_storemerge626_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge626.us = 0x%X",llvm_cbe_storemerge626_2e_us);
printf("\nindvars.iv110 = 0x%X",llvm_cbe_indvars_2e_iv110);
printf("\n = 0x%X",llvm_cbe_tmp__81);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%86 = add nsw i32 %%storemerge626.us, %%97, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_235_count);
  llvm_cbe_tmp__71 = (unsigned int )((unsigned int )(llvm_cbe_storemerge626_2e_us&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__82&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__71&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%87 = mul nsw i32 %%86, 3, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_236_count);
  llvm_cbe_tmp__72 = (unsigned int )((unsigned int )(llvm_cbe_tmp__71&4294967295ull)) * ((unsigned int )(3u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__72&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%88 = sext i32 %%87 to i64, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_241_count);
  llvm_cbe_tmp__73 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__72);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__73);
if (AESL_DEBUG_TRACE)
printf("\n  %%89 = getelementptr inbounds i8* %%output, i64 %%88, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_242_count);
  llvm_cbe_tmp__74 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__73))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__73));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%78, i8* %%89, align 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_243_count);
  *llvm_cbe_tmp__74 = llvm_cbe_tmp__65;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__65);
if (AESL_DEBUG_TRACE)
printf("\n  %%90 = add nsw i32 %%87, 1, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_244_count);
  llvm_cbe_tmp__75 = (unsigned int )((unsigned int )(llvm_cbe_tmp__72&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__75&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%91 = sext i32 %%90 to i64, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_245_count);
  llvm_cbe_tmp__76 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__75);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__76);
if (AESL_DEBUG_TRACE)
printf("\n  %%92 = getelementptr inbounds i8* %%output, i64 %%91, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_246_count);
  llvm_cbe_tmp__77 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__76))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__76));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%80, i8* %%92, align 1, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_247_count);
  *llvm_cbe_tmp__77 = llvm_cbe_tmp__67;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__67);
if (AESL_DEBUG_TRACE)
printf("\n  %%93 = add nsw i32 %%87, 2, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_248_count);
  llvm_cbe_tmp__78 = (unsigned int )((unsigned int )(llvm_cbe_tmp__72&4294967295ull)) + ((unsigned int )(2u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__78&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%94 = sext i32 %%93 to i64, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_249_count);
  llvm_cbe_tmp__79 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__78);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__79);
if (AESL_DEBUG_TRACE)
printf("\n  %%95 = getelementptr inbounds i8* %%output, i64 %%94, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_250_count);
  llvm_cbe_tmp__80 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__79))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__79));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%82, i8* %%95, align 1, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_251_count);
  *llvm_cbe_tmp__80 = llvm_cbe_tmp__69;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__69);
if (AESL_DEBUG_TRACE)
printf("\n  %%96 = add nsw i32 %%storemerge626.us, 1, !dbg !11 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_252_count);
  llvm_cbe_tmp__81 = (unsigned int )((unsigned int )(llvm_cbe_storemerge626_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__81&4294967295ull)));
  if (((llvm_cbe_tmp__81&4294967295U) == (llvm_cbe_tmp__8&4294967295U))) {
    goto llvm_cbe__2e_critedge10_2e_us;
  } else {
    llvm_cbe_storemerge626_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__81;   /* for PHI node */
    goto llvm_cbe_tmp__86;
  }

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.lr.ph27.us' */
  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e_lr_2e_ph63:
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = sub nsw i32 %%indvars.iv154, %%centerY, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_78_count);
  llvm_cbe_tmp__5 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv154&4294967295ull)) - ((unsigned int )(llvm_cbe_centerY&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__5&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = sitofp i32 %%9 to double, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_79_count);
  llvm_cbe_tmp__6 = (double )((double )(signed int )llvm_cbe_tmp__5);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__6, *(long long*)(&llvm_cbe_tmp__6));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow213 = fmul double %%10, %%10, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_pow213_count);
  llvm_cbe_pow213 = (double )llvm_cbe_tmp__6 * llvm_cbe_tmp__6;
if (AESL_DEBUG_TRACE)
printf("\npow213 = %lf,  0x%llx\n", llvm_cbe_pow213, *(long long*)(&llvm_cbe_pow213));
  llvm_cbe_indvars_2e_iv116__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv114__PHI_TEMPORARY = (unsigned int )15u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv112__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__1;   /* for PHI node */
  llvm_cbe_indvars_2e_iv110__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__83;

  } while (1); /* end of syntactic loop '.preheader54' */
llvm_cbe__2e__crit_edge66:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @ImageTransform}\n");
  return;
}

