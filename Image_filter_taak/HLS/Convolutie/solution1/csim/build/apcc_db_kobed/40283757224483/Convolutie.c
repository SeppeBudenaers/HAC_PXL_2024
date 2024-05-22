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
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
   char *llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
   char *llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
  float *llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  float *llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  float *llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  float *llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  float *llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  float *llvm_cbe_tmp__8;
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
  static  unsigned long long aesl_llvm_cbe_storemerge10_count = 0;
  unsigned int llvm_cbe_storemerge10;
  unsigned int llvm_cbe_storemerge10__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  unsigned int llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  unsigned int llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge19_count = 0;
  unsigned int llvm_cbe_storemerge19;
  unsigned int llvm_cbe_storemerge19__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  unsigned int llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  unsigned int llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  unsigned int llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  unsigned int llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  unsigned long long llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
   char *llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  unsigned char llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  unsigned int llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  float llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  unsigned long long llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
   char *llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  unsigned char llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  unsigned int llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  float llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  float llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  float llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  unsigned int llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  unsigned long long llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
   char *llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  unsigned char llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  unsigned int llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  float llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  float llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  float llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  unsigned int llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  unsigned int llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  unsigned int llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  unsigned long long llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
   char *llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  unsigned char llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  unsigned int llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  float llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  float llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  unsigned long long llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
   char *llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  unsigned char llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  unsigned int llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  float llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  float llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  float llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  unsigned int llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  unsigned long long llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
   char *llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  unsigned char llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  unsigned int llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  float llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  float llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  float llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  unsigned int llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  unsigned int llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  unsigned int llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  unsigned int llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  unsigned long long llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
   char *llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  unsigned char llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  unsigned int llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  float llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  float llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;
  unsigned long long llvm_cbe_tmp__69;
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
   char *llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  unsigned char llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  unsigned int llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  float llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  float llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
  float llvm_cbe_tmp__75;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  unsigned int llvm_cbe_tmp__76;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  unsigned long long llvm_cbe_tmp__77;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
   char *llvm_cbe_tmp__78;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  unsigned char llvm_cbe_tmp__79;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  unsigned int llvm_cbe_tmp__80;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  float llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
  float llvm_cbe_tmp__82;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
  float llvm_cbe_tmp__83;
  static  unsigned long long aesl_llvm_cbe_234_count = 0;
  static  unsigned long long aesl_llvm_cbe_235_count = 0;
  static  unsigned long long aesl_llvm_cbe_236_count = 0;
  static  unsigned long long aesl_llvm_cbe_237_count = 0;
  static  unsigned long long aesl_llvm_cbe_238_count = 0;
  static  unsigned long long aesl_llvm_cbe_239_count = 0;
  static  unsigned long long aesl_llvm_cbe_240_count = 0;
  static  unsigned long long aesl_llvm_cbe_241_count = 0;
  static  unsigned long long aesl_llvm_cbe_242_count = 0;
  static  unsigned long long aesl_llvm_cbe_243_count = 0;
  static  unsigned long long aesl_llvm_cbe_244_count = 0;
  static  unsigned long long aesl_llvm_cbe_245_count = 0;
  static  unsigned long long aesl_llvm_cbe_246_count = 0;
  static  unsigned long long aesl_llvm_cbe_247_count = 0;
  unsigned int llvm_cbe_tmp__84;
  static  unsigned long long aesl_llvm_cbe_248_count = 0;
  static  unsigned long long aesl_llvm_cbe_249_count = 0;
  static  unsigned long long aesl_llvm_cbe_250_count = 0;
  static  unsigned long long aesl_llvm_cbe_251_count = 0;
  static  unsigned long long aesl_llvm_cbe_252_count = 0;
  static  unsigned long long aesl_llvm_cbe_253_count = 0;
  static  unsigned long long aesl_llvm_cbe_254_count = 0;
  static  unsigned long long aesl_llvm_cbe_255_count = 0;
  unsigned char llvm_cbe_tmp__85;
  static  unsigned long long aesl_llvm_cbe_phitmp_count = 0;
  unsigned char llvm_cbe_phitmp;
  static  unsigned long long aesl_llvm_cbe_256_count = 0;
  static  unsigned long long aesl_llvm_cbe_257_count = 0;
  unsigned char llvm_cbe_tmp__86;
  unsigned char llvm_cbe_tmp__86__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_258_count = 0;
  unsigned int llvm_cbe_tmp__87;
  static  unsigned long long aesl_llvm_cbe_259_count = 0;
  unsigned long long llvm_cbe_tmp__88;
  static  unsigned long long aesl_llvm_cbe_260_count = 0;
   char *llvm_cbe_tmp__89;
  static  unsigned long long aesl_llvm_cbe_261_count = 0;
  static  unsigned long long aesl_llvm_cbe_262_count = 0;
  unsigned int llvm_cbe_tmp__90;
  static  unsigned long long aesl_llvm_cbe_263_count = 0;
  static  unsigned long long aesl_llvm_cbe_264_count = 0;
  static  unsigned long long aesl_llvm_cbe_265_count = 0;
  static  unsigned long long aesl_llvm_cbe_266_count = 0;
  static  unsigned long long aesl_llvm_cbe_267_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond12_count = 0;
  static  unsigned long long aesl_llvm_cbe_268_count = 0;
  static  unsigned long long aesl_llvm_cbe_269_count = 0;
  static  unsigned long long aesl_llvm_cbe_270_count = 0;
  static  unsigned long long aesl_llvm_cbe_271_count = 0;
  static  unsigned long long aesl_llvm_cbe_272_count = 0;
  static  unsigned long long aesl_llvm_cbe_273_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond13_count = 0;
  static  unsigned long long aesl_llvm_cbe_274_count = 0;
  static  unsigned long long aesl_llvm_cbe_275_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @applyConvolution\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = bitcast [3 x [3 x float]]* %%kernel to i8*, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_6_count);
  llvm_cbe_tmp__1 = ( char *)(( char *)(&llvm_cbe_kernel));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = call i8* @memset(i8* %%1, i32 0, i64 36 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_7_count);
  ( char *)memset(( char *)llvm_cbe_tmp__1, 0u, 36ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%I64X",36ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__2);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 0, i64 0, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_8_count);
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
printf("\n  store float 1.000000e+00, float* %%3, align 16, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_9_count);
  *llvm_cbe_tmp__3 = 0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 0, i64 2, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_10_count);
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
printf("\n  store float -1.000000e+00, float* %%4, align 8, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_11_count);
  *llvm_cbe_tmp__4 = -0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", -0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 1, i64 0, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_12_count);
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
printf("\n  store float 1.000000e+00, float* %%5, align 4, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_13_count);
  *llvm_cbe_tmp__5 = 0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 1, i64 2, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_14_count);
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
printf("\n  store float -1.000000e+00, float* %%6, align 4, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_15_count);
  *llvm_cbe_tmp__6 = -0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", -0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 2, i64 0, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_16_count);
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
printf("\n  store float 1.000000e+00, float* %%7, align 8, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_17_count);
  *llvm_cbe_tmp__7 = 0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", 0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr [3 x [3 x float]]* %%kernel, i64 0, i64 2, i64 2, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_18_count);
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
printf("\n  store float -1.000000e+00, float* %%8, align 8, !dbg !4 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_19_count);
  *llvm_cbe_tmp__8 = -0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %f\n", -0x1p0);
  llvm_cbe_storemerge10__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  goto llvm_cbe__2e_preheader8;

  do {     /* Syntactic loop '.preheader8' to make GCC happy */
llvm_cbe__2e_preheader8:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge10 = phi i32 [ 1, %%0 ], [ %%59, %%95  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_storemerge10_count);
  llvm_cbe_storemerge10 = (unsigned int )llvm_cbe_storemerge10__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge10 = 0x%X",llvm_cbe_storemerge10);
printf("\n = 0x%X",1u);
printf("\n = 0x%X",llvm_cbe_tmp__59);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = shl i32 %%storemerge10, 2, !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_50_count);
  llvm_cbe_tmp__9 = (unsigned int )llvm_cbe_storemerge10 << 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__9);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = add i32 %%9, -5, !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_51_count);
  llvm_cbe_tmp__10 = (unsigned int )((unsigned int )(llvm_cbe_tmp__9&4294967295ull)) + ((unsigned int )(4294967291u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__10&4294967295ull)));
  llvm_cbe_storemerge19__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  goto llvm_cbe__2e_preheader5;

llvm_cbe_tmp__91:
  if (((llvm_cbe_tmp__59&4294967295U) == (5u&4294967295U))) {
    goto llvm_cbe_tmp__92;
  } else {
    llvm_cbe_storemerge10__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__59;   /* for PHI node */
    goto llvm_cbe__2e_preheader8;
  }

  do {     /* Syntactic loop '.preheader5' to make GCC happy */
llvm_cbe__2e_preheader5:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge19 = phi i32 [ 1, %%.preheader8 ], [ %%94, %%89  for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_storemerge19_count);
  llvm_cbe_storemerge19 = (unsigned int )llvm_cbe_storemerge19__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge19 = 0x%X",llvm_cbe_storemerge19);
printf("\n = 0x%X",1u);
printf("\n = 0x%X",llvm_cbe_tmp__90);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = mul i32 %%storemerge10, 6, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_61_count);
  llvm_cbe_tmp__11 = (unsigned int )((unsigned int )(llvm_cbe_storemerge10&4294967295ull)) * ((unsigned int )(6u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__11&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = add i32 %%11, -6, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_62_count);
  llvm_cbe_tmp__12 = (unsigned int )((unsigned int )(llvm_cbe_tmp__11&4294967295ull)) + ((unsigned int )(4294967290u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__12&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = add i32 %%12, %%storemerge19, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_63_count);
  llvm_cbe_tmp__13 = (unsigned int )((unsigned int )(llvm_cbe_tmp__12&4294967295ull)) + ((unsigned int )(llvm_cbe_storemerge19&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__13&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = add i32 %%13, -1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_66_count);
  llvm_cbe_tmp__14 = (unsigned int )((unsigned int )(llvm_cbe_tmp__13&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__14&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = sext i32 %%14 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_67_count);
  llvm_cbe_tmp__15 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__14);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__15);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds i8* %%image, i64 %%15, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_68_count);
  llvm_cbe_tmp__16 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__15))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__15));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = load i8* %%16, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_69_count);
  llvm_cbe_tmp__17 = (unsigned char )*llvm_cbe_tmp__16;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__17);
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = zext i8 %%17 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_70_count);
  llvm_cbe_tmp__18 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__17&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__18);
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = sitofp i32 %%18 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_71_count);
  llvm_cbe_tmp__19 = (float )((float )(signed int )llvm_cbe_tmp__18);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__19, *(int*)(&llvm_cbe_tmp__19));
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = sext i32 %%13 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_82_count);
  llvm_cbe_tmp__20 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds i8* %%image, i64 %%20, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_83_count);
  llvm_cbe_tmp__21 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__20))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__20));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = load i8* %%21, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_84_count);
  llvm_cbe_tmp__22 = (unsigned char )*llvm_cbe_tmp__21;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__22);
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = zext i8 %%22 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_85_count);
  llvm_cbe_tmp__23 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__22&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__23);
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = sitofp i32 %%23 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_86_count);
  llvm_cbe_tmp__24 = (float )((float )(signed int )llvm_cbe_tmp__23);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__24, *(int*)(&llvm_cbe_tmp__24));
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = fmul float %%24, 0.000000e+00, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_87_count);
  llvm_cbe_tmp__25 = (float )((float )(llvm_cbe_tmp__24 * 0x0p0));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__25, *(int*)(&llvm_cbe_tmp__25));
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = fadd float %%19, %%25, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_88_count);
  llvm_cbe_tmp__26 = (float )((float )(llvm_cbe_tmp__19 + llvm_cbe_tmp__25));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__26, *(int*)(&llvm_cbe_tmp__26));
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = add i32 %%13, 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_99_count);
  llvm_cbe_tmp__27 = (unsigned int )((unsigned int )(llvm_cbe_tmp__13&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__27&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = sext i32 %%27 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_100_count);
  llvm_cbe_tmp__28 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__27);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__28);
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = getelementptr inbounds i8* %%image, i64 %%28, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_101_count);
  llvm_cbe_tmp__29 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__28))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__28));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = load i8* %%29, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_102_count);
  llvm_cbe_tmp__30 = (unsigned char )*llvm_cbe_tmp__29;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__30);
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = zext i8 %%30 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_103_count);
  llvm_cbe_tmp__31 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__30&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__31);
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = sitofp i32 %%31 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_104_count);
  llvm_cbe_tmp__32 = (float )((float )(signed int )llvm_cbe_tmp__31);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__32, *(int*)(&llvm_cbe_tmp__32));
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = fmul float %%32, -1.000000e+00, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_105_count);
  llvm_cbe_tmp__33 = (float )((float )(llvm_cbe_tmp__32 * -0x1p0));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__33, *(int*)(&llvm_cbe_tmp__33));
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = fadd float %%26, %%33, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_106_count);
  llvm_cbe_tmp__34 = (float )((float )(llvm_cbe_tmp__26 + llvm_cbe_tmp__33));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__34, *(int*)(&llvm_cbe_tmp__34));
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = mul nsw i32 %%storemerge10, 6, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_124_count);
  llvm_cbe_tmp__35 = (unsigned int )((unsigned int )(llvm_cbe_storemerge10&4294967295ull)) * ((unsigned int )(6u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__35&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = add i32 %%35, %%storemerge19, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_125_count);
  llvm_cbe_tmp__36 = (unsigned int )((unsigned int )(llvm_cbe_tmp__35&4294967295ull)) + ((unsigned int )(llvm_cbe_storemerge19&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__36&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = add i32 %%36, -1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_128_count);
  llvm_cbe_tmp__37 = (unsigned int )((unsigned int )(llvm_cbe_tmp__36&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__37&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = sext i32 %%37 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_129_count);
  llvm_cbe_tmp__38 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__37);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__38);
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = getelementptr inbounds i8* %%image, i64 %%38, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_130_count);
  llvm_cbe_tmp__39 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__38))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__38));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = load i8* %%39, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_131_count);
  llvm_cbe_tmp__40 = (unsigned char )*llvm_cbe_tmp__39;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__40);
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = zext i8 %%40 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_132_count);
  llvm_cbe_tmp__41 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__40&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__41);
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = sitofp i32 %%41 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_133_count);
  llvm_cbe_tmp__42 = (float )((float )(signed int )llvm_cbe_tmp__41);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__42, *(int*)(&llvm_cbe_tmp__42));
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = fadd float %%34, %%42, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_134_count);
  llvm_cbe_tmp__43 = (float )((float )(llvm_cbe_tmp__34 + llvm_cbe_tmp__42));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__43, *(int*)(&llvm_cbe_tmp__43));
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = sext i32 %%36 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_145_count);
  llvm_cbe_tmp__44 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__44);
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = getelementptr inbounds i8* %%image, i64 %%44, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_146_count);
  llvm_cbe_tmp__45 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__44))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__44));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = load i8* %%45, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_147_count);
  llvm_cbe_tmp__46 = (unsigned char )*llvm_cbe_tmp__45;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__46);
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = zext i8 %%46 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_148_count);
  llvm_cbe_tmp__47 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__46&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n  %%48 = sitofp i32 %%47 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_149_count);
  llvm_cbe_tmp__48 = (float )((float )(signed int )llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__48, *(int*)(&llvm_cbe_tmp__48));
