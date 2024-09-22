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
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  unsigned int llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  unsigned int llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv165_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv165;
  unsigned int llvm_cbe_indvars_2e_iv165__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv163_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv163;
  unsigned int llvm_cbe_indvars_2e_iv163__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv161_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv161;
  unsigned int llvm_cbe_indvars_2e_iv161__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv159_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv159;
  unsigned int llvm_cbe_indvars_2e_iv159__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_smax167_count = 0;
  unsigned int llvm_cbe_smax167;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  unsigned int llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_umax168_count = 0;
  unsigned int llvm_cbe_umax168;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  unsigned int llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  unsigned int llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  double llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_pow213_count = 0;
  double llvm_cbe_pow213;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv121_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv121;
  unsigned int llvm_cbe_indvars_2e_iv121__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv119_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv119;
  unsigned int llvm_cbe_indvars_2e_iv119__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv117_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv117;
  unsigned int llvm_cbe_indvars_2e_iv117__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv115_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv115;
  unsigned int llvm_cbe_indvars_2e_iv115__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_smax123_count = 0;
  unsigned int llvm_cbe_smax123;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  unsigned int llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_umax124_count = 0;
  unsigned int llvm_cbe_umax124;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  unsigned int llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  unsigned int llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  double llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_pow2_count = 0;
  double llvm_cbe_pow2;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  double llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  double llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  unsigned int llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  unsigned int llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond92_count = 0;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge737_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge737_2e_us;
  unsigned int llvm_cbe_storemerge737_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  unsigned int llvm_cbe_tmp__15;
  unsigned int llvm_cbe_tmp__15__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  unsigned int llvm_cbe_tmp__16;
  unsigned int llvm_cbe_tmp__16__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  unsigned int llvm_cbe_tmp__17;
  unsigned int llvm_cbe_tmp__17__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  unsigned int llvm_cbe_tmp__18;
  unsigned int llvm_cbe_tmp__18__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  unsigned int llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  unsigned int llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  unsigned long long llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
   char *llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  unsigned char llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  unsigned int llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  unsigned int llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  unsigned int llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  unsigned long long llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
   char *llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  unsigned char llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  unsigned int llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  unsigned int llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  unsigned int llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  unsigned long long llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
   char *llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  unsigned char llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  unsigned int llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  unsigned int llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  unsigned int llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  unsigned long long llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
   char *llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  unsigned char llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  unsigned int llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  unsigned int llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  unsigned int llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge451_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge451_2e_us;
  unsigned int llvm_cbe_storemerge451_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  unsigned int llvm_cbe_tmp__45;
  unsigned int llvm_cbe_tmp__45__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  unsigned int llvm_cbe_tmp__46;
  unsigned int llvm_cbe_tmp__46__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  unsigned int llvm_cbe_tmp__47;
  unsigned int llvm_cbe_tmp__47__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  unsigned int llvm_cbe_tmp__48;
  unsigned int llvm_cbe_tmp__48__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  unsigned int llvm_cbe_tmp__49;
  unsigned int llvm_cbe_tmp__49__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  unsigned int llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  unsigned int llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  unsigned int llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond136_count = 0;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge320_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge320_2e_us;
  unsigned int llvm_cbe_storemerge320_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  unsigned int llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  unsigned int llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  unsigned long long llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
   char *llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  unsigned char llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
   char *llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  unsigned int llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  unsigned long long llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
   char *llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  unsigned char llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
   char *llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  unsigned int llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  unsigned long long llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
   char *llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  unsigned char llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
   char *llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;
  unsigned int llvm_cbe_tmp__69;
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
  unsigned long long llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
   char *llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  unsigned char llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
   char *llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
  unsigned int llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond125_count = 0;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge223_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge223_2e_us;
  unsigned int llvm_cbe_storemerge223_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  unsigned int llvm_cbe_tmp__75;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge451_count = 0;
  unsigned int llvm_cbe_storemerge451;
  unsigned int llvm_cbe_storemerge451__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  unsigned int llvm_cbe_tmp__76;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond169_count = 0;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa48_count = 0;
  unsigned int llvm_cbe__2e_lcssa48;
  unsigned int llvm_cbe__2e_lcssa48__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa47_count = 0;
  unsigned int llvm_cbe__2e_lcssa47;
  unsigned int llvm_cbe__2e_lcssa47__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa46_count = 0;
  unsigned int llvm_cbe__2e_lcssa46;
  unsigned int llvm_cbe__2e_lcssa46__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa45_count = 0;
  unsigned int llvm_cbe__2e_lcssa45;
  unsigned int llvm_cbe__2e_lcssa45__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa44_count = 0;
  unsigned int llvm_cbe__2e_lcssa44;
  unsigned int llvm_cbe__2e_lcssa44__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  unsigned int llvm_cbe_tmp__77;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
  unsigned char llvm_cbe_tmp__78;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
  static  unsigned long long aesl_llvm_cbe_234_count = 0;
  static  unsigned long long aesl_llvm_cbe_235_count = 0;
  unsigned int llvm_cbe_tmp__79;
  static  unsigned long long aesl_llvm_cbe_236_count = 0;
  unsigned char llvm_cbe_tmp__80;
  static  unsigned long long aesl_llvm_cbe_237_count = 0;
  static  unsigned long long aesl_llvm_cbe_238_count = 0;
  static  unsigned long long aesl_llvm_cbe_239_count = 0;
  unsigned int llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_240_count = 0;
  unsigned char llvm_cbe_tmp__82;
  static  unsigned long long aesl_llvm_cbe_241_count = 0;
  static  unsigned long long aesl_llvm_cbe_242_count = 0;
  static  unsigned long long aesl_llvm_cbe_243_count = 0;
  unsigned int llvm_cbe_tmp__83;
  static  unsigned long long aesl_llvm_cbe_244_count = 0;
  unsigned char llvm_cbe_tmp__84;
  static  unsigned long long aesl_llvm_cbe_245_count = 0;
  static  unsigned long long aesl_llvm_cbe_246_count = 0;
  static  unsigned long long aesl_llvm_cbe_247_count = 0;
  static  unsigned long long aesl_llvm_cbe_248_count = 0;
  static  unsigned long long aesl_llvm_cbe_249_count = 0;
  static  unsigned long long aesl_llvm_cbe_250_count = 0;
  unsigned int llvm_cbe_tmp__85;
  static  unsigned long long aesl_llvm_cbe_251_count = 0;
  static  unsigned long long aesl_llvm_cbe_252_count = 0;
  static  unsigned long long aesl_llvm_cbe_253_count = 0;
  static  unsigned long long aesl_llvm_cbe_254_count = 0;
  static  unsigned long long aesl_llvm_cbe_255_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond114_count = 0;
  static  unsigned long long aesl_llvm_cbe_256_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge626_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge626_2e_us;
  unsigned int llvm_cbe_storemerge626_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_257_count = 0;
  unsigned int llvm_cbe_tmp__86;
  static  unsigned long long aesl_llvm_cbe_258_count = 0;
  unsigned int llvm_cbe_tmp__87;
  static  unsigned long long aesl_llvm_cbe_259_count = 0;
  static  unsigned long long aesl_llvm_cbe_260_count = 0;
  static  unsigned long long aesl_llvm_cbe_261_count = 0;
  static  unsigned long long aesl_llvm_cbe_262_count = 0;
  static  unsigned long long aesl_llvm_cbe_263_count = 0;
  static  unsigned long long aesl_llvm_cbe_264_count = 0;
  unsigned long long llvm_cbe_tmp__88;
  static  unsigned long long aesl_llvm_cbe_265_count = 0;
   char *llvm_cbe_tmp__89;
  static  unsigned long long aesl_llvm_cbe_266_count = 0;
  static  unsigned long long aesl_llvm_cbe_267_count = 0;
  unsigned int llvm_cbe_tmp__90;
  static  unsigned long long aesl_llvm_cbe_268_count = 0;
  unsigned long long llvm_cbe_tmp__91;
  static  unsigned long long aesl_llvm_cbe_269_count = 0;
   char *llvm_cbe_tmp__92;
  static  unsigned long long aesl_llvm_cbe_270_count = 0;
  static  unsigned long long aesl_llvm_cbe_271_count = 0;
  unsigned int llvm_cbe_tmp__93;
  static  unsigned long long aesl_llvm_cbe_272_count = 0;
  unsigned long long llvm_cbe_tmp__94;
  static  unsigned long long aesl_llvm_cbe_273_count = 0;
   char *llvm_cbe_tmp__95;
  static  unsigned long long aesl_llvm_cbe_274_count = 0;
  static  unsigned long long aesl_llvm_cbe_275_count = 0;
  unsigned int llvm_cbe_tmp__96;
  static  unsigned long long aesl_llvm_cbe_276_count = 0;
  unsigned long long llvm_cbe_tmp__97;
  static  unsigned long long aesl_llvm_cbe_277_count = 0;
   char *llvm_cbe_tmp__98;
  static  unsigned long long aesl_llvm_cbe_278_count = 0;
  static  unsigned long long aesl_llvm_cbe_279_count = 0;
  unsigned int llvm_cbe_tmp__99;
  static  unsigned long long aesl_llvm_cbe_280_count = 0;
  static  unsigned long long aesl_llvm_cbe_281_count = 0;
  static  unsigned long long aesl_llvm_cbe_282_count = 0;
  static  unsigned long long aesl_llvm_cbe_283_count = 0;
  static  unsigned long long aesl_llvm_cbe_284_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond103_count = 0;
  static  unsigned long long aesl_llvm_cbe_285_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge530_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge530_2e_us;
  unsigned int llvm_cbe_storemerge530_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_286_count = 0;
  unsigned int llvm_cbe_tmp__100;
  static  unsigned long long aesl_llvm_cbe_287_count = 0;
  static  unsigned long long aesl_llvm_cbe_288_count = 0;
  static  unsigned long long aesl_llvm_cbe_289_count = 0;
  static  unsigned long long aesl_llvm_cbe_290_count = 0;
  static  unsigned long long aesl_llvm_cbe_291_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next116_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next116;
  static  unsigned long long aesl_llvm_cbe_292_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next118_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next118;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next120_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next120;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next122_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next122;
  static  unsigned long long aesl_llvm_cbe_293_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next160_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next160;
  static  unsigned long long aesl_llvm_cbe_294_count = 0;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next162_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next162;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next164_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next164;
  static  unsigned long long aesl_llvm_cbe_indvars_2e_iv_2e_next166_count = 0;
  unsigned int llvm_cbe_indvars_2e_iv_2e_next166;
  static  unsigned long long aesl_llvm_cbe_295_count = 0;
  static  unsigned long long aesl_llvm_cbe_296_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @ImageTransform\n");
  if ((((signed int )llvm_cbe_height) > ((signed int )0u))) {
    goto llvm_cbe__2e_preheader58_2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge70;
  }

