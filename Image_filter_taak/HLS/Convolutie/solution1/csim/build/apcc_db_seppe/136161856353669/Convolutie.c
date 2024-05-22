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
void applyConvolution( char *llvm_cbe_image,  char *llvm_cbe_output);


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

void applyConvolution( char *llvm_cbe_image,  char *llvm_cbe_output) {
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
   char *llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
   char *llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  float *llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  float *llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  float *llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  float *llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  float *llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  float *llvm_cbe_tmp__8;
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
   char *llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge16_count = 0;
  unsigned int llvm_cbe_storemerge16;
  unsigned int llvm_cbe_storemerge16__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  unsigned int llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge115_count = 0;
  unsigned int llvm_cbe_storemerge115;
  unsigned int llvm_cbe_storemerge115__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
   char *llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  float llvm_cbe_tmp__12;
  float llvm_cbe_tmp__12__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  float llvm_cbe_tmp__13;
  float llvm_cbe_tmp__13__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  float llvm_cbe_tmp__14;
  float llvm_cbe_tmp__14__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  float llvm_cbe_tmp__15;
  float llvm_cbe_tmp__15__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_storemerge213_count = 0;
  unsigned int llvm_cbe_storemerge213;
  unsigned int llvm_cbe_storemerge213__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  unsigned int llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  unsigned int llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  unsigned long long llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  unsigned int llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  unsigned int llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_or_2e_cond_2e_us_2e_us_count = 0;
  bool llvm_cbe_or_2e_cond_2e_us_2e_us;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  float llvm_cbe_tmp__21;
  float llvm_cbe_tmp__21__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  float llvm_cbe_tmp__22;
  float llvm_cbe_tmp__22__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  float llvm_cbe_tmp__23;
  float llvm_cbe_tmp__23__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  float llvm_cbe_tmp__24;
  float llvm_cbe_tmp__24__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_or_2e_cond_2e_us_2e_us_2e_1_count = 0;
  bool llvm_cbe_or_2e_cond_2e_us_2e_us_2e_1;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  float *llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  float llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  unsigned int llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  unsigned long long llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
   char *llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  unsigned char llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  unsigned int llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  float llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  float llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  float *llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  float llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  unsigned int llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  unsigned int llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  float llvm_cbe_tmp__38;
  float llvm_cbe_tmp__38__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  float llvm_cbe_tmp__39;
  float llvm_cbe_tmp__39__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  float llvm_cbe_tmp__40;
  float llvm_cbe_tmp__40__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  float llvm_cbe_tmp__41;
  float llvm_cbe_tmp__41__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond19_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  unsigned char llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_phitmp_count = 0;
  unsigned char llvm_cbe_phitmp;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  unsigned char llvm_cbe_tmp__43;
  unsigned char llvm_cbe_tmp__43__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  unsigned long long llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
   char *llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  unsigned int llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond20_count = 0;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  unsigned int llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond21_count = 0;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  float *llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  float llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  unsigned int llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  unsigned long long llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
   char *llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  unsigned char llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  unsigned int llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  float llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  float llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  float *llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  float llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  float llvm_cbe_tmp__59;
  float llvm_cbe_tmp__59__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  float llvm_cbe_tmp__60;
  float llvm_cbe_tmp__60__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  float llvm_cbe_tmp__61;
  float llvm_cbe_tmp__61__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  float llvm_cbe_tmp__62;
  float llvm_cbe_tmp__62__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  unsigned int llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  static  unsigned long long aesl_llvm_cbe_or_2e_cond_2e_us_2e_us_2e_2_count = 0;
  bool llvm_cbe_or_2e_cond_2e_us_2e_us_2e_2;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  float *llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  float llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  unsigned int llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  unsigned long long llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
   char *llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  unsigned char llvm_cbe_tmp__69;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  unsigned int llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  float llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  float llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  float *llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  float llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @applyConvolution\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = bitcast [3 x [3 x float]]* %%kernel to i8*, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_8_count);
  llvm_cbe_tmp__1 = ( char *)(( char *)(&llvm_cbe_kernel));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = call i8* @memset(i8* %%1, i32 0, i64 36 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_9_count);
  ( char *)memset(( char *)llvm_cbe_tmp__1, 0u, 36ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%I64X",36ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__2);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 0, i64 0, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_10_count);
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
printf("\n  store float 1.000000e+00, float* %%3, align 16, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_11_count);
  *llvm_cbe_tmp__3 = 0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 0, i64 2, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_12_count);
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
printf("\n  store float -1.000000e+00, float* %%4, align 8, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_13_count);
  *llvm_cbe_tmp__4 = -0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", -0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 1, i64 0, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_14_count);
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
printf("\n  store float 1.000000e+00, float* %%5, align 4, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_15_count);
  *llvm_cbe_tmp__5 = 0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 1, i64 2, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_16_count);
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
printf("\n  store float -1.000000e+00, float* %%6, align 4, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_17_count);
  *llvm_cbe_tmp__6 = -0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", -0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 2, i64 0, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_18_count);
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
printf("\n  store float 1.000000e+00, float* %%7, align 8, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_19_count);
  *llvm_cbe_tmp__7 = 0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 2, i64 2, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_20_count);
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
printf("\n  store float -1.000000e+00, float* %%8, align 8, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_21_count);
  *llvm_cbe_tmp__8 = -0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", -0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = bitcast [3 x float]* %%sum to i8*, !dbg !7 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_53_count);
  llvm_cbe_tmp__9 = ( char *)(( char *)(&llvm_cbe_sum));
  llvm_cbe_storemerge16__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  goto llvm_cbe__2e_preheader14;

  do {     /* Syntactic loop '.preheader14' to make GCC happy */
llvm_cbe__2e_preheader14:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge16 = phi i32 [ 1, %%0 ], [ %%60, %%59  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_storemerge16_count);
  llvm_cbe_storemerge16 = (unsigned int )llvm_cbe_storemerge16__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge16 = 0x%X",llvm_cbe_storemerge16);
printf("\n = 0x%X",1u);
printf("\n = 0x%X",llvm_cbe_tmp__47);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = mul nsw i32 %%storemerge16, 6, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_61_count);
  llvm_cbe_tmp__10 = (unsigned int )((unsigned int )(llvm_cbe_storemerge16&4294967295ull)) * ((unsigned int )(6u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__10&4294967295ull)));
  llvm_cbe_storemerge115__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  goto llvm_cbe_tmp__75;

llvm_cbe_tmp__76:
if (AESL_DEBUG_TRACE)
printf("\n  %%60 = add nsw i32 %%storemerge16, 1, !dbg !7 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_170_count);
  llvm_cbe_tmp__47 = (unsigned int )((unsigned int )(llvm_cbe_storemerge16&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__47&4294967295ull)));
  if (((llvm_cbe_tmp__47&4294967295U) == (6u&4294967295U))) {
    goto llvm_cbe_tmp__77;
  } else {
    llvm_cbe_storemerge16__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__47;   /* for PHI node */
    goto llvm_cbe__2e_preheader14;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__75:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge115 = phi i32 [ 1, %%.preheader14 ], [ %%58, %%54  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_storemerge115_count);
  llvm_cbe_storemerge115 = (unsigned int )llvm_cbe_storemerge115__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge115 = 0x%X",llvm_cbe_storemerge115);
printf("\n = 0x%X",1u);
printf("\n = 0x%X",llvm_cbe_tmp__46);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = call i8* @memset(i8* %%9, i32 0, i64 12 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_64_count);
  ( char *)memset(( char *)llvm_cbe_tmp__9, 0u, 12ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%I64X",12ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__11);
}
  llvm_cbe_tmp__12__PHI_TEMPORARY = (float )0x0p0;   /* for PHI node */
  llvm_cbe_tmp__13__PHI_TEMPORARY = (float )0x0p0;   /* for PHI node */
  llvm_cbe_tmp__14__PHI_TEMPORARY = (float )0x0p0;   /* for PHI node */
  llvm_cbe_tmp__15__PHI_TEMPORARY = (float )0x0p0;   /* for PHI node */
  llvm_cbe_storemerge213__PHI_TEMPORARY = (unsigned int )4294967295u;   /* for PHI node */
  goto llvm_cbe__2e_preheader11;

llvm_cbe_tmp__78:
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = phi i8 [ %%phitmp, %%51 ], [ -1, %%.preheader ], !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_157_count);
  llvm_cbe_tmp__43 = (unsigned char )llvm_cbe_tmp__43__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__43);
printf("\nphitmp = 0x%X",llvm_cbe_phitmp);
printf("\n = 0x%X",((unsigned char )-1));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = sext i32 %%44 to i64, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_158_count);
  llvm_cbe_tmp__44 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__44);