if (AESL_DEBUG_TRACE)
printf("\n  %%49 = fmul float %%48, 0.000000e+00, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_150_count);
  llvm_cbe_tmp__49 = (float )((float )(llvm_cbe_tmp__48 * 0x0p0));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__49, *(int*)(&llvm_cbe_tmp__49));
if (AESL_DEBUG_TRACE)
printf("\n  %%50 = fadd float %%43, %%49, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_151_count);
  llvm_cbe_tmp__50 = (float )((float )(llvm_cbe_tmp__43 + llvm_cbe_tmp__49));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__50, *(int*)(&llvm_cbe_tmp__50));
if (AESL_DEBUG_TRACE)
printf("\n  %%51 = add i32 %%36, 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_162_count);
  llvm_cbe_tmp__51 = (unsigned int )((unsigned int )(llvm_cbe_tmp__36&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__51&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%52 = sext i32 %%51 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_163_count);
  llvm_cbe_tmp__52 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__51);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__52);
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = getelementptr inbounds i8* %%image, i64 %%52, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_164_count);
  llvm_cbe_tmp__53 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__52))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__52));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = load i8* %%53, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_165_count);
  llvm_cbe_tmp__54 = (unsigned char )*llvm_cbe_tmp__53;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__54);
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = zext i8 %%54 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_166_count);
  llvm_cbe_tmp__55 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__54&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__55);
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = sitofp i32 %%55 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_167_count);
  llvm_cbe_tmp__56 = (float )((float )(signed int )llvm_cbe_tmp__55);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__56, *(int*)(&llvm_cbe_tmp__56));