llvm_cbe__2e_preheader58_2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = sub i32 0, %%width, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_62_count);
  llvm_cbe_tmp__1 = (unsigned int )-(llvm_cbe_width);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__1&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = sub i32 0, %%height, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_63_count);
  llvm_cbe_tmp__2 = (unsigned int )-(llvm_cbe_height);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__2&4294967295ull)));
  llvm_cbe_indvars_2e_iv165__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv163__PHI_TEMPORARY = (unsigned int )15u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv161__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__2;   /* for PHI node */
  llvm_cbe_indvars_2e_iv159__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader58;

  do {     /* Syntactic loop '.preheader58' to make GCC happy */
llvm_cbe__2e_preheader58:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv165 = phi i32 [ 1, %%.preheader58.lr.ph ], [ %%indvars.iv.next166, %%._crit_edge ], !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv165_count);
  llvm_cbe_indvars_2e_iv165 = (unsigned int )llvm_cbe_indvars_2e_iv165__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv165 = 0x%X",llvm_cbe_indvars_2e_iv165);
printf("\n = 0x%X",1u);
printf("\nindvars.iv.next166 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next166);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv163 = phi i32 [ 15, %%.preheader58.lr.ph ], [ %%indvars.iv.next164, %%._crit_edge ], !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv163_count);
  llvm_cbe_indvars_2e_iv163 = (unsigned int )llvm_cbe_indvars_2e_iv163__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv163 = 0x%X",llvm_cbe_indvars_2e_iv163);
printf("\n = 0x%X",15u);
printf("\nindvars.iv.next164 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next164);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv161 = phi i32 [ %%4, %%.preheader58.lr.ph ], [ %%indvars.iv.next162, %%._crit_edge ], !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv161_count);
  llvm_cbe_indvars_2e_iv161 = (unsigned int )llvm_cbe_indvars_2e_iv161__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv161 = 0x%X",llvm_cbe_indvars_2e_iv161);
printf("\n = 0x%X",llvm_cbe_tmp__2);
printf("\nindvars.iv.next162 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next162);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv159 = phi i32 [ 0, %%.preheader58.lr.ph ], [ %%indvars.iv.next160, %%._crit_edge  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv159_count);
  llvm_cbe_indvars_2e_iv159 = (unsigned int )llvm_cbe_indvars_2e_iv159__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv159 = 0x%X",llvm_cbe_indvars_2e_iv159);
printf("\n = 0x%X",0u);
printf("\nindvars.iv.next160 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next160);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%smax167 = select i1 %%5, i32 %%indvars.iv163, i32 %%indvars.iv165, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_smax167_count);
  llvm_cbe_smax167 = (unsigned int )(((((signed int )llvm_cbe_indvars_2e_iv163) > ((signed int )llvm_cbe_indvars_2e_iv165))) ? ((unsigned int )llvm_cbe_indvars_2e_iv163) : ((unsigned int )llvm_cbe_indvars_2e_iv165));
if (AESL_DEBUG_TRACE)
printf("\nsmax167 = 0x%X\n", llvm_cbe_smax167);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = sub i32 %%indvars.iv159, %%smax167, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_78_count);
  llvm_cbe_tmp__3 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv159&4294967295ull)) - ((unsigned int )(llvm_cbe_smax167&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__3&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%umax168 = select i1 %%7, i32 %%indvars.iv161, i32 %%6, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_umax168_count);
  llvm_cbe_umax168 = (unsigned int )(((((unsigned int )llvm_cbe_indvars_2e_iv161&4294967295U) > ((unsigned int )llvm_cbe_tmp__3&4294967295U))) ? ((unsigned int )llvm_cbe_indvars_2e_iv161) : ((unsigned int )llvm_cbe_tmp__3));
if (AESL_DEBUG_TRACE)
printf("\numax168 = 0x%X\n", llvm_cbe_umax168);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = sub i32 %%indvars.iv159, %%umax168, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_80_count);
  llvm_cbe_tmp__4 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv159&4294967295ull)) - ((unsigned int )(llvm_cbe_umax168&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__4&4294967295ull)));
  if ((((signed int )llvm_cbe_width) > ((signed int )0u))) {
    goto llvm_cbe__2e_lr_2e_ph67;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

llvm_cbe__2e__crit_edge:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next160 = add i32 %%indvars.iv159, 15, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next160_count);
  llvm_cbe_indvars_2e_iv_2e_next160 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv159&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next160 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next160&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next162 = add i32 %%indvars.iv161, 15, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next162_count);
  llvm_cbe_indvars_2e_iv_2e_next162 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv161&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next162 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next162&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next164 = add i32 %%indvars.iv163, 15, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next164_count);
  llvm_cbe_indvars_2e_iv_2e_next164 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv163&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next164 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next164&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next166 = add i32 %%indvars.iv165, 15, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next166_count);
  llvm_cbe_indvars_2e_iv_2e_next166 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv165&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next166 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next166&4294967295ull)));
  if ((((signed int )llvm_cbe_indvars_2e_iv_2e_next160) < ((signed int )llvm_cbe_height))) {
    llvm_cbe_indvars_2e_iv165__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next166;   /* for PHI node */
    llvm_cbe_indvars_2e_iv163__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next164;   /* for PHI node */
    llvm_cbe_indvars_2e_iv161__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next162;   /* for PHI node */
    llvm_cbe_indvars_2e_iv159__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next160;   /* for PHI node */
    goto llvm_cbe__2e_preheader58;
  } else {
    goto llvm_cbe__2e__crit_edge70;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__101:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv121 = phi i32 [ 1, %%.lr.ph67 ], [ %%indvars.iv.next122, %%.critedge9 ], !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv121_count);
  llvm_cbe_indvars_2e_iv121 = (unsigned int )llvm_cbe_indvars_2e_iv121__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv121 = 0x%X",llvm_cbe_indvars_2e_iv121);