if (AESL_DEBUG_TRACE)
printf("\n  %%57 = getelementptr inbounds i8* %%output, i64 %%56, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_159_count);
  llvm_cbe_tmp__45 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__44))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__44));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%55, i8* %%57, align 1, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_160_count);
  *llvm_cbe_tmp__45 = llvm_cbe_tmp__43;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__43);
if (AESL_DEBUG_TRACE)
printf("\n  %%58 = add nsw i32 %%storemerge115, 1, !dbg !7 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_161_count);
  llvm_cbe_tmp__46 = (unsigned int )((unsigned int )(llvm_cbe_storemerge115&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__46&4294967295ull)));
  if (((llvm_cbe_tmp__46&4294967295U) == (6u&4294967295U))) {
    goto llvm_cbe_tmp__76;
  } else {
    llvm_cbe_storemerge115__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__46;   /* for PHI node */
    goto llvm_cbe_tmp__75;
  }

llvm_cbe__2e_preheader:
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = add i32 %%storemerge115, %%10, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_136_count);
  llvm_cbe_tmp__36 = (unsigned int )((unsigned int )(llvm_cbe_storemerge115&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__10&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__36&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = fptosi float %%47 to i32, !dbg !9 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_137_count);
  llvm_cbe_tmp__37 = (unsigned int )((signed int )llvm_cbe_tmp__38&4294967295U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__37);
  if ((((signed int )llvm_cbe_tmp__37) > ((signed int )255u))) {
    llvm_cbe_tmp__43__PHI_TEMPORARY = (unsigned char )((unsigned char )-1);   /* for PHI node */
    goto llvm_cbe_tmp__78;
  } else {
    goto llvm_cbe_tmp__79;
  }

  do {     /* Syntactic loop '.preheader11' to make GCC happy */
llvm_cbe__2e_preheader11:
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = phi float [ 0.000000e+00, %%11 ], [ %%47, %%.preheader11..preheader11.split_crit_edge  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_71_count);
  llvm_cbe_tmp__12 = (float )llvm_cbe_tmp__12__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__12);
printf("\n = %f",0x0p0);
printf("\n = %f",llvm_cbe_tmp__38);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = phi float [ 0.000000e+00, %%11 ], [ %%48, %%.preheader11..preheader11.split_crit_edge  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_72_count);
  llvm_cbe_tmp__13 = (float )llvm_cbe_tmp__13__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__13);