if (AESL_DEBUG_TRACE)
printf("\n  %%57 = fmul float %%56, -1.000000e+00, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_168_count);
  llvm_cbe_tmp__57 = (float )((float )(llvm_cbe_tmp__56 * -0x1p0));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__57, *(int*)(&llvm_cbe_tmp__57));
if (AESL_DEBUG_TRACE)
printf("\n  %%58 = fadd float %%50, %%57, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_169_count);
  llvm_cbe_tmp__58 = (float )((float )(llvm_cbe_tmp__50 + llvm_cbe_tmp__57));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__58, *(int*)(&llvm_cbe_tmp__58));
if (AESL_DEBUG_TRACE)
printf("\n  %%59 = add nsw i32 %%storemerge10, 1, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_187_count);
  llvm_cbe_tmp__59 = (unsigned int )((unsigned int )(llvm_cbe_storemerge10&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__59&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%60 = mul nsw i32 %%59, 6, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_188_count);
  llvm_cbe_tmp__60 = (unsigned int )((unsigned int )(llvm_cbe_tmp__59&4294967295ull)) * ((unsigned int )(6u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__60&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%61 = add i32 %%60, %%storemerge19, !dbg !5 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_189_count);
  llvm_cbe_tmp__61 = (unsigned int )((unsigned int )(llvm_cbe_tmp__60&4294967295ull)) + ((unsigned int )(llvm_cbe_storemerge19&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__61&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = add i32 %%61, -1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_192_count);
  llvm_cbe_tmp__62 = (unsigned int )((unsigned int )(llvm_cbe_tmp__61&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__62&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%63 = sext i32 %%62 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_193_count);
  llvm_cbe_tmp__63 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__62);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__63);
if (AESL_DEBUG_TRACE)
printf("\n  %%64 = getelementptr inbounds i8* %%image, i64 %%63, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_194_count);
  llvm_cbe_tmp__64 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__63))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__63));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%65 = load i8* %%64, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_195_count);
  llvm_cbe_tmp__65 = (unsigned char )*llvm_cbe_tmp__64;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__65);