printf("\n = 0x%X",1u);
printf("\nindvars.iv.next122 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next122);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv119 = phi i32 [ 15, %%.lr.ph67 ], [ %%indvars.iv.next120, %%.critedge9 ], !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv119_count);
  llvm_cbe_indvars_2e_iv119 = (unsigned int )llvm_cbe_indvars_2e_iv119__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv119 = 0x%X",llvm_cbe_indvars_2e_iv119);
printf("\n = 0x%X",15u);
printf("\nindvars.iv.next120 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next120);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv117 = phi i32 [ %%3, %%.lr.ph67 ], [ %%indvars.iv.next118, %%.critedge9 ], !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv117_count);
  llvm_cbe_indvars_2e_iv117 = (unsigned int )llvm_cbe_indvars_2e_iv117__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv117 = 0x%X",llvm_cbe_indvars_2e_iv117);
printf("\n = 0x%X",llvm_cbe_tmp__1);
printf("\nindvars.iv.next118 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next118);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv115 = phi i32 [ 0, %%.lr.ph67 ], [ %%indvars.iv.next116, %%.critedge9  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv115_count);
  llvm_cbe_indvars_2e_iv115 = (unsigned int )llvm_cbe_indvars_2e_iv115__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nindvars.iv115 = 0x%X",llvm_cbe_indvars_2e_iv115);
printf("\n = 0x%X",0u);
printf("\nindvars.iv.next116 = 0x%X",llvm_cbe_indvars_2e_iv_2e_next116);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%smax123 = select i1 %%13, i32 %%indvars.iv119, i32 %%indvars.iv121, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_smax123_count);
  llvm_cbe_smax123 = (unsigned int )(((((signed int )llvm_cbe_indvars_2e_iv119) > ((signed int )llvm_cbe_indvars_2e_iv121))) ? ((unsigned int )llvm_cbe_indvars_2e_iv119) : ((unsigned int )llvm_cbe_indvars_2e_iv121));
if (AESL_DEBUG_TRACE)
printf("\nsmax123 = 0x%X\n", llvm_cbe_smax123);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = sub i32 %%indvars.iv115, %%smax123, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_87_count);
  llvm_cbe_tmp__7 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv115&4294967295ull)) - ((unsigned int )(llvm_cbe_smax123&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__7&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%umax124 = select i1 %%15, i32 %%indvars.iv117, i32 %%14, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_umax124_count);
  llvm_cbe_umax124 = (unsigned int )(((((unsigned int )llvm_cbe_indvars_2e_iv117&4294967295U) > ((unsigned int )llvm_cbe_tmp__7&4294967295U))) ? ((unsigned int )llvm_cbe_indvars_2e_iv117) : ((unsigned int )llvm_cbe_tmp__7));
if (AESL_DEBUG_TRACE)
printf("\numax124 = 0x%X\n", llvm_cbe_umax124);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = sub i32 %%indvars.iv115, %%umax124, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_89_count);
  llvm_cbe_tmp__8 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv115&4294967295ull)) - ((unsigned int )(llvm_cbe_umax124&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__8&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = sub nsw i32 %%indvars.iv115, %%centerX, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_90_count);
  llvm_cbe_tmp__9 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv115&4294967295ull)) - ((unsigned int )(llvm_cbe_centerX&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__9&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = sitofp i32 %%17 to double, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_91_count);
  llvm_cbe_tmp__10 = (double )((double )(signed int )llvm_cbe_tmp__9);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__10, *(long long*)(&llvm_cbe_tmp__10));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow2 = fmul double %%18, %%18, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_pow2_count);
  llvm_cbe_pow2 = (double )llvm_cbe_tmp__10 * llvm_cbe_tmp__10;
if (AESL_DEBUG_TRACE)
printf("\npow2 = %lf,  0x%llx\n", llvm_cbe_pow2, *(long long*)(&llvm_cbe_pow2));
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = fadd double %%pow2, %%pow213, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_92_count);
  llvm_cbe_tmp__11 = (double )llvm_cbe_pow2 + llvm_cbe_pow213;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__11, *(long long*)(&llvm_cbe_tmp__11));
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = tail call double @sqrt(double %%19) nounwind readnone, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_93_count);
  llvm_cbe_tmp__12 = (double ) /*tail*/ sqrt(llvm_cbe_tmp__11);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__11, *(long long*)(&llvm_cbe_tmp__11));
printf("\nReturn  = %lf",llvm_cbe_tmp__12);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = fptosi double %%20 to i32, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_94_count);
  llvm_cbe_tmp__13 = (unsigned int )((signed int )llvm_cbe_tmp__12&4294967295U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__13);
  if ((((signed int )llvm_cbe_tmp__13) < ((signed int )120u))) {
    goto llvm_cbe__2e_preheader43;
  } else {
    goto llvm_cbe__2e_preheader21;
  }