printf("\n = %f",0x0p0);
printf("\n = %f",llvm_cbe_tmp__39);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = phi float [ 0.000000e+00, %%11 ], [ %%49, %%.preheader11..preheader11.split_crit_edge  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_73_count);
  llvm_cbe_tmp__14 = (float )llvm_cbe_tmp__14__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__14);
printf("\n = %f",0x0p0);
printf("\n = %f",llvm_cbe_tmp__40);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = phi float [ 0.000000e+00, %%11 ], [ %%50, %%.preheader11..preheader11.split_crit_edge  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_74_count);
  llvm_cbe_tmp__15 = (float )llvm_cbe_tmp__15__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__15);
printf("\n = %f",0x0p0);
printf("\n = %f",llvm_cbe_tmp__41);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge213 = phi i32 [ -1, %%11 ], [ %%20, %%.preheader11..preheader11.split_crit_edge  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_storemerge213_count);
  llvm_cbe_storemerge213 = (unsigned int )llvm_cbe_storemerge213__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge213 = 0x%X",llvm_cbe_storemerge213);
printf("\n = 0x%X",4294967295u);
printf("\n = 0x%X",llvm_cbe_tmp__17);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = add nsw i32 %%storemerge213, %%storemerge16, !dbg !7 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_79_count);
  llvm_cbe_tmp__16 = (unsigned int )((unsigned int )(llvm_cbe_storemerge213&4294967295ull)) + ((unsigned int )(llvm_cbe_storemerge16&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__16&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = add nsw i32 %%storemerge213, 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_82_count);
  llvm_cbe_tmp__17 = (unsigned int )((unsigned int )(llvm_cbe_storemerge213&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__17&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = sext i32 %%20 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_83_count);
  llvm_cbe_tmp__18 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__17);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__18);
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = mul nsw i32 %%17, 6, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_84_count);
  llvm_cbe_tmp__19 = (unsigned int )((unsigned int )(llvm_cbe_tmp__16&4294967295ull)) * ((unsigned int )(6u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__19&4294967295ull)));
  if ((((signed int )llvm_cbe_tmp__16) > ((signed int )4294967295u))) {
    goto llvm_cbe__2e_preheader11_2e_split_2e_us;
  } else {
    llvm_cbe_tmp__38__PHI_TEMPORARY = (float )llvm_cbe_tmp__12;   /* for PHI node */
    llvm_cbe_tmp__39__PHI_TEMPORARY = (float )llvm_cbe_tmp__13;   /* for PHI node */
    llvm_cbe_tmp__40__PHI_TEMPORARY = (float )llvm_cbe_tmp__14;   /* for PHI node */
    llvm_cbe_tmp__41__PHI_TEMPORARY = (float )llvm_cbe_tmp__15;   /* for PHI node */
    goto llvm_cbe__2e_preheader11_2e__2e_preheader11_2e_split_crit_edge;
  }