if (AESL_DEBUG_TRACE)
printf("\n  %%66 = zext i8 %%65 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_196_count);
  llvm_cbe_tmp__66 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__65&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__66);
if (AESL_DEBUG_TRACE)
printf("\n  %%67 = sitofp i32 %%66 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_197_count);
  llvm_cbe_tmp__67 = (float )((float )(signed int )llvm_cbe_tmp__66);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__67, *(int*)(&llvm_cbe_tmp__67));
if (AESL_DEBUG_TRACE)
printf("\n  %%68 = fadd float %%58, %%67, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_198_count);
  llvm_cbe_tmp__68 = (float )((float )(llvm_cbe_tmp__58 + llvm_cbe_tmp__67));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__68, *(int*)(&llvm_cbe_tmp__68));
if (AESL_DEBUG_TRACE)
printf("\n  %%69 = sext i32 %%61 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_209_count);
  llvm_cbe_tmp__69 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__61);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__69);
if (AESL_DEBUG_TRACE)
printf("\n  %%70 = getelementptr inbounds i8* %%image, i64 %%69, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_210_count);
  llvm_cbe_tmp__70 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__69))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__69));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%71 = load i8* %%70, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_211_count);
  llvm_cbe_tmp__71 = (unsigned char )*llvm_cbe_tmp__70;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__71);
