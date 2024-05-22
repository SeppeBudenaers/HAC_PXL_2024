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
void applyConvolution( char *llvm_cbe_image,  char *llvm_cbe_output, signed int llvm_cbe_width, signed int llvm_cbe_height, signed int llvm_cbe_channels);


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

void applyConvolution( char *llvm_cbe_image,  char *llvm_cbe_output, signed int llvm_cbe_width, signed int llvm_cbe_height, signed int llvm_cbe_channels) {
  static  unsigned long long aesl_llvm_cbe_kernel_count = 0;
  float llvm_cbe_kernel[3][3];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_sum_count = 0;
  float llvm_cbe_sum[3];    /* Address-exposed local */
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
   char *llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
   char *llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  float *llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  float *llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  float *llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  float *llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  float *llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  float *llvm_cbe_tmp__8;
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
   char *llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge25_count = 0;
  unsigned int llvm_cbe_storemerge25;
  unsigned int llvm_cbe_storemerge25__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  unsigned int llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge122_count = 0;
  unsigned int llvm_cbe_storemerge122;
  unsigned int llvm_cbe_storemerge122__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
   char *llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge220_count = 0;
  unsigned int llvm_cbe_storemerge220;
  unsigned int llvm_cbe_storemerge220__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  unsigned int llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  unsigned int llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  unsigned long long llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  unsigned int llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  unsigned int llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_or_2e_cond_2e_us_count = 0;
  bool llvm_cbe_or_2e_cond_2e_us;
  static  unsigned long long aesl_llvm_cbe_or_2e_cond7_2e_us_count = 0;
  bool llvm_cbe_or_2e_cond7_2e_us;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_or_2e_cond_2e_us_2e_1_count = 0;
  bool llvm_cbe_or_2e_cond_2e_us_2e_1;
  static  unsigned long long aesl_llvm_cbe_or_2e_cond7_2e_us_2e_1_count = 0;
  bool llvm_cbe_or_2e_cond7_2e_us_2e_1;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  unsigned int llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond28_count = 0;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  unsigned int llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  unsigned long long llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
   char *llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  unsigned char llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  unsigned int llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  float llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  float llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  unsigned long long llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  float *llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  float llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  float llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge510_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge510_2e_us;
  unsigned int llvm_cbe_storemerge510_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  float *llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  float llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  unsigned int llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  unsigned int llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  unsigned int llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  unsigned int llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond31_count = 0;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge38_count = 0;
  unsigned int llvm_cbe_storemerge38;
  unsigned int llvm_cbe_storemerge38__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  unsigned long long llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  float *llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  float llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  unsigned int llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  unsigned char llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_phitmp_count = 0;
  unsigned char llvm_cbe_phitmp;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  unsigned char llvm_cbe_tmp__40;
  unsigned char llvm_cbe_tmp__40__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  unsigned int llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  unsigned long long llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
   char *llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  unsigned int llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  unsigned long long llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
   char *llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  unsigned char llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
   char *llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  unsigned int llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  unsigned int llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond32_count = 0;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  unsigned int llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond33_count = 0;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  float *llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  float llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  unsigned int llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  unsigned int llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge510_2e_us_2e_1_count = 0;
  unsigned int llvm_cbe_storemerge510_2e_us_2e_1;
  unsigned int llvm_cbe_storemerge510_2e_us_2e_1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  unsigned int llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  unsigned long long llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
   char *llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
  unsigned char llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
  unsigned int llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_234_count = 0;
  float llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_235_count = 0;
  float llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_236_count = 0;
  unsigned long long llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_237_count = 0;
  float *llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_238_count = 0;
  float llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_239_count = 0;
  float llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_240_count = 0;
  static  unsigned long long aesl_llvm_cbe_241_count = 0;
  static  unsigned long long aesl_llvm_cbe_242_count = 0;
  unsigned int llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_243_count = 0;
  static  unsigned long long aesl_llvm_cbe_244_count = 0;
  static  unsigned long long aesl_llvm_cbe_245_count = 0;
  static  unsigned long long aesl_llvm_cbe_246_count = 0;
  static  unsigned long long aesl_llvm_cbe_247_count = 0;
  static  unsigned long long aesl_llvm_cbe_248_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond28_2e_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_249_count = 0;
  static  unsigned long long aesl_llvm_cbe_250_count = 0;
  static  unsigned long long aesl_llvm_cbe_251_count = 0;
  static  unsigned long long aesl_llvm_cbe_252_count = 0;
  static  unsigned long long aesl_llvm_cbe_253_count = 0;
  static  unsigned long long aesl_llvm_cbe_254_count = 0;
  static  unsigned long long aesl_llvm_cbe_255_count = 0;
  static  unsigned long long aesl_llvm_cbe_256_count = 0;
  unsigned int llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_257_count = 0;
  static  unsigned long long aesl_llvm_cbe_258_count = 0;
  static  unsigned long long aesl_llvm_cbe_259_count = 0;
  static  unsigned long long aesl_llvm_cbe_260_count = 0;
  static  unsigned long long aesl_llvm_cbe_261_count = 0;
  static  unsigned long long aesl_llvm_cbe_262_count = 0;
  static  unsigned long long aesl_llvm_cbe_or_2e_cond_2e_us_2e_2_count = 0;
  bool llvm_cbe_or_2e_cond_2e_us_2e_2;
  static  unsigned long long aesl_llvm_cbe_or_2e_cond7_2e_us_2e_2_count = 0;
  bool llvm_cbe_or_2e_cond7_2e_us_2e_2;
  static  unsigned long long aesl_llvm_cbe_263_count = 0;
  static  unsigned long long aesl_llvm_cbe_264_count = 0;
  static  unsigned long long aesl_llvm_cbe_265_count = 0;
  static  unsigned long long aesl_llvm_cbe_266_count = 0;
  static  unsigned long long aesl_llvm_cbe_267_count = 0;
  static  unsigned long long aesl_llvm_cbe_268_count = 0;
  static  unsigned long long aesl_llvm_cbe_269_count = 0;
  static  unsigned long long aesl_llvm_cbe_270_count = 0;
  float *llvm_cbe_tmp__69;
  static  unsigned long long aesl_llvm_cbe_271_count = 0;
  float llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_272_count = 0;
  unsigned int llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_273_count = 0;
  unsigned int llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_274_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge510_2e_us_2e_2_count = 0;
  unsigned int llvm_cbe_storemerge510_2e_us_2e_2;
  unsigned int llvm_cbe_storemerge510_2e_us_2e_2__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_275_count = 0;
  static  unsigned long long aesl_llvm_cbe_276_count = 0;
  static  unsigned long long aesl_llvm_cbe_277_count = 0;
  unsigned int llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_278_count = 0;
  unsigned long long llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_279_count = 0;
   char *llvm_cbe_tmp__75;
  static  unsigned long long aesl_llvm_cbe_280_count = 0;
  unsigned char llvm_cbe_tmp__76;
  static  unsigned long long aesl_llvm_cbe_281_count = 0;
  unsigned int llvm_cbe_tmp__77;
  static  unsigned long long aesl_llvm_cbe_282_count = 0;
  float llvm_cbe_tmp__78;
  static  unsigned long long aesl_llvm_cbe_283_count = 0;
  float llvm_cbe_tmp__79;
  static  unsigned long long aesl_llvm_cbe_284_count = 0;
  unsigned long long llvm_cbe_tmp__80;
  static  unsigned long long aesl_llvm_cbe_285_count = 0;
  float *llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_286_count = 0;
  float llvm_cbe_tmp__82;
  static  unsigned long long aesl_llvm_cbe_287_count = 0;
  float llvm_cbe_tmp__83;
  static  unsigned long long aesl_llvm_cbe_288_count = 0;
  static  unsigned long long aesl_llvm_cbe_289_count = 0;
  static  unsigned long long aesl_llvm_cbe_290_count = 0;
  unsigned int llvm_cbe_tmp__84;
  static  unsigned long long aesl_llvm_cbe_291_count = 0;
  static  unsigned long long aesl_llvm_cbe_292_count = 0;
  static  unsigned long long aesl_llvm_cbe_293_count = 0;
  static  unsigned long long aesl_llvm_cbe_294_count = 0;
  static  unsigned long long aesl_llvm_cbe_295_count = 0;
  static  unsigned long long aesl_llvm_cbe_296_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond28_2e_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_297_count = 0;
  static  unsigned long long aesl_llvm_cbe_298_count = 0;
  static  unsigned long long aesl_llvm_cbe_299_count = 0;
  static  unsigned long long aesl_llvm_cbe_300_count = 0;
  static  unsigned long long aesl_llvm_cbe_301_count = 0;
  static  unsigned long long aesl_llvm_cbe_302_count = 0;
  static  unsigned long long aesl_llvm_cbe_303_count = 0;
  static  unsigned long long aesl_llvm_cbe_304_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @applyConvolution\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = bitcast [3 x [3 x float]]* %%kernel to i8*, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_25_count);
  llvm_cbe_tmp__1 = ( char *)(( char *)(&llvm_cbe_kernel));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = call i8* @memset(i8* %%1, i32 0, i64 36 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_26_count);
  ( char *)memset(( char *)llvm_cbe_tmp__1, 0u, 36ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%I64X",36ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__2);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 0, i64 0, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_27_count);
  llvm_cbe_tmp__3 = (float *)(&llvm_cbe_kernel[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
}

#ifdef AESL_BC_SIM
  assert(((signed long long )0ull) < 3 && "Write access out of array 'kernel' bound?");
  assert(((signed long long )0ull) < 3 && "Write access out of array 'kernel' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store float 1.000000e+00, float* %%3, align 16, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_28_count);
  *llvm_cbe_tmp__3 = 0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 0, i64 2, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_29_count);
  llvm_cbe_tmp__4 = (float *)(&llvm_cbe_kernel[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
][(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
}

#ifdef AESL_BC_SIM
  assert(((signed long long )0ull) < 3 && "Write access out of array 'kernel' bound?");
  assert(((signed long long )2ull) < 3 && "Write access out of array 'kernel' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store float -1.000000e+00, float* %%4, align 8, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_30_count);
  *llvm_cbe_tmp__4 = -0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", -0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 1, i64 0, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_31_count);
  llvm_cbe_tmp__5 = (float *)(&llvm_cbe_kernel[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 3
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
}

#ifdef AESL_BC_SIM
  assert(((signed long long )1ull) < 3 && "Write access out of array 'kernel' bound?");
  assert(((signed long long )0ull) < 3 && "Write access out of array 'kernel' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store float 1.000000e+00, float* %%5, align 4, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_32_count);
  *llvm_cbe_tmp__5 = 0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 1, i64 2, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_33_count);
  llvm_cbe_tmp__6 = (float *)(&llvm_cbe_kernel[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 3
#endif
][(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
}

#ifdef AESL_BC_SIM
  assert(((signed long long )1ull) < 3 && "Write access out of array 'kernel' bound?");
  assert(((signed long long )2ull) < 3 && "Write access out of array 'kernel' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store float -1.000000e+00, float* %%6, align 4, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_34_count);
  *llvm_cbe_tmp__6 = -0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", -0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 2, i64 0, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_35_count);
  llvm_cbe_tmp__7 = (float *)(&llvm_cbe_kernel[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 3
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
}

#ifdef AESL_BC_SIM
  assert(((signed long long )2ull) < 3 && "Write access out of array 'kernel' bound?");
  assert(((signed long long )0ull) < 3 && "Write access out of array 'kernel' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store float 1.000000e+00, float* %%7, align 8, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_36_count);
  *llvm_cbe_tmp__7 = 0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 2, i64 2, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_37_count);
  llvm_cbe_tmp__8 = (float *)(&llvm_cbe_kernel[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 3
#endif
][(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
}

#ifdef AESL_BC_SIM
  assert(((signed long long )2ull) < 3 && "Write access out of array 'kernel' bound?");
  assert(((signed long long )2ull) < 3 && "Write access out of array 'kernel' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store float -1.000000e+00, float* %%8, align 8, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_38_count);
  *llvm_cbe_tmp__8 = -0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", -0x1p0);
  if ((((signed int )llvm_cbe_height) > ((signed int )0u))) {
    goto llvm_cbe__2e_preheader21_2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge26;
  }

llvm_cbe__2e_preheader21_2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = bitcast [3 x float]* %%sum to i8*, !dbg !7 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_56_count);
  llvm_cbe_tmp__9 = ( char *)(( char *)(&llvm_cbe_sum));
  llvm_cbe_storemerge25__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader21;

  do {     /* Syntactic loop '.preheader21' to make GCC happy */
llvm_cbe__2e_preheader21:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge25 = phi i32 [ 0, %%.preheader21.lr.ph ], [ %%75, %%._crit_edge24  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_storemerge25_count);
  llvm_cbe_storemerge25 = (unsigned int )llvm_cbe_storemerge25__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge25 = 0x%X",llvm_cbe_storemerge25);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__51);
}
  if ((((signed int )llvm_cbe_width) > ((signed int )0u))) {
    goto llvm_cbe__2e_lr_2e_ph23;
  } else {
    goto llvm_cbe__2e__crit_edge24;
  }

llvm_cbe__2e__crit_edge24:
if (AESL_DEBUG_TRACE)
printf("\n  %%75 = add nsw i32 %%storemerge25, 1, !dbg !7 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_206_count);
  llvm_cbe_tmp__51 = (unsigned int )((unsigned int )(llvm_cbe_storemerge25&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__51&4294967295ull)));
  if (((llvm_cbe_tmp__51&4294967295U) == (llvm_cbe_height&4294967295U))) {
    goto llvm_cbe__2e__crit_edge26;
  } else {
    llvm_cbe_storemerge25__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__51;   /* for PHI node */
    goto llvm_cbe__2e_preheader21;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__85:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge122 = phi i32 [ 0, %%.lr.ph23 ], [ %%74, %%._crit_edge  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_storemerge122_count);
  llvm_cbe_storemerge122 = (unsigned int )llvm_cbe_storemerge122__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge122 = 0x%X",llvm_cbe_storemerge122);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__50);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = call i8* @memset(i8* %%11, i32 0, i64 12 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_69_count);
  ( char *)memset(( char *)llvm_cbe_tmp__9, 0u, 12ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%I64X",12ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__11);
}
  llvm_cbe_storemerge220__PHI_TEMPORARY = (unsigned int )4294967295u;   /* for PHI node */
  goto llvm_cbe__2e_preheader12;

llvm_cbe__2e__crit_edge:
if (AESL_DEBUG_TRACE)
printf("\n  %%74 = add nsw i32 %%storemerge122, 1, !dbg !7 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_197_count);
  llvm_cbe_tmp__50 = (unsigned int )((unsigned int )(llvm_cbe_storemerge122&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__50&4294967295ull)));
  if (((llvm_cbe_tmp__50&4294967295U) == (llvm_cbe_width&4294967295U))) {
    goto llvm_cbe__2e__crit_edge24;
  } else {
    llvm_cbe_storemerge122__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__50;   /* for PHI node */
    goto llvm_cbe_tmp__85;
  }

llvm_cbe__2e_preheader:
  if ((((signed int )llvm_cbe_channels) > ((signed int )0u))) {
    goto llvm_cbe__2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

  do {     /* Syntactic loop '.preheader12' to make GCC happy */
llvm_cbe__2e_preheader12:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge220 = phi i32 [ -1, %%14 ], [ %%19, %%.us-lcssa  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_storemerge220_count);
  llvm_cbe_storemerge220 = (unsigned int )llvm_cbe_storemerge220__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge220 = 0x%X",llvm_cbe_storemerge220);
printf("\n = 0x%X",4294967295u);
printf("\n = 0x%X",llvm_cbe_tmp__13);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = add nsw i32 %%storemerge220, %%storemerge25, !dbg !7 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_80_count);
  llvm_cbe_tmp__12 = (unsigned int )((unsigned int )(llvm_cbe_storemerge220&4294967295ull)) + ((unsigned int )(llvm_cbe_storemerge25&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__12&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = add nsw i32 %%storemerge220, 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_83_count);
  llvm_cbe_tmp__13 = (unsigned int )((unsigned int )(llvm_cbe_storemerge220&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__13&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = sext i32 %%19 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_84_count);
  llvm_cbe_tmp__14 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__14);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = mul nsw i32 %%16, %%width, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_85_count);
  llvm_cbe_tmp__15 = (unsigned int )((unsigned int )(llvm_cbe_tmp__12&4294967295ull)) * ((unsigned int )(llvm_cbe_width&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__15&4294967295ull)));
  if ((((signed int )llvm_cbe_tmp__12) > ((signed int )4294967295u))) {
    goto llvm_cbe__2e_preheader12_2e_split_2e_us;
  } else {
    goto llvm_cbe__2e_us_2d_lcssa;
  }

llvm_cbe__2e_us_2d_lcssa:
  if (((llvm_cbe_tmp__13&4294967295U) == (2u&4294967295U))) {
    goto llvm_cbe__2e_preheader;
  } else {
    llvm_cbe_storemerge220__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__13;   /* for PHI node */
    goto llvm_cbe__2e_preheader12;
  }

llvm_cbe__2e_us_2d_lcssa_2e_us:
  goto llvm_cbe__2e_us_2d_lcssa;

llvm_cbe_tmp__86:
if (AESL_DEBUG_TRACE)
printf("\n  %%97 = add nsw i32 %%storemerge122, 1, !dbg !7 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_256_count);
  llvm_cbe_tmp__68 = (unsigned int )((unsigned int )(llvm_cbe_storemerge122&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__68&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%or.cond.us.2 = and i1 %%98, %%99, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_or_2e_cond_2e_us_2e_2_count);
  llvm_cbe_or_2e_cond_2e_us_2e_2 = (bool )(((((signed int )llvm_cbe_tmp__68) > ((signed int )4294967295u)) & (((signed int )llvm_cbe_tmp__68) < ((signed int )llvm_cbe_width)))&1);
if (AESL_DEBUG_TRACE)
printf("\nor.cond.us.2 = 0x%X\n", llvm_cbe_or_2e_cond_2e_us_2e_2);
if (AESL_DEBUG_TRACE)
printf("\n  %%or.cond7.us.2 = and i1 %%or.cond.us.2, %%18, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_or_2e_cond7_2e_us_2e_2_count);
  llvm_cbe_or_2e_cond7_2e_us_2e_2 = (bool )((llvm_cbe_or_2e_cond_2e_us_2e_2 & (((signed int )llvm_cbe_tmp__12) < ((signed int )llvm_cbe_height)))&1);
if (AESL_DEBUG_TRACE)
printf("\nor.cond7.us.2 = 0x%X\n", llvm_cbe_or_2e_cond7_2e_us_2e_2);
  if (llvm_cbe_or_2e_cond7_2e_us_2e_2) {
    goto llvm_cbe__2e_preheader9_2e_us_2e_2;
  } else {
    goto llvm_cbe__2e_us_2d_lcssa_2e_us;
  }

llvm_cbe_tmp__87:
if (AESL_DEBUG_TRACE)
printf("\n  %%or.cond.us.1 = and i1 %%26, %%27, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_or_2e_cond_2e_us_2e_1_count);
  llvm_cbe_or_2e_cond_2e_us_2e_1 = (bool )(((((signed int )llvm_cbe_storemerge122) > ((signed int )4294967295u)) & (((signed int )llvm_cbe_storemerge122) < ((signed int )llvm_cbe_width)))&1);
if (AESL_DEBUG_TRACE)
printf("\nor.cond.us.1 = 0x%X\n", llvm_cbe_or_2e_cond_2e_us_2e_1);
if (AESL_DEBUG_TRACE)
printf("\n  %%or.cond7.us.1 = and i1 %%or.cond.us.1, %%18, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_or_2e_cond7_2e_us_2e_1_count);
  llvm_cbe_or_2e_cond7_2e_us_2e_1 = (bool )((llvm_cbe_or_2e_cond_2e_us_2e_1 & (((signed int )llvm_cbe_tmp__12) < ((signed int )llvm_cbe_height)))&1);
if (AESL_DEBUG_TRACE)
printf("\nor.cond7.us.1 = 0x%X\n", llvm_cbe_or_2e_cond7_2e_us_2e_1);
  if (llvm_cbe_or_2e_cond7_2e_us_2e_1) {
    goto llvm_cbe__2e_preheader9_2e_us_2e_1;
  } else {
    goto llvm_cbe_tmp__86;
  }

llvm_cbe__2e_preheader12_2e_split_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = add nsw i32 %%storemerge122, -1, !dbg !7 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_87_count);
  llvm_cbe_tmp__16 = (unsigned int )((unsigned int )(llvm_cbe_storemerge122&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__16&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%or.cond.us = and i1 %%23, %%24, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_or_2e_cond_2e_us_count);
  llvm_cbe_or_2e_cond_2e_us = (bool )(((((signed int )llvm_cbe_storemerge122) > ((signed int )0u)) & (((signed int )llvm_cbe_tmp__16) < ((signed int )llvm_cbe_width)))&1);
if (AESL_DEBUG_TRACE)
printf("\nor.cond.us = 0x%X\n", llvm_cbe_or_2e_cond_2e_us);
if (AESL_DEBUG_TRACE)
printf("\n  %%or.cond7.us = and i1 %%or.cond.us, %%18, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_or_2e_cond7_2e_us_count);
  llvm_cbe_or_2e_cond7_2e_us = (bool )((llvm_cbe_or_2e_cond_2e_us & (((signed int )llvm_cbe_tmp__12) < ((signed int )llvm_cbe_height)))&1);
if (AESL_DEBUG_TRACE)
printf("\nor.cond7.us = 0x%X\n", llvm_cbe_or_2e_cond7_2e_us);
  if (llvm_cbe_or_2e_cond7_2e_us) {
    goto llvm_cbe__2e_preheader9_2e_us;
  } else {
    goto llvm_cbe_tmp__87;
  }

llvm_cbe__2e_loopexit_2e_us:
  goto llvm_cbe_tmp__87;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__88:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge510.us = phi i32 [ 0, %%.lr.ph11.us ], [ %%29, %%28  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_storemerge510_2e_us_count);
  llvm_cbe_storemerge510_2e_us = (unsigned int )llvm_cbe_storemerge510_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge510.us = 0x%X",llvm_cbe_storemerge510_2e_us);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__17);
}
  if ((((signed int )llvm_cbe_storemerge510_2e_us) < ((signed int )3u))) {
    goto llvm_cbe_tmp__89;
  } else {
    goto llvm_cbe_tmp__90;
  }

llvm_cbe_tmp__90:
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = add nsw i32 %%storemerge510.us, 1, !dbg !8 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_107_count);
  llvm_cbe_tmp__17 = (unsigned int )((unsigned int )(llvm_cbe_storemerge510_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__17&4294967295ull)));
  if (((llvm_cbe_tmp__17&4294967295U) == (llvm_cbe_channels&4294967295U))) {
    goto llvm_cbe__2e_loopexit_2e_us;
  } else {
    llvm_cbe_storemerge510_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__17;   /* for PHI node */
    goto llvm_cbe_tmp__88;
  }

llvm_cbe_tmp__89:
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = add nsw i32 %%storemerge510.us, %%47, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_115_count);
  llvm_cbe_tmp__18 = (unsigned int )((unsigned int )(llvm_cbe_storemerge510_2e_us&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__32&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__18&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = sext i32 %%31 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_116_count);
  llvm_cbe_tmp__19 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__18);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__19);
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = getelementptr inbounds i8* %%image, i64 %%32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_117_count);
  llvm_cbe_tmp__20 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__19))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__19));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = load i8* %%33, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_118_count);
  llvm_cbe_tmp__21 = (unsigned char )*llvm_cbe_tmp__20;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__21);
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = zext i8 %%34 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_119_count);
  llvm_cbe_tmp__22 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__21&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__22);
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = sitofp i32 %%35 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_120_count);
  llvm_cbe_tmp__23 = (float )((float )(signed int )llvm_cbe_tmp__22);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__23, *(int*)(&llvm_cbe_tmp__23));
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = fmul float %%45, %%36, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_121_count);
  llvm_cbe_tmp__24 = (float )((float )(llvm_cbe_tmp__30 * llvm_cbe_tmp__23));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__24, *(int*)(&llvm_cbe_tmp__24));
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = sext i32 %%storemerge510.us to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_122_count);
  llvm_cbe_tmp__25 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge510_2e_us);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__25);
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = getelementptr inbounds [3 x float]* %%sum, i64 0, i64 %%38, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_123_count);
  llvm_cbe_tmp__26 = (float *)(&llvm_cbe_sum[(((signed long long )llvm_cbe_tmp__25))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__25));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__25) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'sum' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = load float* %%39, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_124_count);
  llvm_cbe_tmp__27 = (float )*llvm_cbe_tmp__26;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__27, *(int*)(&llvm_cbe_tmp__27));
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = fadd float %%40, %%37, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_125_count);
  llvm_cbe_tmp__28 = (float )((float )(llvm_cbe_tmp__27 + llvm_cbe_tmp__24));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__28, *(int*)(&llvm_cbe_tmp__28));

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__25) < 3 && "Write access out of array 'sum' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store float %%41, float* %%39, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_126_count);
  *llvm_cbe_tmp__26 = llvm_cbe_tmp__28;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__28);
  goto llvm_cbe_tmp__90;

  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e_lr_2e_ph11_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = getelementptr inbounds [3 x [3 x float]]* %%kernel, i64 0, i64 %%20, i64 0, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_137_count);
  llvm_cbe_tmp__29 = (float *)(&llvm_cbe_kernel[(((signed long long )llvm_cbe_tmp__14))
#ifdef AESL_BC_SIM
 % 3
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__14));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__14) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'kernel' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )0ull) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'kernel' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = load float* %%44, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_138_count);
  llvm_cbe_tmp__30 = (float )*llvm_cbe_tmp__29;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__30, *(int*)(&llvm_cbe_tmp__30));
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = add nsw i32 %%22, %%21, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_139_count);
  llvm_cbe_tmp__31 = (unsigned int )((unsigned int )(llvm_cbe_tmp__16&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__15&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__31&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = mul nsw i32 %%46, %%channels, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_140_count);
  llvm_cbe_tmp__32 = (unsigned int )((unsigned int )(llvm_cbe_tmp__31&4294967295ull)) * ((unsigned int )(llvm_cbe_channels&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__32&4294967295ull)));
  llvm_cbe_storemerge510_2e_us__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__88;