llvm_cbe__2e_preheader11_2e__2e_preheader11_2e_split_crit_edge:
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = phi float [ %%13, %%.preheader11 ], [ %%13, %%.preheader11.split.us ], [ %%91, %%.preheader9.us.us.2 ], [ %%74, %%73  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_144_count);
  llvm_cbe_tmp__38 = (float )llvm_cbe_tmp__38__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__38);
printf("\n = %f",llvm_cbe_tmp__12);
printf("\n = %f",llvm_cbe_tmp__12);
printf("\n = %f",llvm_cbe_tmp__74);
printf("\n = %f",llvm_cbe_tmp__59);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%48 = phi float [ %%14, %%.preheader11 ], [ %%14, %%.preheader11.split.us ], [ %%91, %%.preheader9.us.us.2 ], [ %%75, %%73  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_145_count);
  llvm_cbe_tmp__39 = (float )llvm_cbe_tmp__39__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__39);
printf("\n = %f",llvm_cbe_tmp__13);
printf("\n = %f",llvm_cbe_tmp__13);
printf("\n = %f",llvm_cbe_tmp__74);
printf("\n = %f",llvm_cbe_tmp__60);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%49 = phi float [ %%15, %%.preheader11 ], [ %%15, %%.preheader11.split.us ], [ %%91, %%.preheader9.us.us.2 ], [ %%76, %%73  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_146_count);
  llvm_cbe_tmp__40 = (float )llvm_cbe_tmp__40__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__40);
printf("\n = %f",llvm_cbe_tmp__14);
printf("\n = %f",llvm_cbe_tmp__14);
printf("\n = %f",llvm_cbe_tmp__74);
printf("\n = %f",llvm_cbe_tmp__61);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%50 = phi float [ %%16, %%.preheader11 ], [ %%16, %%.preheader11.split.us ], [ %%91, %%.preheader9.us.us.2 ], [ %%77, %%73  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_147_count);
  llvm_cbe_tmp__41 = (float )llvm_cbe_tmp__41__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__41);
printf("\n = %f",llvm_cbe_tmp__15);
printf("\n = %f",llvm_cbe_tmp__15);
printf("\n = %f",llvm_cbe_tmp__74);
printf("\n = %f",llvm_cbe_tmp__62);
}
  if (((llvm_cbe_tmp__17&4294967295U) == (2u&4294967295U))) {
    goto llvm_cbe__2e_preheader;
  } else {
    llvm_cbe_tmp__12__PHI_TEMPORARY = (float )llvm_cbe_tmp__38;   /* for PHI node */
    llvm_cbe_tmp__13__PHI_TEMPORARY = (float )llvm_cbe_tmp__39;   /* for PHI node */
    llvm_cbe_tmp__14__PHI_TEMPORARY = (float )llvm_cbe_tmp__40;   /* for PHI node */
    llvm_cbe_tmp__15__PHI_TEMPORARY = (float )llvm_cbe_tmp__41;   /* for PHI node */
    llvm_cbe_storemerge213__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__17;   /* for PHI node */
    goto llvm_cbe__2e_preheader11;
  }

llvm_cbe__2e_preheader11_2e_split_2e_us:
  if ((((signed int )llvm_cbe_tmp__16) < ((signed int )6u))) {
    goto llvm_cbe__2e_preheader11_2e_split_2e_us_2e_split_2e_us;
  } else {
    llvm_cbe_tmp__38__PHI_TEMPORARY = (float )llvm_cbe_tmp__12;   /* for PHI node */
    llvm_cbe_tmp__39__PHI_TEMPORARY = (float )llvm_cbe_tmp__13;   /* for PHI node */
    llvm_cbe_tmp__40__PHI_TEMPORARY = (float )llvm_cbe_tmp__14;   /* for PHI node */
    llvm_cbe_tmp__41__PHI_TEMPORARY = (float )llvm_cbe_tmp__15;   /* for PHI node */
    goto llvm_cbe__2e_preheader11_2e__2e_preheader11_2e_split_crit_edge;
  }

llvm_cbe_tmp__80:
if (AESL_DEBUG_TRACE)
printf("\n  %%74 = phi float [ %%72, %%.preheader9.us.us.1 ], [ %%27, %%26  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_198_count);
  llvm_cbe_tmp__59 = (float )llvm_cbe_tmp__59__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__59);