if (AESL_DEBUG_TRACE)
printf("\n  %%72 = zext i8 %%71 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_212_count);
  llvm_cbe_tmp__72 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__71&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__72);
if (AESL_DEBUG_TRACE)
printf("\n  %%73 = sitofp i32 %%72 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_213_count);
  llvm_cbe_tmp__73 = (float )((float )(signed int )llvm_cbe_tmp__72);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__73, *(int*)(&llvm_cbe_tmp__73));
if (AESL_DEBUG_TRACE)
printf("\n  %%74 = fmul float %%73, 0.000000e+00, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_214_count);
  llvm_cbe_tmp__74 = (float )((float )(llvm_cbe_tmp__73 * 0x0p0));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__74, *(int*)(&llvm_cbe_tmp__74));
if (AESL_DEBUG_TRACE)
printf("\n  %%75 = fadd float %%68, %%74, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_215_count);
  llvm_cbe_tmp__75 = (float )((float )(llvm_cbe_tmp__68 + llvm_cbe_tmp__74));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__75, *(int*)(&llvm_cbe_tmp__75));
if (AESL_DEBUG_TRACE)
printf("\n  %%76 = add i32 %%61, 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_226_count);
  llvm_cbe_tmp__76 = (unsigned int )((unsigned int )(llvm_cbe_tmp__61&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__76&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%77 = sext i32 %%76 to i64, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_227_count);
  llvm_cbe_tmp__77 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__76);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__77);