llvm_cbe__2e_preheader9_2e_us:
  if ((((signed int )llvm_cbe_channels) > ((signed int )0u))) {
    goto llvm_cbe__2e_lr_2e_ph11_2e_us;
  } else {
    goto llvm_cbe__2e_loopexit_2e_us;
  }

llvm_cbe__2e_loopexit_2e_us_2e_1:
  goto llvm_cbe_tmp__86;

llvm_cbe__2e_preheader9_2e_us_2e_1:
  if ((((signed int )llvm_cbe_channels) > ((signed int )0u))) {
    goto llvm_cbe__2e_lr_2e_ph11_2e_us_2e_1;
  } else {
    goto llvm_cbe__2e_loopexit_2e_us_2e_1;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__91:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge510.us.1 = phi i32 [ 0, %%.lr.ph11.us.1 ], [ %%95, %%94  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_storemerge510_2e_us_2e_1_count);
  llvm_cbe_storemerge510_2e_us_2e_1 = (unsigned int )llvm_cbe_storemerge510_2e_us_2e_1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge510.us.1 = 0x%X",llvm_cbe_storemerge510_2e_us_2e_1);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__67);
}
  if ((((signed int )llvm_cbe_storemerge510_2e_us_2e_1) < ((signed int )3u))) {
    goto llvm_cbe_tmp__92;
  } else {
    goto llvm_cbe_tmp__93;
  }