llvm_cbe__2e_critedge9:
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next116 = add i32 %%indvars.iv115, 15, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next116_count);
  llvm_cbe_indvars_2e_iv_2e_next116 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv115&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next116 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next116&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next118 = add i32 %%indvars.iv117, 15, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next118_count);
  llvm_cbe_indvars_2e_iv_2e_next118 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv117&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next118 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next118&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next120 = add i32 %%indvars.iv119, 15, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next120_count);
  llvm_cbe_indvars_2e_iv_2e_next120 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv119&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next120 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next120&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%indvars.iv.next122 = add i32 %%indvars.iv121, 15, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_indvars_2e_iv_2e_next122_count);
  llvm_cbe_indvars_2e_iv_2e_next122 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv121&4294967295ull)) + ((unsigned int )(15u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nindvars.iv.next122 = 0x%X\n", ((unsigned int )(llvm_cbe_indvars_2e_iv_2e_next122&4294967295ull)));
  if ((((signed int )llvm_cbe_indvars_2e_iv_2e_next116) < ((signed int )llvm_cbe_width))) {
    llvm_cbe_indvars_2e_iv121__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next122;   /* for PHI node */
    llvm_cbe_indvars_2e_iv119__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next120;   /* for PHI node */
    llvm_cbe_indvars_2e_iv117__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next118;   /* for PHI node */
    llvm_cbe_indvars_2e_iv115__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv_2e_next116;   /* for PHI node */
    goto llvm_cbe_tmp__101;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

llvm_cbe__2e_critedge9_2e_loopexit:
  goto llvm_cbe__2e_critedge9;

llvm_cbe__2e_preheader21:
  if ((((signed int )llvm_cbe_indvars_2e_iv159) < ((signed int )llvm_cbe_height))) {
    goto llvm_cbe__2e_preheader_2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e_critedge9_2e_loopexit;
  }

llvm_cbe__2e__2e_critedge9_2e_loopexit_crit_edge:
  goto llvm_cbe__2e_critedge9_2e_loopexit;

llvm_cbe__2e_preheader_2e_lr_2e_ph:
  if ((((signed int )llvm_cbe_indvars_2e_iv115) < ((signed int )llvm_cbe_width))) {
    llvm_cbe_storemerge223_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv159;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  } else {
    goto llvm_cbe__2e__2e_critedge9_2e_loopexit_crit_edge;
  }

  do {     /* Syntactic loop '.lr.ph.us' to make GCC happy */
llvm_cbe__2e_lr_2e_ph_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge223.us = phi i32 [ %%64, %%.critedge12.us ], [ %%indvars.iv159, %%.preheader.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge223_2e_us_count);
  llvm_cbe_storemerge223_2e_us = (unsigned int )llvm_cbe_storemerge223_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge223.us = 0x%X",llvm_cbe_storemerge223_2e_us);
printf("\n = 0x%X",llvm_cbe_tmp__52);
printf("\nindvars.iv159 = 0x%X",llvm_cbe_indvars_2e_iv159);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%88 = mul nsw i32 %%storemerge223.us, %%width, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_222_count);
  llvm_cbe_tmp__75 = (unsigned int )((unsigned int )(llvm_cbe_storemerge223_2e_us&4294967295ull)) * ((unsigned int )(llvm_cbe_width&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__75&4294967295ull)));
  llvm_cbe_storemerge320_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv115;   /* for PHI node */
  goto llvm_cbe_tmp__102;

llvm_cbe__2e_critedge12_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%64 = add nsw i32 %%storemerge223.us, 1, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_174_count);
  llvm_cbe_tmp__52 = (unsigned int )((unsigned int )(llvm_cbe_storemerge223_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__52&4294967295ull)));
  if (((llvm_cbe_tmp__52&4294967295U) == (llvm_cbe_tmp__4&4294967295U))) {
    goto llvm_cbe__2e__2e_critedge9_2e_loopexit_crit_edge;
  } else {
    llvm_cbe_storemerge223_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__52;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__102:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge320.us = phi i32 [ %%indvars.iv115, %%.lr.ph.us ], [ %%87, %%65  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge320_2e_us_count);
  llvm_cbe_storemerge320_2e_us = (unsigned int )llvm_cbe_storemerge320_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge320.us = 0x%X",llvm_cbe_storemerge320_2e_us);
printf("\nindvars.iv115 = 0x%X",llvm_cbe_indvars_2e_iv115);
printf("\n = 0x%X",llvm_cbe_tmp__74);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%66 = add nsw i32 %%storemerge320.us, %%88, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_181_count);
  llvm_cbe_tmp__53 = (unsigned int )((unsigned int )(llvm_cbe_storemerge320_2e_us&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__75&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__53&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%67 = shl nsw i32 %%66, 2, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_182_count);
  llvm_cbe_tmp__54 = (unsigned int )llvm_cbe_tmp__53 << 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__54);
if (AESL_DEBUG_TRACE)
printf("\n  %%68 = sext i32 %%67 to i64, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_192_count);
  llvm_cbe_tmp__55 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__54);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__55);
if (AESL_DEBUG_TRACE)
printf("\n  %%69 = getelementptr inbounds i8* %%imageRGBA, i64 %%68, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_193_count);
  llvm_cbe_tmp__56 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__55))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__55));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%70 = load i8* %%69, align 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_194_count);
  llvm_cbe_tmp__57 = (unsigned char )*llvm_cbe_tmp__56;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__57);
if (AESL_DEBUG_TRACE)
printf("\n  %%71 = getelementptr inbounds i8* %%output, i64 %%68, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_195_count);
  llvm_cbe_tmp__58 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__55))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__55));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%70, i8* %%71, align 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_196_count);
  *llvm_cbe_tmp__58 = llvm_cbe_tmp__57;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__57);
if (AESL_DEBUG_TRACE)
printf("\n  %%72 = or i32 %%67, 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_197_count);
  llvm_cbe_tmp__59 = (unsigned int )llvm_cbe_tmp__54 | 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__59);
if (AESL_DEBUG_TRACE)
printf("\n  %%73 = sext i32 %%72 to i64, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_198_count);
  llvm_cbe_tmp__60 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__59);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__60);
if (AESL_DEBUG_TRACE)
printf("\n  %%74 = getelementptr inbounds i8* %%imageRGBA, i64 %%73, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_199_count);
  llvm_cbe_tmp__61 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__60))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__60));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%75 = load i8* %%74, align 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_200_count);
  llvm_cbe_tmp__62 = (unsigned char )*llvm_cbe_tmp__61;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__62);
if (AESL_DEBUG_TRACE)
printf("\n  %%76 = getelementptr inbounds i8* %%output, i64 %%73, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_201_count);
  llvm_cbe_tmp__63 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__60))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__60));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%75, i8* %%76, align 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_202_count);
  *llvm_cbe_tmp__63 = llvm_cbe_tmp__62;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__62);