if (AESL_DEBUG_TRACE)
printf("\n  %%78 = getelementptr inbounds i8* %%image, i64 %%77, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_228_count);
  llvm_cbe_tmp__78 = ( char *)(&llvm_cbe_image[(((signed long long )llvm_cbe_tmp__77))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__77));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%79 = load i8* %%78, align 1, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_229_count);
  llvm_cbe_tmp__79 = (unsigned char )*llvm_cbe_tmp__78;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__79);
if (AESL_DEBUG_TRACE)
printf("\n  %%80 = zext i8 %%79 to i32, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_230_count);
  llvm_cbe_tmp__80 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__79&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__80);
if (AESL_DEBUG_TRACE)
printf("\n  %%81 = sitofp i32 %%80 to float, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_231_count);
  llvm_cbe_tmp__81 = (float )((float )(signed int )llvm_cbe_tmp__80);
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__81, *(int*)(&llvm_cbe_tmp__81));
if (AESL_DEBUG_TRACE)
printf("\n  %%82 = fmul float %%81, -1.000000e+00, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_232_count);
  llvm_cbe_tmp__82 = (float )((float )(llvm_cbe_tmp__81 * -0x1p0));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__82, *(int*)(&llvm_cbe_tmp__82));
if (AESL_DEBUG_TRACE)
printf("\n  %%83 = fadd float %%75, %%82, !dbg !2 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_233_count);
  llvm_cbe_tmp__83 = (float )((float )(llvm_cbe_tmp__75 + llvm_cbe_tmp__82));
if (AESL_DEBUG_TRACE)
printf("\n = %f,  0x%x\n", llvm_cbe_tmp__83, *(int*)(&llvm_cbe_tmp__83));
if (AESL_DEBUG_TRACE)
printf("\n  %%84 = fptosi float %%83 to i32, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_247_count);
  llvm_cbe_tmp__84 = (unsigned int )((signed int )llvm_cbe_tmp__83&4294967295U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__84);
  if ((((signed int )llvm_cbe_tmp__84) > ((signed int )127u))) {
    llvm_cbe_tmp__86__PHI_TEMPORARY = (unsigned char )((unsigned char )127);   /* for PHI node */
    goto llvm_cbe_tmp__93;
  } else {
    goto llvm_cbe_tmp__94;
  }

llvm_cbe_tmp__93:
if (AESL_DEBUG_TRACE)
printf("\n  %%90 = phi i8 [ %%phitmp, %%86 ], [ 127, %%.preheader5 ], !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_257_count);
  llvm_cbe_tmp__86 = (unsigned char )llvm_cbe_tmp__86__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__86);
printf("\nphitmp = 0x%X",llvm_cbe_phitmp);
printf("\n = 0x%X",((unsigned char )127));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%91 = add i32 %%10, %%storemerge19, !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_258_count);
  llvm_cbe_tmp__87 = (unsigned int )((unsigned int )(llvm_cbe_tmp__10&4294967295ull)) + ((unsigned int )(llvm_cbe_storemerge19&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__87&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%92 = sext i32 %%91 to i64, !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_259_count);
  llvm_cbe_tmp__88 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__87);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__88);