llvm_cbe_tmp__93:
if (AESL_DEBUG_TRACE)
printf("\n  %%95 = add nsw i32 %%storemerge510.us.1, 1, !dbg !8 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_242_count);
  llvm_cbe_tmp__67 = (unsigned int )((unsigned int )(llvm_cbe_storemerge510_2e_us_2e_1&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__67&4294967295ull)));
  if (((llvm_cbe_tmp__67&4294967295U) == (llvm_cbe_channels&4294967295U))) {
    goto llvm_cbe__2e_loopexit_2e_us_2e_1;
  } else {
    llvm_cbe_storemerge510_2e_us_2e_1__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__67;   /* for PHI node */
    goto llvm_cbe_tmp__91;
  }

llvm_cbe_tmp__92:
if (AESL_DEBUG_TRACE)
printf("\n  %%83 = add nsw i32 %%storemerge510.us.1, %%79, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_229_count);
  llvm_cbe_tmp__56 = (unsigned int )((unsigned int )(llvm_cbe_storemerge510_2e_us_2e_1&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__55&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__56&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%84 = sext i32 %%83 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_230_count);
  llvm_cbe_tmp__57 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__56);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__57);
if (AESL_DEBUG_TRACE)
printf("\n  %%85 = getelementptr inbounds i8* %%image, i64 %%84, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_231_count);
  llvm_cbe_tmp__58 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__57))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__57));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%86 = load i8* %%85, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_232_count);
  llvm_cbe_tmp__59 = (unsigned char )*llvm_cbe_tmp__58;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__59);