if (AESL_DEBUG_TRACE)
printf("\n  %%77 = or i32 %%67, 2, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_203_count);
  llvm_cbe_tmp__64 = (unsigned int )llvm_cbe_tmp__54 | 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__64);
if (AESL_DEBUG_TRACE)
printf("\n  %%78 = sext i32 %%77 to i64, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_204_count);
  llvm_cbe_tmp__65 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__64);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__65);
if (AESL_DEBUG_TRACE)
printf("\n  %%79 = getelementptr inbounds i8* %%imageRGBA, i64 %%78, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_205_count);
  llvm_cbe_tmp__66 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__65))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__65));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%80 = load i8* %%79, align 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_206_count);
  llvm_cbe_tmp__67 = (unsigned char )*llvm_cbe_tmp__66;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__67);
if (AESL_DEBUG_TRACE)
printf("\n  %%81 = getelementptr inbounds i8* %%output, i64 %%78, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_207_count);
  llvm_cbe_tmp__68 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__65))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__65));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%80, i8* %%81, align 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_208_count);
  *llvm_cbe_tmp__68 = llvm_cbe_tmp__67;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__67);
if (AESL_DEBUG_TRACE)
printf("\n  %%82 = or i32 %%67, 3, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_209_count);
  llvm_cbe_tmp__69 = (unsigned int )llvm_cbe_tmp__54 | 3u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__69);
if (AESL_DEBUG_TRACE)
printf("\n  %%83 = sext i32 %%82 to i64, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_210_count);
  llvm_cbe_tmp__70 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__69);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__70);
if (AESL_DEBUG_TRACE)
printf("\n  %%84 = getelementptr inbounds i8* %%imageRGBA, i64 %%83, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_211_count);
  llvm_cbe_tmp__71 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__70))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__70));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%85 = load i8* %%84, align 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_212_count);
  llvm_cbe_tmp__72 = (unsigned char )*llvm_cbe_tmp__71;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__72);
if (AESL_DEBUG_TRACE)
printf("\n  %%86 = getelementptr inbounds i8* %%output, i64 %%83, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_213_count);
  llvm_cbe_tmp__73 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__70))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__70));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%85, i8* %%86, align 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_214_count);
  *llvm_cbe_tmp__73 = llvm_cbe_tmp__72;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__72);
if (AESL_DEBUG_TRACE)
printf("\n  %%87 = add nsw i32 %%storemerge320.us, 1, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_215_count);
  llvm_cbe_tmp__74 = (unsigned int )((unsigned int )(llvm_cbe_storemerge320_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__74&4294967295ull)));
  if (((llvm_cbe_tmp__74&4294967295U) == (llvm_cbe_tmp__8&4294967295U))) {
    goto llvm_cbe__2e_critedge12_2e_us;
  } else {
    llvm_cbe_storemerge320_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__74;   /* for PHI node */
    goto llvm_cbe_tmp__102;
  }

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.lr.ph.us' */
llvm_cbe__2e_critedge9_2e_loopexit28:
  goto llvm_cbe__2e_critedge9;

llvm_cbe__2e_critedge:
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa48 = phi i32 [ 0, %%.preheader43 ], [ %%36, %%.critedge8.us ], [ 0, %%.critedge8  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe__2e_lcssa48_count);
  llvm_cbe__2e_lcssa48 = (unsigned int )llvm_cbe__2e_lcssa48__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa48 = 0x%X",llvm_cbe__2e_lcssa48);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__25);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa47 = phi i32 [ 0, %%.preheader43 ], [ %%42, %%.critedge8.us ], [ 0, %%.critedge8  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe__2e_lcssa47_count);
  llvm_cbe__2e_lcssa47 = (unsigned int )llvm_cbe__2e_lcssa47__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa47 = 0x%X",llvm_cbe__2e_lcssa47);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__31);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa46 = phi i32 [ 0, %%.preheader43 ], [ %%48, %%.critedge8.us ], [ 0, %%.critedge8  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe__2e_lcssa46_count);
  llvm_cbe__2e_lcssa46 = (unsigned int )llvm_cbe__2e_lcssa46__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa46 = 0x%X",llvm_cbe__2e_lcssa46);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__37);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa45 = phi i32 [ 0, %%.preheader43 ], [ %%54, %%.critedge8.us ], [ 0, %%.critedge8  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe__2e_lcssa45_count);
  llvm_cbe__2e_lcssa45 = (unsigned int )llvm_cbe__2e_lcssa45__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa45 = 0x%X",llvm_cbe__2e_lcssa45);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__43);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa44 = phi i32 [ 0, %%.preheader43 ], [ %%62, %%.critedge8.us ], [ 0, %%.critedge8  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe__2e_lcssa44_count);
  llvm_cbe__2e_lcssa44 = (unsigned int )llvm_cbe__2e_lcssa44__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa44 = 0x%X",llvm_cbe__2e_lcssa44);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__51);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%90 = sdiv i32 %%.lcssa48, %%.lcssa44, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_231_count);
  llvm_cbe_tmp__77 = (unsigned int )((signed int )(((signed int )llvm_cbe__2e_lcssa48) / ((signed int )llvm_cbe__2e_lcssa44)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__77));