if (AESL_DEBUG_TRACE)
printf("\n  %%93 = getelementptr inbounds i8* %%output, i64 %%92, !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_260_count);
  llvm_cbe_tmp__89 = ( char *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__88))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__88));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%90, i8* %%93, align 1, !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_261_count);
  *llvm_cbe_tmp__89 = llvm_cbe_tmp__86;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__86);
if (AESL_DEBUG_TRACE)
printf("\n  %%94 = add nsw i32 %%storemerge19, 1, !dbg !6 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_262_count);
  llvm_cbe_tmp__90 = (unsigned int )((unsigned int )(llvm_cbe_storemerge19&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__90&4294967295ull)));
  if (((llvm_cbe_tmp__90&4294967295U) == (5u&4294967295U))) {
    goto llvm_cbe_tmp__91;
  } else {
    llvm_cbe_storemerge19__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__90;   /* for PHI node */
    goto llvm_cbe__2e_preheader5;
  }

llvm_cbe_tmp__94:
if (AESL_DEBUG_TRACE)
printf("\n  %%88 = trunc i32 %%84 to i8, !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_255_count);
  llvm_cbe_tmp__85 = (unsigned char )((unsigned char )llvm_cbe_tmp__84&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__85);
if (AESL_DEBUG_TRACE)
printf("\n  %%phitmp = select i1 %%87, i8 -128, i8 %%88, !dbg !3 for 0x%I64xth hint within @applyConvolution  --> \n", ++aesl_llvm_cbe_phitmp_count);
  llvm_cbe_phitmp = (unsigned char )(((((signed int )llvm_cbe_tmp__84) < ((signed int )4294967168u))) ? ((unsigned char )((unsigned char )128u)) : ((unsigned char )llvm_cbe_tmp__85));
if (AESL_DEBUG_TRACE)
printf("\nphitmp = 0x%X\n", llvm_cbe_phitmp);
  llvm_cbe_tmp__86__PHI_TEMPORARY = (unsigned char )llvm_cbe_phitmp;   /* for PHI node */
  goto llvm_cbe_tmp__93;

  } while (1); /* end of syntactic loop '.preheader5' */
  } while (1); /* end of syntactic loop '.preheader8' */
llvm_cbe_tmp__92:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @applyConvolution}\n");
  return;
}