if (AESL_DEBUG_TRACE)
printf("\n  %%87 = zext i8 %%86 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_233_count);
  llvm_cbe_tmp__60 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__59&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__60);
if (AESL_DEBUG_TRACE)
printf("\n  %%88 = sitofp i32 %%87 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_234_count);
  llvm_cbe_tmp__61 = (float )((float )(signed int )llvm_cbe_tmp__60);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__61, *(int*)(&llvm_cbe_tmp__61));
if (AESL_DEBUG_TRACE)
printf("\n  %%89 = fmul float %%77, %%88, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_235_count);
  llvm_cbe_tmp__62 = (float )((float )(llvm_cbe_tmp__53 * llvm_cbe_tmp__61));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__62, *(int*)(&llvm_cbe_tmp__62));
if (AESL_DEBUG_TRACE)
printf("\n  %%90 = sext i32 %%storemerge510.us.1 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_236_count);
  llvm_cbe_tmp__63 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge510_2e_us_2e_1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__63);
if (AESL_DEBUG_TRACE)
printf("\n  %%91 = getelementptr inbounds [3 x float]* %%sum, i64 0, i64 %%90, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_237_count);
  llvm_cbe_tmp__64 = (float *)(&llvm_cbe_sum[(((signed long long )llvm_cbe_tmp__63))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__63));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__63) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'sum' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%92 = load float* %%91, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_238_count);
  llvm_cbe_tmp__65 = (float )*llvm_cbe_tmp__64;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__65, *(int*)(&llvm_cbe_tmp__65));