if (AESL_DEBUG_TRACE)
printf("\n  %%91 = trunc i32 %%90 to i8, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_232_count);
  llvm_cbe_tmp__78 = (unsigned char )((unsigned char )llvm_cbe_tmp__77&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__78);
if (AESL_DEBUG_TRACE)
printf("\n  %%92 = sdiv i32 %%.lcssa47, %%.lcssa44, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_235_count);
  llvm_cbe_tmp__79 = (unsigned int )((signed int )(((signed int )llvm_cbe__2e_lcssa47) / ((signed int )llvm_cbe__2e_lcssa44)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__79));
if (AESL_DEBUG_TRACE)
printf("\n  %%93 = trunc i32 %%92 to i8, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_236_count);
  llvm_cbe_tmp__80 = (unsigned char )((unsigned char )llvm_cbe_tmp__79&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__80);
if (AESL_DEBUG_TRACE)
printf("\n  %%94 = sdiv i32 %%.lcssa46, %%.lcssa44, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_239_count);
  llvm_cbe_tmp__81 = (unsigned int )((signed int )(((signed int )llvm_cbe__2e_lcssa46) / ((signed int )llvm_cbe__2e_lcssa44)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__81));
if (AESL_DEBUG_TRACE)
printf("\n  %%95 = trunc i32 %%94 to i8, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_240_count);
  llvm_cbe_tmp__82 = (unsigned char )((unsigned char )llvm_cbe_tmp__81&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__82);
if (AESL_DEBUG_TRACE)
printf("\n  %%96 = sdiv i32 %%.lcssa45, %%.lcssa44, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_243_count);
  llvm_cbe_tmp__83 = (unsigned int )((signed int )(((signed int )llvm_cbe__2e_lcssa45) / ((signed int )llvm_cbe__2e_lcssa44)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__83));
if (AESL_DEBUG_TRACE)
printf("\n  %%97 = trunc i32 %%96 to i8, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_244_count);
  llvm_cbe_tmp__84 = (unsigned char )((unsigned char )llvm_cbe_tmp__83&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__84);
  if ((((signed int )llvm_cbe_indvars_2e_iv159) < ((signed int )llvm_cbe_height))) {
    goto llvm_cbe__2e_preheader24_2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e_critedge9_2e_loopexit28;
  }

llvm_cbe__2e_preheader43:
  if ((((signed int )llvm_cbe_indvars_2e_iv159) < ((signed int )llvm_cbe_height))) {
    goto llvm_cbe__2e_preheader31_2e_lr_2e_ph;
  } else {
    llvm_cbe__2e_lcssa48__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa47__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa46__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa45__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa44__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_critedge;
  }

  do {     /* Syntactic loop '.lr.ph38.us' to make GCC happy */
llvm_cbe__2e_lr_2e_ph38_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge451.us = phi i32 [ %%24, %%.critedge8.us ], [ %%indvars.iv159, %%.preheader31.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge451_2e_us_count);
  llvm_cbe_storemerge451_2e_us = (unsigned int )llvm_cbe_storemerge451_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge451.us = 0x%X",llvm_cbe_storemerge451_2e_us);
printf("\n = 0x%X",llvm_cbe_tmp__14);
printf("\nindvars.iv159 = 0x%X",llvm_cbe_indvars_2e_iv159);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = phi i32 [ %%36, %%.critedge8.us ], [ 0, %%.preheader31.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_162_count);
  llvm_cbe_tmp__45 = (unsigned int )llvm_cbe_tmp__45__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__45);
printf("\n = 0x%X",llvm_cbe_tmp__25);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%57 = phi i32 [ %%42, %%.critedge8.us ], [ 0, %%.preheader31.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_163_count);
  llvm_cbe_tmp__46 = (unsigned int )llvm_cbe_tmp__46__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__46);
printf("\n = 0x%X",llvm_cbe_tmp__31);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%58 = phi i32 [ %%48, %%.critedge8.us ], [ 0, %%.preheader31.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_164_count);
  llvm_cbe_tmp__47 = (unsigned int )llvm_cbe_tmp__47__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__47);
printf("\n = 0x%X",llvm_cbe_tmp__37);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%59 = phi i32 [ %%54, %%.critedge8.us ], [ 0, %%.preheader31.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_165_count);
  llvm_cbe_tmp__48 = (unsigned int )llvm_cbe_tmp__48__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__48);
printf("\n = 0x%X",llvm_cbe_tmp__43);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%60 = phi i32 [ %%62, %%.critedge8.us ], [ 0, %%.preheader31.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_166_count);
  llvm_cbe_tmp__49 = (unsigned int )llvm_cbe_tmp__49__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__49);
printf("\n = 0x%X",llvm_cbe_tmp__51);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%61 = mul nsw i32 %%storemerge451.us, %%width, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_167_count);
  llvm_cbe_tmp__50 = (unsigned int )((unsigned int )(llvm_cbe_storemerge451_2e_us&4294967295ull)) * ((unsigned int )(llvm_cbe_width&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__50&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = sub i32 %%60, %%umax124, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_168_count);
  llvm_cbe_tmp__51 = (unsigned int )((unsigned int )(llvm_cbe_tmp__49&4294967295ull)) - ((unsigned int )(llvm_cbe_umax124&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__51&4294967295ull)));
  llvm_cbe_storemerge737_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv115;   /* for PHI node */
  llvm_cbe_tmp__15__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__45;   /* for PHI node */
  llvm_cbe_tmp__16__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__46;   /* for PHI node */
  llvm_cbe_tmp__17__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__47;   /* for PHI node */
  llvm_cbe_tmp__18__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__48;   /* for PHI node */
  goto llvm_cbe_tmp__103;

llvm_cbe__2e_critedge8_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = add nsw i32 %%storemerge451.us, 1, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_102_count);
  llvm_cbe_tmp__14 = (unsigned int )((unsigned int )(llvm_cbe_storemerge451_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__14&4294967295ull)));
  if (((llvm_cbe_tmp__14&4294967295U) == (llvm_cbe_tmp__4&4294967295U))) {
    llvm_cbe__2e_lcssa48__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__25;   /* for PHI node */
    llvm_cbe__2e_lcssa47__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__31;   /* for PHI node */
    llvm_cbe__2e_lcssa46__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__37;   /* for PHI node */
    llvm_cbe__2e_lcssa45__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__43;   /* for PHI node */
    llvm_cbe__2e_lcssa44__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__51;   /* for PHI node */
    goto llvm_cbe__2e_critedge;
  } else {
    llvm_cbe_storemerge451_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__14;   /* for PHI node */
    llvm_cbe_tmp__45__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__25;   /* for PHI node */
    llvm_cbe_tmp__46__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__31;   /* for PHI node */
    llvm_cbe_tmp__47__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__37;   /* for PHI node */
    llvm_cbe_tmp__48__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__43;   /* for PHI node */
    llvm_cbe_tmp__49__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__51;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph38_2e_us;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__103:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge737.us = phi i32 [ %%indvars.iv115, %%.lr.ph38.us ], [ %%55, %%25  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge737_2e_us_count);
  llvm_cbe_storemerge737_2e_us = (unsigned int )llvm_cbe_storemerge737_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge737.us = 0x%X",llvm_cbe_storemerge737_2e_us);
printf("\nindvars.iv115 = 0x%X",llvm_cbe_indvars_2e_iv115);
printf("\n = 0x%X",llvm_cbe_tmp__44);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = phi i32 [ %%56, %%.lr.ph38.us ], [ %%36, %%25  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_109_count);
  llvm_cbe_tmp__15 = (unsigned int )llvm_cbe_tmp__15__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__15);
printf("\n = 0x%X",llvm_cbe_tmp__45);
printf("\n = 0x%X",llvm_cbe_tmp__25);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = phi i32 [ %%57, %%.lr.ph38.us ], [ %%42, %%25  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_110_count);
  llvm_cbe_tmp__16 = (unsigned int )llvm_cbe_tmp__16__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__16);
printf("\n = 0x%X",llvm_cbe_tmp__46);
printf("\n = 0x%X",llvm_cbe_tmp__31);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = phi i32 [ %%58, %%.lr.ph38.us ], [ %%48, %%25  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_111_count);
  llvm_cbe_tmp__17 = (unsigned int )llvm_cbe_tmp__17__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__17);
printf("\n = 0x%X",llvm_cbe_tmp__47);
printf("\n = 0x%X",llvm_cbe_tmp__37);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = phi i32 [ %%59, %%.lr.ph38.us ], [ %%54, %%25  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_112_count);
  llvm_cbe_tmp__18 = (unsigned int )llvm_cbe_tmp__18__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__18);