printf("\n = %f",llvm_cbe_tmp__58);
printf("\n = %f",llvm_cbe_tmp__21);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%75 = phi float [ %%72, %%.preheader9.us.us.1 ], [ %%28, %%26  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_199_count);
  llvm_cbe_tmp__60 = (float )llvm_cbe_tmp__60__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__60);
printf("\n = %f",llvm_cbe_tmp__58);
printf("\n = %f",llvm_cbe_tmp__22);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%76 = phi float [ %%72, %%.preheader9.us.us.1 ], [ %%29, %%26  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_200_count);
  llvm_cbe_tmp__61 = (float )llvm_cbe_tmp__61__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__61);
printf("\n = %f",llvm_cbe_tmp__58);
printf("\n = %f",llvm_cbe_tmp__23);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%77 = phi float [ %%72, %%.preheader9.us.us.1 ], [ %%30, %%26  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_201_count);
  llvm_cbe_tmp__62 = (float )llvm_cbe_tmp__62__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__62);
printf("\n = %f",llvm_cbe_tmp__58);
printf("\n = %f",llvm_cbe_tmp__24);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%78 = add nsw i32 %%storemerge115, 1, !dbg !7 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_207_count);
  llvm_cbe_tmp__63 = (unsigned int )((unsigned int )(llvm_cbe_storemerge115&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__63&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%or.cond.us.us.2 = and i1 %%79, %%80, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_or_2e_cond_2e_us_2e_us_2e_2_count);
  llvm_cbe_or_2e_cond_2e_us_2e_us_2e_2 = (bool )(((((signed int )llvm_cbe_tmp__63) > ((signed int )4294967295u)) & (((signed int )llvm_cbe_tmp__63) < ((signed int )6u)))&1);
if (AESL_DEBUG_TRACE)
printf("\nor.cond.us.us.2 = 0x%X\n", llvm_cbe_or_2e_cond_2e_us_2e_us_2e_2);
  if (llvm_cbe_or_2e_cond_2e_us_2e_us_2e_2) {
    goto llvm_cbe__2e_preheader9_2e_us_2e_us_2e_2;
  } else {
    llvm_cbe_tmp__38__PHI_TEMPORARY = (float )llvm_cbe_tmp__59;   /* for PHI node */
    llvm_cbe_tmp__39__PHI_TEMPORARY = (float )llvm_cbe_tmp__60;   /* for PHI node */
    llvm_cbe_tmp__40__PHI_TEMPORARY = (float )llvm_cbe_tmp__61;   /* for PHI node */
    llvm_cbe_tmp__41__PHI_TEMPORARY = (float )llvm_cbe_tmp__62;   /* for PHI node */
    goto llvm_cbe__2e_preheader11_2e__2e_preheader11_2e_split_crit_edge;
  }

llvm_cbe_tmp__81:
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = phi float [ %%43, %%.preheader9.us.us ], [ %%13, %%.preheader11.split.us.split.us  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_95_count);
  llvm_cbe_tmp__21 = (float )llvm_cbe_tmp__21__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__21);
printf("\n = %f",llvm_cbe_tmp__35);
printf("\n = %f",llvm_cbe_tmp__12);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = phi float [ %%43, %%.preheader9.us.us ], [ %%14, %%.preheader11.split.us.split.us  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_96_count);
  llvm_cbe_tmp__22 = (float )llvm_cbe_tmp__22__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__22);
printf("\n = %f",llvm_cbe_tmp__35);
printf("\n = %f",llvm_cbe_tmp__13);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = phi float [ %%43, %%.preheader9.us.us ], [ %%15, %%.preheader11.split.us.split.us  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_97_count);
  llvm_cbe_tmp__23 = (float )llvm_cbe_tmp__23__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__23);
printf("\n = %f",llvm_cbe_tmp__35);
printf("\n = %f",llvm_cbe_tmp__14);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = phi float [ %%43, %%.preheader9.us.us ], [ %%16, %%.preheader11.split.us.split.us  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_98_count);
  llvm_cbe_tmp__24 = (float )llvm_cbe_tmp__24__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %f",llvm_cbe_tmp__24);
printf("\n = %f",llvm_cbe_tmp__35);
printf("\n = %f",llvm_cbe_tmp__15);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%or.cond.us.us.1 = and i1 %%31, %%32, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_or_2e_cond_2e_us_2e_us_2e_1_count);
  llvm_cbe_or_2e_cond_2e_us_2e_us_2e_1 = (bool )(((((signed int )llvm_cbe_storemerge115) > ((signed int )4294967295u)) & (((signed int )llvm_cbe_storemerge115) < ((signed int )6u)))&1);