if (AESL_DEBUG_TRACE)
printf("\n  %%93 = fadd float %%92, %%89, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_239_count);
  llvm_cbe_tmp__66 = (float )((float )(llvm_cbe_tmp__65 + llvm_cbe_tmp__62));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__66, *(int*)(&llvm_cbe_tmp__66));

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__63) < 3 && "Write access out of array 'sum' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store float %%93, float* %%91, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_240_count);
  *llvm_cbe_tmp__64 = llvm_cbe_tmp__66;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__66);
  goto llvm_cbe_tmp__93;

  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e_lr_2e_ph11_2e_us_2e_1:
if (AESL_DEBUG_TRACE)
printf("\n  %%76 = getelementptr inbounds [3 x [3 x float]]* %%kernel, i64 0, i64 %%20, i64 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_222_count);
  llvm_cbe_tmp__52 = (float *)(&llvm_cbe_kernel[(((signed long long )llvm_cbe_tmp__14))
#ifdef AESL_BC_SIM
 % 3
#endif
][(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__14));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__14) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'kernel' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )1ull) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'kernel' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%77 = load float* %%76, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_223_count);
  llvm_cbe_tmp__53 = (float )*llvm_cbe_tmp__52;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__53, *(int*)(&llvm_cbe_tmp__53));