printf("\n = 0x%X",llvm_cbe_tmp__48);
printf("\n = 0x%X",llvm_cbe_tmp__43);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = add nsw i32 %%storemerge737.us, %%61, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_113_count);
  llvm_cbe_tmp__19 = (unsigned int )((unsigned int )(llvm_cbe_storemerge737_2e_us&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__50&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__19&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = shl nsw i32 %%30, 2, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_114_count);
  llvm_cbe_tmp__20 = (unsigned int )llvm_cbe_tmp__19 << 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = sext i32 %%31 to i64, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_120_count);
  llvm_cbe_tmp__21 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__21);
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = getelementptr inbounds i8* %%imageRGBA, i64 %%32, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_121_count);
  llvm_cbe_tmp__22 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__21))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__21));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = load i8* %%33, align 1, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_122_count);
  llvm_cbe_tmp__23 = (unsigned char )*llvm_cbe_tmp__22;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__23);
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = zext i8 %%34 to i32, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_123_count);
  llvm_cbe_tmp__24 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__23&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__24);
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = add nsw i32 %%35, %%26, !dbg !2 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_124_count);
  llvm_cbe_tmp__25 = (unsigned int )((unsigned int )(llvm_cbe_tmp__24&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__15&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__25&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = or i32 %%31, 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_128_count);
  llvm_cbe_tmp__26 = (unsigned int )llvm_cbe_tmp__20 | 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__26);
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = sext i32 %%37 to i64, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_129_count);
  llvm_cbe_tmp__27 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__26);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__27);
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = getelementptr inbounds i8* %%imageRGBA, i64 %%38, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_130_count);
  llvm_cbe_tmp__28 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__27))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__27));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = load i8* %%39, align 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_131_count);
  llvm_cbe_tmp__29 = (unsigned char )*llvm_cbe_tmp__28;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__29);
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = zext i8 %%40 to i32, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_132_count);
  llvm_cbe_tmp__30 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__29&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__30);
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = add nsw i32 %%41, %%27, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_133_count);
  llvm_cbe_tmp__31 = (unsigned int )((unsigned int )(llvm_cbe_tmp__30&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__16&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__31&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = or i32 %%31, 2, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_137_count);
  llvm_cbe_tmp__32 = (unsigned int )llvm_cbe_tmp__20 | 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__32);
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = sext i32 %%43 to i64, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_138_count);
  llvm_cbe_tmp__33 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__32);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__33);
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = getelementptr inbounds i8* %%imageRGBA, i64 %%44, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_139_count);
  llvm_cbe_tmp__34 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__33))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__33));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = load i8* %%45, align 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_140_count);
  llvm_cbe_tmp__35 = (unsigned char )*llvm_cbe_tmp__34;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__35);
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = zext i8 %%46 to i32, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_141_count);
  llvm_cbe_tmp__36 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__35&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE)
printf("\n  %%48 = add nsw i32 %%47, %%28, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_142_count);
  llvm_cbe_tmp__37 = (unsigned int )((unsigned int )(llvm_cbe_tmp__36&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__17&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__37&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%49 = or i32 %%31, 3, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_146_count);
  llvm_cbe_tmp__38 = (unsigned int )llvm_cbe_tmp__20 | 3u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__38);
if (AESL_DEBUG_TRACE)
printf("\n  %%50 = sext i32 %%49 to i64, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_147_count);
  llvm_cbe_tmp__39 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__38);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__39);
if (AESL_DEBUG_TRACE)
printf("\n  %%51 = getelementptr inbounds i8* %%imageRGBA, i64 %%50, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_148_count);
  llvm_cbe_tmp__40 = ( char *)(&llvm_cbe_imageRGBA[(((signed long long )llvm_cbe_tmp__39))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__39));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%52 = load i8* %%51, align 1, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_149_count);
  llvm_cbe_tmp__41 = (unsigned char )*llvm_cbe_tmp__40;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__41);
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = zext i8 %%52 to i32, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_150_count);
  llvm_cbe_tmp__42 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__41&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__42);
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = add nsw i32 %%53, %%29, !dbg !3 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_151_count);
  llvm_cbe_tmp__43 = (unsigned int )((unsigned int )(llvm_cbe_tmp__42&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__18&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__43&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = add nsw i32 %%storemerge737.us, 1, !dbg !10 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_155_count);
  llvm_cbe_tmp__44 = (unsigned int )((unsigned int )(llvm_cbe_storemerge737_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__44&4294967295ull)));
  if (((llvm_cbe_tmp__44&4294967295U) == (llvm_cbe_tmp__8&4294967295U))) {
    goto llvm_cbe__2e_critedge8_2e_us;
  } else {
    llvm_cbe_storemerge737_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__44;   /* for PHI node */
    llvm_cbe_tmp__15__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__25;   /* for PHI node */
    llvm_cbe_tmp__16__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__31;   /* for PHI node */
    llvm_cbe_tmp__17__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__37;   /* for PHI node */
    llvm_cbe_tmp__18__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__43;   /* for PHI node */
    goto llvm_cbe_tmp__103;
  }

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.lr.ph38.us' */
llvm_cbe__2e_preheader31_2e_lr_2e_ph:
  if ((((signed int )llvm_cbe_indvars_2e_iv115) < ((signed int )llvm_cbe_width))) {
    llvm_cbe_storemerge451_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv159;   /* for PHI node */
    llvm_cbe_tmp__45__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe_tmp__46__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe_tmp__47__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe_tmp__48__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe_tmp__49__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph38_2e_us;
  } else {
    llvm_cbe_storemerge451__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv159;   /* for PHI node */
    goto llvm_cbe__2e_critedge8;
  }

  do {     /* Syntactic loop '.critedge8' to make GCC happy */
llvm_cbe__2e_critedge8:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge451 = phi i32 [ %%89, %%.critedge8 ], [ %%indvars.iv159, %%.preheader31.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge451_count);
  llvm_cbe_storemerge451 = (unsigned int )llvm_cbe_storemerge451__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge451 = 0x%X",llvm_cbe_storemerge451);
printf("\n = 0x%X",llvm_cbe_tmp__76);
printf("\nindvars.iv159 = 0x%X",llvm_cbe_indvars_2e_iv159);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%89 = add nsw i32 %%storemerge451, 1, !dbg !9 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_224_count);
  llvm_cbe_tmp__76 = (unsigned int )((unsigned int )(llvm_cbe_storemerge451&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__76&4294967295ull)));
  if (((llvm_cbe_tmp__76&4294967295U) == (llvm_cbe_tmp__4&4294967295U))) {
    llvm_cbe__2e_lcssa48__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa47__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa46__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa45__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa44__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_critedge;
  } else {
    llvm_cbe_storemerge451__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__76;   /* for PHI node */
    goto llvm_cbe__2e_critedge8;
  }

  } while (1); /* end of syntactic loop '.critedge8' */
llvm_cbe__2e__2e_critedge9_2e_loopexit28_crit_edge:
  goto llvm_cbe__2e_critedge9_2e_loopexit28;

llvm_cbe__2e_preheader24_2e_lr_2e_ph:
  if ((((signed int )llvm_cbe_indvars_2e_iv115) < ((signed int )llvm_cbe_width))) {
    llvm_cbe_storemerge530_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv159;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph27_2e_us;
  } else {
    goto llvm_cbe__2e__2e_critedge9_2e_loopexit28_crit_edge;
  }

  do {     /* Syntactic loop '.lr.ph27.us' to make GCC happy */
llvm_cbe__2e_lr_2e_ph27_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge530.us = phi i32 [ %%99, %%.critedge10.us ], [ %%indvars.iv159, %%.preheader24.lr.ph  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge530_2e_us_count);
  llvm_cbe_storemerge530_2e_us = (unsigned int )llvm_cbe_storemerge530_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge530.us = 0x%X",llvm_cbe_storemerge530_2e_us);
printf("\n = 0x%X",llvm_cbe_tmp__85);
printf("\nindvars.iv159 = 0x%X",llvm_cbe_indvars_2e_iv159);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%115 = mul nsw i32 %%storemerge530.us, %%width, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_286_count);
  llvm_cbe_tmp__100 = (unsigned int )((unsigned int )(llvm_cbe_storemerge530_2e_us&4294967295ull)) * ((unsigned int )(llvm_cbe_width&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__100&4294967295ull)));
  llvm_cbe_storemerge626_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_indvars_2e_iv115;   /* for PHI node */
  goto llvm_cbe_tmp__104;