if (AESL_DEBUG_TRACE)
printf("\nor.cond.us.us.1 = 0x%X\n", llvm_cbe_or_2e_cond_2e_us_2e_us_2e_1);
  if (llvm_cbe_or_2e_cond_2e_us_2e_us_2e_1) {
    goto llvm_cbe__2e_preheader9_2e_us_2e_us_2e_1;
  } else {
    llvm_cbe_tmp__59__PHI_TEMPORARY = (float )llvm_cbe_tmp__21;   /* for PHI node */
    llvm_cbe_tmp__60__PHI_TEMPORARY = (float )llvm_cbe_tmp__22;   /* for PHI node */
    llvm_cbe_tmp__61__PHI_TEMPORARY = (float )llvm_cbe_tmp__23;   /* for PHI node */
    llvm_cbe_tmp__62__PHI_TEMPORARY = (float )llvm_cbe_tmp__24;   /* for PHI node */
    goto llvm_cbe_tmp__80;
  }

llvm_cbe__2e_preheader11_2e_split_2e_us_2e_split_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = add nsw i32 %%storemerge115, -1, !dbg !7 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_87_count);
  llvm_cbe_tmp__20 = (unsigned int )((unsigned int )(llvm_cbe_storemerge115&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__20&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%or.cond.us.us = and i1 %%24, %%25, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_or_2e_cond_2e_us_2e_us_count);
  llvm_cbe_or_2e_cond_2e_us_2e_us = (bool )(((((signed int )llvm_cbe_storemerge115) > ((signed int )0u)) & (((signed int )llvm_cbe_tmp__20) < ((signed int )6u)))&1);
if (AESL_DEBUG_TRACE)
printf("\nor.cond.us.us = 0x%X\n", llvm_cbe_or_2e_cond_2e_us_2e_us);
  if (llvm_cbe_or_2e_cond_2e_us_2e_us) {
    goto llvm_cbe__2e_preheader9_2e_us_2e_us;
  } else {
    llvm_cbe_tmp__21__PHI_TEMPORARY = (float )llvm_cbe_tmp__12;   /* for PHI node */
    llvm_cbe_tmp__22__PHI_TEMPORARY = (float )llvm_cbe_tmp__13;   /* for PHI node */
    llvm_cbe_tmp__23__PHI_TEMPORARY = (float )llvm_cbe_tmp__14;   /* for PHI node */
    llvm_cbe_tmp__24__PHI_TEMPORARY = (float )llvm_cbe_tmp__15;   /* for PHI node */
    goto llvm_cbe_tmp__81;
  }

llvm_cbe__2e_preheader9_2e_us_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = getelementptr inbounds [3 x [3 x float]]* %%kernel, i64 0, i64 %%21, i64 0, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_116_count);
  llvm_cbe_tmp__25 = (float *)(&llvm_cbe_kernel[(((signed long long )llvm_cbe_tmp__18))
#ifdef AESL_BC_SIM
 % 3
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__18));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__18) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'kernel' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )0ull) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'kernel' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = load float* %%33, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_117_count);
  llvm_cbe_tmp__26 = (float )*llvm_cbe_tmp__25;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__26, *(int*)(&llvm_cbe_tmp__26));
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = add i32 %%23, %%22, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_118_count);
  llvm_cbe_tmp__27 = (unsigned int )((unsigned int )(llvm_cbe_tmp__20&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__19&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__27&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = sext i32 %%35 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_119_count);
  llvm_cbe_tmp__28 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__27);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__28);
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = getelementptr inbounds i8* %%image, i64 %%36, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_120_count);
  llvm_cbe_tmp__29 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__28))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__28));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = load i8* %%37, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_121_count);
  llvm_cbe_tmp__30 = (unsigned char )*llvm_cbe_tmp__29;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__30);
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = zext i8 %%38 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_122_count);
  llvm_cbe_tmp__31 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__30&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__31);
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = sitofp i32 %%39 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_123_count);
  llvm_cbe_tmp__32 = (float )((float )(signed int )llvm_cbe_tmp__31);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__32, *(int*)(&llvm_cbe_tmp__32));
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = fmul float %%34, %%40, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_124_count);
  llvm_cbe_tmp__33 = (float )((float )(llvm_cbe_tmp__26 * llvm_cbe_tmp__32));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__33, *(int*)(&llvm_cbe_tmp__33));
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = getelementptr inbounds [3 x float]* %%sum, i64 0, i64 0, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_125_count);
  llvm_cbe_tmp__34 = (float *)(&llvm_cbe_sum[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = fadd float %%16, %%41, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_126_count);
  llvm_cbe_tmp__35 = (float )((float )(llvm_cbe_tmp__15 + llvm_cbe_tmp__33));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__35, *(int*)(&llvm_cbe_tmp__35));