if (AESL_DEBUG_TRACE)
printf("\n  %%78 = add nsw i32 %%storemerge122, %%21, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_224_count);
  llvm_cbe_tmp__54 = (unsigned int )((unsigned int )(llvm_cbe_storemerge122&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__15&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__54&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%79 = mul nsw i32 %%78, %%channels, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_225_count);
  llvm_cbe_tmp__55 = (unsigned int )((unsigned int )(llvm_cbe_tmp__54&4294967295ull)) * ((unsigned int )(llvm_cbe_channels&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__55&4294967295ull)));
  llvm_cbe_storemerge510_2e_us_2e_1__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__91;

llvm_cbe__2e_loopexit_2e_us_2e_2:
  goto llvm_cbe__2e_us_2d_lcssa_2e_us;

llvm_cbe__2e_preheader9_2e_us_2e_2:
  if ((((signed int )llvm_cbe_channels) > ((signed int )0u))) {
    goto llvm_cbe__2e_lr_2e_ph11_2e_us_2e_2;
  } else {
    goto llvm_cbe__2e_loopexit_2e_us_2e_2;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__94:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge510.us.2 = phi i32 [ 0, %%.lr.ph11.us.2 ], [ %%119, %%118  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_storemerge510_2e_us_2e_2_count);
  llvm_cbe_storemerge510_2e_us_2e_2 = (unsigned int )llvm_cbe_storemerge510_2e_us_2e_2__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge510.us.2 = 0x%X",llvm_cbe_storemerge510_2e_us_2e_2);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__84);
}
  if ((((signed int )llvm_cbe_storemerge510_2e_us_2e_2) < ((signed int )3u))) {
    goto llvm_cbe_tmp__95;
  } else {
    goto llvm_cbe_tmp__96;
  }

llvm_cbe_tmp__96:
if (AESL_DEBUG_TRACE)
printf("\n  %%119 = add nsw i32 %%storemerge510.us.2, 1, !dbg !8 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_290_count);
  llvm_cbe_tmp__84 = (unsigned int )((unsigned int )(llvm_cbe_storemerge510_2e_us_2e_2&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__84&4294967295ull)));
  if (((llvm_cbe_tmp__84&4294967295U) == (llvm_cbe_channels&4294967295U))) {
    goto llvm_cbe__2e_loopexit_2e_us_2e_2;
  } else {
    llvm_cbe_storemerge510_2e_us_2e_2__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__84;   /* for PHI node */
    goto llvm_cbe_tmp__94;
  }

llvm_cbe_tmp__95:
if (AESL_DEBUG_TRACE)
printf("\n  %%107 = add nsw i32 %%storemerge510.us.2, %%103, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_277_count);
  llvm_cbe_tmp__73 = (unsigned int )((unsigned int )(llvm_cbe_storemerge510_2e_us_2e_2&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__72&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__73&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%108 = sext i32 %%107 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_278_count);
  llvm_cbe_tmp__74 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__73);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__74);
if (AESL_DEBUG_TRACE)
printf("\n  %%109 = getelementptr inbounds i8* %%image, i64 %%108, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_279_count);
  llvm_cbe_tmp__75 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__74))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__74));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%110 = load i8* %%109, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_280_count);
  llvm_cbe_tmp__76 = (unsigned char )*llvm_cbe_tmp__75;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__76);