llvm_cbe__2e_critedge10_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%99 = add nsw i32 %%storemerge530.us, 1, !dbg !11 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_250_count);
  llvm_cbe_tmp__85 = (unsigned int )((unsigned int )(llvm_cbe_storemerge530_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__85&4294967295ull)));
  if (((llvm_cbe_tmp__85&4294967295U) == (llvm_cbe_tmp__4&4294967295U))) {
    goto llvm_cbe__2e__2e_critedge9_2e_loopexit28_crit_edge;
  } else {
    llvm_cbe_storemerge530_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__85;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph27_2e_us;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__104:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge626.us = phi i32 [ %%indvars.iv115, %%.lr.ph27.us ], [ %%114, %%100  for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_storemerge626_2e_us_count);
  llvm_cbe_storemerge626_2e_us = (unsigned int )llvm_cbe_storemerge626_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge626.us = 0x%X",llvm_cbe_storemerge626_2e_us);
printf("\nindvars.iv115 = 0x%X",llvm_cbe_indvars_2e_iv115);
printf("\n = 0x%X",llvm_cbe_tmp__99);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%101 = add nsw i32 %%storemerge626.us, %%115, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_257_count);
  llvm_cbe_tmp__86 = (unsigned int )((unsigned int )(llvm_cbe_storemerge626_2e_us&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__100&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__86&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%102 = shl nsw i32 %%101, 2, !dbg !6 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_258_count);
  llvm_cbe_tmp__87 = (unsigned int )llvm_cbe_tmp__86 << 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__87);
if (AESL_DEBUG_TRACE)
printf("\n  %%103 = sext i32 %%102 to i64, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_264_count);
  llvm_cbe_tmp__88 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__87);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__88);
if (AESL_DEBUG_TRACE)
printf("\n  %%104 = getelementptr inbounds i8* %%output, i64 %%103, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_265_count);
  llvm_cbe_tmp__89 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__88))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__88));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%91, i8* %%104, align 1, !dbg !4 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_266_count);
  *llvm_cbe_tmp__89 = llvm_cbe_tmp__78;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__78);
if (AESL_DEBUG_TRACE)
printf("\n  %%105 = or i32 %%102, 1, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_267_count);
  llvm_cbe_tmp__90 = (unsigned int )llvm_cbe_tmp__87 | 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__90);
if (AESL_DEBUG_TRACE)
printf("\n  %%106 = sext i32 %%105 to i64, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_268_count);
  llvm_cbe_tmp__91 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__90);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__91);
if (AESL_DEBUG_TRACE)
printf("\n  %%107 = getelementptr inbounds i8* %%output, i64 %%106, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_269_count);
  llvm_cbe_tmp__92 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__91))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__91));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%93, i8* %%107, align 1, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_270_count);
  *llvm_cbe_tmp__92 = llvm_cbe_tmp__80;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__80);
if (AESL_DEBUG_TRACE)
printf("\n  %%108 = or i32 %%102, 2, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_271_count);
  llvm_cbe_tmp__93 = (unsigned int )llvm_cbe_tmp__87 | 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__93);
if (AESL_DEBUG_TRACE)
printf("\n  %%109 = sext i32 %%108 to i64, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_272_count);
  llvm_cbe_tmp__94 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__93);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__94);
if (AESL_DEBUG_TRACE)
printf("\n  %%110 = getelementptr inbounds i8* %%output, i64 %%109, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_273_count);
  llvm_cbe_tmp__95 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__94))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__94));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%95, i8* %%110, align 1, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_274_count);
  *llvm_cbe_tmp__95 = llvm_cbe_tmp__82;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__82);
if (AESL_DEBUG_TRACE)
printf("\n  %%111 = or i32 %%102, 3, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_275_count);
  llvm_cbe_tmp__96 = (unsigned int )llvm_cbe_tmp__87 | 3u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__96);
if (AESL_DEBUG_TRACE)
printf("\n  %%112 = sext i32 %%111 to i64, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_276_count);
  llvm_cbe_tmp__97 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__96);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__97);
if (AESL_DEBUG_TRACE)
printf("\n  %%113 = getelementptr inbounds i8* %%output, i64 %%112, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_277_count);
  llvm_cbe_tmp__98 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__97))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__97));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%97, i8* %%113, align 1, !dbg !5 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_278_count);
  *llvm_cbe_tmp__98 = llvm_cbe_tmp__84;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__84);
if (AESL_DEBUG_TRACE)
printf("\n  %%114 = add nsw i32 %%storemerge626.us, 1, !dbg !11 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_279_count);
  llvm_cbe_tmp__99 = (unsigned int )((unsigned int )(llvm_cbe_storemerge626_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__99&4294967295ull)));
  if (((llvm_cbe_tmp__99&4294967295U) == (llvm_cbe_tmp__8&4294967295U))) {
    goto llvm_cbe__2e_critedge10_2e_us;
  } else {
    llvm_cbe_storemerge626_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__99;   /* for PHI node */
    goto llvm_cbe_tmp__104;
  }

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.lr.ph27.us' */
  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e_lr_2e_ph67:
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = sub nsw i32 %%indvars.iv159, %%centerY, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_82_count);
  llvm_cbe_tmp__5 = (unsigned int )((unsigned int )(llvm_cbe_indvars_2e_iv159&4294967295ull)) - ((unsigned int )(llvm_cbe_centerY&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__5&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = sitofp i32 %%9 to double, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_83_count);
  llvm_cbe_tmp__6 = (double )((double )(signed int )llvm_cbe_tmp__5);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__6, *(long long*)(&llvm_cbe_tmp__6));
if (AESL_DEBUG_TRACE)
printf("\n  %%pow213 = fmul double %%10, %%10, !dbg !7 for 0x%I64xth hint within @ImageTransform  --> \n", ++aesl_llvm_cbe_pow213_count);
  llvm_cbe_pow213 = (double )llvm_cbe_tmp__6 * llvm_cbe_tmp__6;
if (AESL_DEBUG_TRACE)
printf("\npow213 = %lf,  0x%llx\n", llvm_cbe_pow213, *(long long*)(&llvm_cbe_pow213));
  llvm_cbe_indvars_2e_iv121__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv119__PHI_TEMPORARY = (unsigned int )15u;   /* for PHI node */
  llvm_cbe_indvars_2e_iv117__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__1;   /* for PHI node */
  llvm_cbe_indvars_2e_iv115__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__101;

  } while (1); /* end of syntactic loop '.preheader58' */
llvm_cbe__2e__crit_edge70:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @ImageTransform}\n");
  return;
}