#ifdef AESL_BC_SIM
  assert(((signed long long )0ull) < 3 && "Write access out of array 'sum' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store float %%43, float* %%42, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_127_count);
  *llvm_cbe_tmp__34 = llvm_cbe_tmp__35;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__35);
  llvm_cbe_tmp__21__PHI_TEMPORARY = (float )llvm_cbe_tmp__35;   /* for PHI node */
  llvm_cbe_tmp__22__PHI_TEMPORARY = (float )llvm_cbe_tmp__35;   /* for PHI node */
  llvm_cbe_tmp__23__PHI_TEMPORARY = (float )llvm_cbe_tmp__35;   /* for PHI node */
  llvm_cbe_tmp__24__PHI_TEMPORARY = (float )llvm_cbe_tmp__35;   /* for PHI node */
  goto llvm_cbe_tmp__81;

llvm_cbe__2e_preheader9_2e_us_2e_us_2e_1:
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = getelementptr inbounds [3 x [3 x float]]* %%kernel, i64 0, i64 %%21, i64 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_185_count);
  llvm_cbe_tmp__48 = (float *)(&llvm_cbe_kernel[(((signed long long )llvm_cbe_tmp__18))
#ifdef AESL_BC_SIM
 % 3
#endif
][(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__18));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__18) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'kernel' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )1ull) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'kernel' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%63 = load float* %%62, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_186_count);
  llvm_cbe_tmp__49 = (float )*llvm_cbe_tmp__48;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__49, *(int*)(&llvm_cbe_tmp__49));
if (AESL_DEBUG_TRACE)
printf("\n  %%64 = add i32 %%storemerge115, %%22, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_187_count);
  llvm_cbe_tmp__50 = (unsigned int )((unsigned int )(llvm_cbe_storemerge115&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__19&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__50&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%65 = sext i32 %%64 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_188_count);
  llvm_cbe_tmp__51 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__50);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__51);
if (AESL_DEBUG_TRACE)
printf("\n  %%66 = getelementptr inbounds i8* %%image, i64 %%65, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_189_count);
  llvm_cbe_tmp__52 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__51))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__51));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%67 = load i8* %%66, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_190_count);
  llvm_cbe_tmp__53 = (unsigned char )*llvm_cbe_tmp__52;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__53);
if (AESL_DEBUG_TRACE)
printf("\n  %%68 = zext i8 %%67 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_191_count);
  llvm_cbe_tmp__54 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__53&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__54);
if (AESL_DEBUG_TRACE)
printf("\n  %%69 = sitofp i32 %%68 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_192_count);
  llvm_cbe_tmp__55 = (float )((float )(signed int )llvm_cbe_tmp__54);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__55, *(int*)(&llvm_cbe_tmp__55));
if (AESL_DEBUG_TRACE)
printf("\n  %%70 = fmul float %%63, %%69, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_193_count);
  llvm_cbe_tmp__56 = (float )((float )(llvm_cbe_tmp__49 * llvm_cbe_tmp__55));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__56, *(int*)(&llvm_cbe_tmp__56));
if (AESL_DEBUG_TRACE)
printf("\n  %%71 = getelementptr inbounds [3 x float]* %%sum, i64 0, i64 0, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_194_count);
  llvm_cbe_tmp__57 = (float *)(&llvm_cbe_sum[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%72 = fadd float %%29, %%70, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_195_count);
  llvm_cbe_tmp__58 = (float )((float )(llvm_cbe_tmp__23 + llvm_cbe_tmp__56));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__58, *(int*)(&llvm_cbe_tmp__58));

#ifdef AESL_BC_SIM
  assert(((signed long long )0ull) < 3 && "Write access out of array 'sum' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store float %%72, float* %%71, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_196_count);
  *llvm_cbe_tmp__57 = llvm_cbe_tmp__58;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__58);
  llvm_cbe_tmp__59__PHI_TEMPORARY = (float )llvm_cbe_tmp__58;   /* for PHI node */
  llvm_cbe_tmp__60__PHI_TEMPORARY = (float )llvm_cbe_tmp__58;   /* for PHI node */
  llvm_cbe_tmp__61__PHI_TEMPORARY = (float )llvm_cbe_tmp__58;   /* for PHI node */
  llvm_cbe_tmp__62__PHI_TEMPORARY = (float )llvm_cbe_tmp__58;   /* for PHI node */
  goto llvm_cbe_tmp__80;

llvm_cbe__2e_preheader9_2e_us_2e_us_2e_2:
if (AESL_DEBUG_TRACE)
printf("\n  %%81 = getelementptr inbounds [3 x [3 x float]]* %%kernel, i64 0, i64 %%21, i64 2, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_220_count);
  llvm_cbe_tmp__64 = (float *)(&llvm_cbe_kernel[(((signed long long )llvm_cbe_tmp__18))
#ifdef AESL_BC_SIM
 % 3
#endif
][(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__18));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__18) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'kernel' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )2ull) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'kernel' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%82 = load float* %%81, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_221_count);
  llvm_cbe_tmp__65 = (float )*llvm_cbe_tmp__64;
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__65, *(int*)(&llvm_cbe_tmp__65));
if (AESL_DEBUG_TRACE)
printf("\n  %%83 = add i32 %%78, %%22, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_222_count);
  llvm_cbe_tmp__66 = (unsigned int )((unsigned int )(llvm_cbe_tmp__63&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__19&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__66&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%84 = sext i32 %%83 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_223_count);
  llvm_cbe_tmp__67 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__66);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__67);