if (AESL_DEBUG_TRACE)
printf("\n  %%111 = zext i8 %%110 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_281_count);
  llvm_cbe_tmp__77 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__76&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__77);
if (AESL_DEBUG_TRACE)
printf("\n  %%112 = sitofp i32 %%111 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_282_count);
  llvm_cbe_tmp__78 = (float )((float )(signed int )llvm_cbe_tmp__77);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__78, *(int*)(&llvm_cbe_tmp__78));
if (AESL_DEBUG_TRACE)
printf("\n  %%113 = fmul float %%101, %%112, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_283_count);
  llvm_cbe_tmp__79 = (float )((float )(llvm_cbe_tmp__70 * llvm_cbe_tmp__78));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__79, *(int*)(&llvm_cbe_tmp__79));
if (AESL_DEBUG_TRACE)
printf("\n  %%114 = sext i32 %%storemerge510.us.2 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_284_count);
  llvm_cbe_tmp__80 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge510_2e_us_2e_2);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__80);
if (AESL_DEBUG_TRACE)
printf("\n  %%115 = getelementptr inbounds [3 x float]* %%sum, i64 0, i64 %%114, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_285_count);
  llvm_cbe_tmp__81 = (float *)(&llvm_cbe_sum[(((signed long long )llvm_cbe_tmp__80))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__80));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__80) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'sum' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%116 = load float* %%115, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_286_count);
  llvm_cbe_tmp__82 = (float )*llvm_cbe_tmp__81;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__82, *(int*)(&llvm_cbe_tmp__82));
if (AESL_DEBUG_TRACE)
printf("\n  %%117 = fadd float %%116, %%113, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_287_count);
  llvm_cbe_tmp__83 = (float )((float )(llvm_cbe_tmp__82 + llvm_cbe_tmp__79));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__83, *(int*)(&llvm_cbe_tmp__83));

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__80) < 3 && "Write access out of array 'sum' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store float %%117, float* %%115, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_288_count);
  *llvm_cbe_tmp__81 = llvm_cbe_tmp__83;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__83);
  goto llvm_cbe_tmp__96;

  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e_lr_2e_ph11_2e_us_2e_2:
if (AESL_DEBUG_TRACE)
printf("\n  %%100 = getelementptr inbounds [3 x [3 x float]]* %%kernel, i64 0, i64 %%20, i64 2, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_270_count);
  llvm_cbe_tmp__69 = (float *)(&llvm_cbe_kernel[(((signed long long )llvm_cbe_tmp__14))
#ifdef AESL_BC_SIM
 % 3
#endif
][(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__14));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__14) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'kernel' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )2ull) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'kernel' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%101 = load float* %%100, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_271_count);
  llvm_cbe_tmp__70 = (float )*llvm_cbe_tmp__69;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__70, *(int*)(&llvm_cbe_tmp__70));
if (AESL_DEBUG_TRACE)
printf("\n  %%102 = add nsw i32 %%97, %%21, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_272_count);
  llvm_cbe_tmp__71 = (unsigned int )((unsigned int )(llvm_cbe_tmp__68&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__15&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__71&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%103 = mul nsw i32 %%102, %%channels, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_273_count);
  llvm_cbe_tmp__72 = (unsigned int )((unsigned int )(llvm_cbe_tmp__71&4294967295ull)) * ((unsigned int )(llvm_cbe_channels&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__72&4294967295ull)));
  llvm_cbe_storemerge510_2e_us_2e_2__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__94;

  } while (1); /* end of syntactic loop '.preheader12' */
  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__97:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge38 = phi i32 [ 0, %%.lr.ph ], [ %%73, %%72  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_storemerge38_count);
  llvm_cbe_storemerge38 = (unsigned int )llvm_cbe_storemerge38__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge38 = 0x%X",llvm_cbe_storemerge38);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__49);
}
  if ((((signed int )llvm_cbe_storemerge38) < ((signed int )3u))) {
    goto llvm_cbe_tmp__98;
  } else {
    goto llvm_cbe_tmp__99;
  }

llvm_cbe_tmp__100:
if (AESL_DEBUG_TRACE)
printf("\n  %%73 = add nsw i32 %%storemerge38, 1, !dbg !9 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_187_count);
  llvm_cbe_tmp__49 = (unsigned int )((unsigned int )(llvm_cbe_storemerge38&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__49&4294967295ull)));
  if (((llvm_cbe_tmp__49&4294967295U) == (llvm_cbe_channels&4294967295U))) {
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge38__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__49;   /* for PHI node */
    goto llvm_cbe_tmp__97;
  }

llvm_cbe_tmp__101:
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = phi i8 [ %%phitmp, %%58 ], [ -1, %%52 ], !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_174_count);
  llvm_cbe_tmp__40 = (unsigned char )llvm_cbe_tmp__40__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__40);
printf("\nphitmp = 0x%X",llvm_cbe_phitmp);
printf("\n = 0x%X",((unsigned char )-1));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%63 = add nsw i32 %%storemerge38, %%49, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_175_count);
  llvm_cbe_tmp__41 = (unsigned int )((unsigned int )(llvm_cbe_storemerge38&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__34&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__41&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%64 = sext i32 %%63 to i64, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_176_count);
  llvm_cbe_tmp__42 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__41);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__42);
if (AESL_DEBUG_TRACE)
printf("\n  %%65 = getelementptr inbounds i8* %%output, i64 %%64, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_177_count);
  llvm_cbe_tmp__43 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__42))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__42));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%62, i8* %%65, align 1, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_178_count);
  *llvm_cbe_tmp__43 = llvm_cbe_tmp__40;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__40);
  goto llvm_cbe_tmp__100;

llvm_cbe_tmp__98:
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = sext i32 %%storemerge38 to i64, !dbg !9 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_161_count);
  llvm_cbe_tmp__35 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge38);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__35);
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = getelementptr inbounds [3 x float]* %%sum, i64 0, i64 %%53, !dbg !9 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_162_count);
  llvm_cbe_tmp__36 = (float *)(&llvm_cbe_sum[(((signed long long )llvm_cbe_tmp__35))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__35));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__35) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'sum' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = load float* %%54, align 4, !dbg !9 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_163_count);
  llvm_cbe_tmp__37 = (float )*llvm_cbe_tmp__36;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__37, *(int*)(&llvm_cbe_tmp__37));
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = fptosi float %%55 to i32, !dbg !9 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_164_count);
  llvm_cbe_tmp__38 = (unsigned int )((signed int )llvm_cbe_tmp__37&4294967295U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__38);
  if ((((signed int )llvm_cbe_tmp__38) > ((signed int )255u))) {
    llvm_cbe_tmp__40__PHI_TEMPORARY = (unsigned char )((unsigned char )-1);   /* for PHI node */
    goto llvm_cbe_tmp__101;
  } else {
    goto llvm_cbe_tmp__102;
  }

llvm_cbe_tmp__102:
if (AESL_DEBUG_TRACE)
printf("\n  %%60 = trunc i32 %%56 to i8, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_172_count);
  llvm_cbe_tmp__39 = (unsigned char )((unsigned char )llvm_cbe_tmp__38&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__39);
if (AESL_DEBUG_TRACE)
printf("\n  %%phitmp = select i1 %%59, i8 0, i8 %%60, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_phitmp_count);
  llvm_cbe_phitmp = (unsigned char )(((((signed int )llvm_cbe_tmp__38) < ((signed int )0u))) ? ((unsigned char )((unsigned char )0)) : ((unsigned char )llvm_cbe_tmp__39));
if (AESL_DEBUG_TRACE)
printf("\nphitmp = 0x%X\n", llvm_cbe_phitmp);
  llvm_cbe_tmp__40__PHI_TEMPORARY = (unsigned char )llvm_cbe_phitmp;   /* for PHI node */
  goto llvm_cbe_tmp__101;

llvm_cbe_tmp__99:
if (AESL_DEBUG_TRACE)
printf("\n  %%67 = add nsw i32 %%storemerge38, %%49, !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_180_count);
  llvm_cbe_tmp__44 = (unsigned int )((unsigned int )(llvm_cbe_storemerge38&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__34&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__44&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%68 = sext i32 %%67 to i64, !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_181_count);
  llvm_cbe_tmp__45 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__44);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__45);
if (AESL_DEBUG_TRACE)
printf("\n  %%69 = getelementptr inbounds i8* %%image, i64 %%68, !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_182_count);
  llvm_cbe_tmp__46 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__45))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__45));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%70 = load i8* %%69, align 1, !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_183_count);
  llvm_cbe_tmp__47 = (unsigned char )*llvm_cbe_tmp__46;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n  %%71 = getelementptr inbounds i8* %%output, i64 %%68, !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_184_count);
  llvm_cbe_tmp__48 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__45))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__45));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%70, i8* %%71, align 1, !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_185_count);
  *llvm_cbe_tmp__48 = llvm_cbe_tmp__47;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__47);
  goto llvm_cbe_tmp__100;

  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%48 = add nsw i32 %%storemerge122, %%13, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_150_count);
  llvm_cbe_tmp__33 = (unsigned int )((unsigned int )(llvm_cbe_storemerge122&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__10&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__33&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%49 = mul nsw i32 %%48, %%channels, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_151_count);
  llvm_cbe_tmp__34 = (unsigned int )((unsigned int )(llvm_cbe_tmp__33&4294967295ull)) * ((unsigned int )(llvm_cbe_channels&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__34&4294967295ull)));
  llvm_cbe_storemerge38__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__97;

  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e_lr_2e_ph23:
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = mul nsw i32 %%storemerge25, %%width, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_66_count);
  llvm_cbe_tmp__10 = (unsigned int )((unsigned int )(llvm_cbe_storemerge25&4294967295ull)) * ((unsigned int )(llvm_cbe_width&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__10&4294967295ull)));
  llvm_cbe_storemerge122__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__85;

  } while (1); /* end of syntactic loop '.preheader21' */
llvm_cbe__2e__crit_edge26:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @applyConvolution}\n");
  return;
}