if (AESL_DEBUG_TRACE)
printf("\n  %%85 = getelementptr inbounds i8* %%image, i64 %%84, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_224_count);
  llvm_cbe_tmp__68 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__67))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__67));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%86 = load i8* %%85, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_225_count);
  llvm_cbe_tmp__69 = (unsigned char )*llvm_cbe_tmp__68;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__69);
if (AESL_DEBUG_TRACE)
printf("\n  %%87 = zext i8 %%86 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_226_count);
  llvm_cbe_tmp__70 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__69&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__70);
if (AESL_DEBUG_TRACE)
printf("\n  %%88 = sitofp i32 %%87 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_227_count);
  llvm_cbe_tmp__71 = (float )((float )(signed int )llvm_cbe_tmp__70);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__71, *(int*)(&llvm_cbe_tmp__71));
if (AESL_DEBUG_TRACE)
printf("\n  %%89 = fmul float %%82, %%88, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_228_count);
  llvm_cbe_tmp__72 = (float )((float )(llvm_cbe_tmp__65 * llvm_cbe_tmp__71));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__72, *(int*)(&llvm_cbe_tmp__72));
if (AESL_DEBUG_TRACE)
printf("\n  %%90 = getelementptr inbounds [3 x float]* %%sum, i64 0, i64 0, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_229_count);
  llvm_cbe_tmp__73 = (float *)(&llvm_cbe_sum[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%91 = fadd float %%75, %%89, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_230_count);
  llvm_cbe_tmp__74 = (float )((float )(llvm_cbe_tmp__60 + llvm_cbe_tmp__72));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__74, *(int*)(&llvm_cbe_tmp__74));

#ifdef AESL_BC_SIM
  assert(((signed long long )0ull) < 3 && "Write access out of array 'sum' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store float %%91, float* %%90, align 4, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_231_count);
  *llvm_cbe_tmp__73 = llvm_cbe_tmp__74;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", llvm_cbe_tmp__74);
  llvm_cbe_tmp__38__PHI_TEMPORARY = (float )llvm_cbe_tmp__74;   /* for PHI node */
  llvm_cbe_tmp__39__PHI_TEMPORARY = (float )llvm_cbe_tmp__74;   /* for PHI node */
  llvm_cbe_tmp__40__PHI_TEMPORARY = (float )llvm_cbe_tmp__74;   /* for PHI node */
  llvm_cbe_tmp__41__PHI_TEMPORARY = (float )llvm_cbe_tmp__74;   /* for PHI node */
  goto llvm_cbe__2e_preheader11_2e__2e_preheader11_2e_split_crit_edge;

  } while (1); /* end of syntactic loop '.preheader11' */
llvm_cbe_tmp__79:
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = trunc i32 %%45 to i8, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_155_count);
  llvm_cbe_tmp__42 = (unsigned char )((unsigned char )llvm_cbe_tmp__37&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__42);
if (AESL_DEBUG_TRACE)
printf("\n  %%phitmp = select i1 %%52, i8 0, i8 %%53, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_phitmp_count);
  llvm_cbe_phitmp = (unsigned char )(((((signed int )llvm_cbe_tmp__37) < ((signed int )0u))) ? ((unsigned char )((unsigned char )0)) : ((unsigned char )llvm_cbe_tmp__42));
if (AESL_DEBUG_TRACE)
printf("\nphitmp = 0x%X\n", llvm_cbe_phitmp);
  llvm_cbe_tmp__43__PHI_TEMPORARY = (unsigned char )llvm_cbe_phitmp;   /* for PHI node */
  goto llvm_cbe_tmp__78;

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.preheader14' */
llvm_cbe_tmp__77:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @applyConvolution}\n");
  return;
}

