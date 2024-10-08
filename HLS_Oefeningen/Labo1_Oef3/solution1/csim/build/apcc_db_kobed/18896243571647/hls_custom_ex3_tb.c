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

/* External Global Variable Declarations */

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
signed int main(void);
void CombLogic_Custom(bool , bool , bool , bool *, bool *);


/* Global Variable Definitions and Initialization */
static bool aesl_internal_main_OC_TB_GOLDEN_RESULT2[8] = { 0, 1, 1, 1, 0, 1, 1, 1 };
static  char aesl_internal__OC_str3[21] = "Testbench Success!\n\r";
static  char aesl_internal__OC_str[34] = "Error at row %d of truth table \n\r";
static  char aesl_internal__OC_str2[43] = "d[%d] = %d = TB_GOLDEN_RESULT2[%d] = %d \n\r";
static  char aesl_internal__OC_str4[21] = "Testbench Failure!\n\r";
static bool aesl_internal_main_OC_TB_GOLDEN_RESULT1[8] = { 0, 1, 1, 0, 0, 0, 1, 0 };
static  char aesl_internal__OC_str1[43] = "d[%d] = %d = TB_GOLDEN_RESULT1[%d] = %d \n\r";


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

signed int main(void) {
  static  unsigned long long aesl_llvm_cbe_LED3_TB_count = 0;
  bool llvm_cbe_LED3_TB[8];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_LED2_TB_count = 0;
  bool llvm_cbe_LED2_TB[8];    /* Address-exposed local */
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
  bool *llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  bool *llvm_cbe_tmp__2;
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
  bool *llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  bool *llvm_cbe_tmp__4;
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
  bool *llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  bool *llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  bool *llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  bool *llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
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
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
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
  bool *llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  bool *llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
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
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  bool *llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  bool *llvm_cbe_tmp__12;
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
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
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
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  bool *llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  bool *llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
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
  bool *llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  bool *llvm_cbe_tmp__16;
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
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
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
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge14_count = 0;
  unsigned int llvm_cbe_storemerge14;
  unsigned int llvm_cbe_storemerge14__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  unsigned int llvm_cbe_tmp__17;
  unsigned int llvm_cbe_tmp__17__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  unsigned long long llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  bool *llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  bool llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  bool *llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  bool llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  bool llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  unsigned int llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  unsigned int llvm_cbe_tmp__25;
  unsigned int llvm_cbe_tmp__25__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  bool *llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
  bool llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
  bool *llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_234_count = 0;
  bool llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_235_count = 0;
  bool llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_236_count = 0;
  static  unsigned long long aesl_llvm_cbe_237_count = 0;
  unsigned int llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_238_count = 0;
  static  unsigned long long aesl_llvm_cbe_239_count = 0;
  static  unsigned long long aesl_llvm_cbe_240_count = 0;
  static  unsigned long long aesl_llvm_cbe_241_count = 0;
  static  unsigned long long aesl_llvm_cbe_242_count = 0;
  unsigned int llvm_cbe_tmp__32;
  unsigned int llvm_cbe_tmp__32__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_243_count = 0;
  bool llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_244_count = 0;
  unsigned int llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_245_count = 0;
  unsigned int llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_246_count = 0;
  unsigned int llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_247_count = 0;
  bool llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_248_count = 0;
  unsigned int llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_249_count = 0;
  unsigned int llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_250_count = 0;
  unsigned int llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_251_count = 0;
  unsigned int llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_252_count = 0;
  static  unsigned long long aesl_llvm_cbe_253_count = 0;
  static  unsigned long long aesl_llvm_cbe_254_count = 0;
  static  unsigned long long aesl_llvm_cbe_255_count = 0;
  static  unsigned long long aesl_llvm_cbe_256_count = 0;
  static  unsigned long long aesl_llvm_cbe_257_count = 0;
  static  unsigned long long aesl_llvm_cbe_258_count = 0;
  static  unsigned long long aesl_llvm_cbe_259_count = 0;
  static  unsigned long long aesl_llvm_cbe_260_count = 0;
  static  unsigned long long aesl_llvm_cbe_261_count = 0;
  static  unsigned long long aesl_llvm_cbe_262_count = 0;
  static  unsigned long long aesl_llvm_cbe_263_count = 0;
  static  unsigned long long aesl_llvm_cbe_264_count = 0;
  static  unsigned long long aesl_llvm_cbe_265_count = 0;
  static  unsigned long long aesl_llvm_cbe_266_count = 0;
  static  unsigned long long aesl_llvm_cbe_267_count = 0;
  static  unsigned long long aesl_llvm_cbe_268_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_269_count = 0;
  static  unsigned long long aesl_llvm_cbe_270_count = 0;
  static  unsigned long long aesl_llvm_cbe_271_count = 0;
  static  unsigned long long aesl_llvm_cbe_272_count = 0;
  unsigned int llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_273_count = 0;
  static  unsigned long long aesl_llvm_cbe_274_count = 0;
  unsigned int llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_275_count = 0;
  static  unsigned long long aesl_llvm_cbe_276_count = 0;

  CODE_FOR_MAIN();
const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @main\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%0 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 0, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_30_count);
  llvm_cbe_tmp__1 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 0, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_31_count);
  llvm_cbe_tmp__2 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @CombLogic_Custom(i1 zeroext false, i1 zeroext false, i1 zeroext false, i1* %%0, i1* %%1) nounwind, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_32_count);
  CombLogic_Custom(0, 0, 0, (bool *)llvm_cbe_tmp__1, (bool *)llvm_cbe_tmp__2);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",0);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 1, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_47_count);
  llvm_cbe_tmp__3 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 1, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_48_count);
  llvm_cbe_tmp__4 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @CombLogic_Custom(i1 zeroext true, i1 zeroext false, i1 zeroext false, i1* %%2, i1* %%3) nounwind, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_49_count);
  CombLogic_Custom(1, 0, 0, (bool *)llvm_cbe_tmp__3, (bool *)llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",0);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 2, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_72_count);
  llvm_cbe_tmp__5 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 2, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_73_count);
  llvm_cbe_tmp__6 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @CombLogic_Custom(i1 zeroext false, i1 zeroext true, i1 zeroext false, i1* %%4, i1* %%5) nounwind, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_74_count);
  CombLogic_Custom(0, 1, 0, (bool *)llvm_cbe_tmp__5, (bool *)llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",0);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 3, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_89_count);
  llvm_cbe_tmp__7 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 3, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_90_count);
  llvm_cbe_tmp__8 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @CombLogic_Custom(i1 zeroext true, i1 zeroext true, i1 zeroext false, i1* %%6, i1* %%7) nounwind, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_91_count);
  CombLogic_Custom(1, 1, 0, (bool *)llvm_cbe_tmp__7, (bool *)llvm_cbe_tmp__8);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",0);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 4, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_122_count);
  llvm_cbe_tmp__9 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 4, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_123_count);
  llvm_cbe_tmp__10 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @CombLogic_Custom(i1 zeroext false, i1 zeroext false, i1 zeroext true, i1* %%8, i1* %%9) nounwind, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_124_count);
  CombLogic_Custom(0, 0, 1, (bool *)llvm_cbe_tmp__9, (bool *)llvm_cbe_tmp__10);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",1);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 5, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_139_count);
  llvm_cbe_tmp__11 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 5, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_140_count);
  llvm_cbe_tmp__12 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @CombLogic_Custom(i1 zeroext true, i1 zeroext false, i1 zeroext true, i1* %%10, i1* %%11) nounwind, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_141_count);
  CombLogic_Custom(1, 0, 1, (bool *)llvm_cbe_tmp__11, (bool *)llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",1);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 6, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_164_count);
  llvm_cbe_tmp__13 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )6ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 6, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_165_count);
  llvm_cbe_tmp__14 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )6ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @CombLogic_Custom(i1 zeroext false, i1 zeroext true, i1 zeroext true, i1* %%12, i1* %%13) nounwind, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_166_count);
  CombLogic_Custom(0, 1, 1, (bool *)llvm_cbe_tmp__13, (bool *)llvm_cbe_tmp__14);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",1);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 7, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_181_count);
  llvm_cbe_tmp__15 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )7ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 7, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_182_count);
  llvm_cbe_tmp__16 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )7ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @CombLogic_Custom(i1 zeroext true, i1 zeroext true, i1 zeroext true, i1* %%14, i1* %%15) nounwind, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_183_count);
  CombLogic_Custom(1, 1, 1, (bool *)llvm_cbe_tmp__15, (bool *)llvm_cbe_tmp__16);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",1);
}
  llvm_cbe_storemerge14__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  llvm_cbe_tmp__17__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__44;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__44:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge14 = phi i32 [ 0, %%.preheader8 ], [ %%45, %%35  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_storemerge14_count);
  llvm_cbe_storemerge14 = (unsigned int )llvm_cbe_storemerge14__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__41);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = phi i32 [ 0, %%.preheader8 ], [ %%36, %%35  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_217_count);
  llvm_cbe_tmp__17 = (unsigned int )llvm_cbe_tmp__17__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__17);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__32);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = sext i32 %%storemerge14 to i64, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_218_count);
  llvm_cbe_tmp__18 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge14);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__18);
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 %%18, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_219_count);
  llvm_cbe_tmp__19 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )llvm_cbe_tmp__18))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__18));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__18) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'LED3_TB' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = load i1* %%19, align 1, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_220_count);
  llvm_cbe_tmp__20 = (bool )((*llvm_cbe_tmp__19)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds [8 x i1]* @aesl_internal_main.TB_GOLDEN_RESULT1, i64 0, i64 %%18, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_221_count);
  llvm_cbe_tmp__21 = (bool *)(&aesl_internal_main_OC_TB_GOLDEN_RESULT1[(((signed long long )llvm_cbe_tmp__18))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__18));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__18) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_main.TB_GOLDEN_RESULT1' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = load i1* %%21, align 1, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_222_count);
  llvm_cbe_tmp__22 = (bool )((*llvm_cbe_tmp__21)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__22);
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = xor i1 %%20, %%22, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_223_count);
  llvm_cbe_tmp__23 = (bool )((llvm_cbe_tmp__20 ^ llvm_cbe_tmp__22)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__23);
  if (llvm_cbe_tmp__23) {
    goto llvm_cbe_tmp__45;
  } else {
    llvm_cbe_tmp__25__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__17;   /* for PHI node */
    goto llvm_cbe_tmp__46;
  }

llvm_cbe_tmp__47:
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = phi i32 [ 1, %%33 ], [ %%27, %%26  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_242_count);
  llvm_cbe_tmp__32 = (unsigned int )llvm_cbe_tmp__32__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__32);
printf("\n = 0x%X",1u);
printf("\n = 0x%X",llvm_cbe_tmp__25);
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__18) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'LED3_TB' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = load i1* %%19, align 1, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_243_count);
  llvm_cbe_tmp__33 = (bool )((*llvm_cbe_tmp__19)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__33);
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = zext i1 %%37 to i32, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_244_count);
  llvm_cbe_tmp__34 = (unsigned int )((unsigned int )(bool )llvm_cbe_tmp__33&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__34);
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = zext i1 %%22 to i32, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_245_count);
  llvm_cbe_tmp__35 = (unsigned int )((unsigned int )(bool )llvm_cbe_tmp__22&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__35);
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([43 x i8]* @aesl_internal_.str1, i64 0, i64 0), i32 %%storemerge14, i32 %%38, i32 %%storemerge14, i32 %%39) nounwind, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_246_count);
  printf(( char *)((&aesl_internal__OC_str1[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 43
#endif
])), llvm_cbe_storemerge14, llvm_cbe_tmp__34, llvm_cbe_storemerge14, llvm_cbe_tmp__35);
if (AESL_DEBUG_TRACE) {
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__34);
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__35);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__36);
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__18) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'LED2_TB' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = load i1* %%28, align 1, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_247_count);
  llvm_cbe_tmp__37 = (bool )((*llvm_cbe_tmp__26)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__37);
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = zext i1 %%41 to i32, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_248_count);
  llvm_cbe_tmp__38 = (unsigned int )((unsigned int )(bool )llvm_cbe_tmp__37&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__38);
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = zext i1 %%31 to i32, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_249_count);
  llvm_cbe_tmp__39 = (unsigned int )((unsigned int )(bool )llvm_cbe_tmp__29&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__39);
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([43 x i8]* @aesl_internal_.str2, i64 0, i64 0), i32 %%storemerge14, i32 %%42, i32 %%storemerge14, i32 %%43) nounwind, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_250_count);
  printf(( char *)((&aesl_internal__OC_str2[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 43
#endif
])), llvm_cbe_storemerge14, llvm_cbe_tmp__38, llvm_cbe_storemerge14, llvm_cbe_tmp__39);
if (AESL_DEBUG_TRACE) {
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__38);
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__39);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__40);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = add nsw i32 %%storemerge14, 1, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_251_count);
  llvm_cbe_tmp__41 = (unsigned int )((unsigned int )(llvm_cbe_storemerge14&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__41&4294967295ull)));
  if (((llvm_cbe_tmp__41&4294967295U) == (8u&4294967295U))) {
    goto llvm_cbe_tmp__48;
  } else {
    llvm_cbe_storemerge14__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__41;   /* for PHI node */
    llvm_cbe_tmp__17__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__32;   /* for PHI node */
    goto llvm_cbe_tmp__44;
  }

llvm_cbe_tmp__46:
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = phi i32 [ 1, %%24 ], [ %%17, %%16  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_230_count);
  llvm_cbe_tmp__25 = (unsigned int )llvm_cbe_tmp__25__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__25);
printf("\n = 0x%X",1u);
printf("\n = 0x%X",llvm_cbe_tmp__17);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 %%18, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_231_count);
  llvm_cbe_tmp__26 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )llvm_cbe_tmp__18))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__18));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__18) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'LED2_TB' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = load i1* %%28, align 1, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_232_count);
  llvm_cbe_tmp__27 = (bool )((*llvm_cbe_tmp__26)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__27);
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = getelementptr inbounds [8 x i1]* @aesl_internal_main.TB_GOLDEN_RESULT2, i64 0, i64 %%18, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_233_count);
  llvm_cbe_tmp__28 = (bool *)(&aesl_internal_main_OC_TB_GOLDEN_RESULT2[(((signed long long )llvm_cbe_tmp__18))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__18));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__18) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_main.TB_GOLDEN_RESULT2' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = load i1* %%30, align 1, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_234_count);
  llvm_cbe_tmp__29 = (bool )((*llvm_cbe_tmp__28)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__29);
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = xor i1 %%29, %%31, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_235_count);
  llvm_cbe_tmp__30 = (bool )((llvm_cbe_tmp__27 ^ llvm_cbe_tmp__29)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__30);
  if (llvm_cbe_tmp__30) {
    goto llvm_cbe_tmp__49;
  } else {
    llvm_cbe_tmp__32__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__25;   /* for PHI node */
    goto llvm_cbe_tmp__47;
  }

llvm_cbe_tmp__45:
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([34 x i8]* @aesl_internal_.str, i64 0, i64 0), i32 %%storemerge14) nounwind, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_225_count);
  printf(( char *)((&aesl_internal__OC_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 34
#endif
])), llvm_cbe_storemerge14);
if (AESL_DEBUG_TRACE) {
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__24);
}
  llvm_cbe_tmp__25__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  goto llvm_cbe_tmp__46;

llvm_cbe_tmp__49:
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([34 x i8]* @aesl_internal_.str, i64 0, i64 0), i32 %%storemerge14) nounwind, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_237_count);
  printf(( char *)((&aesl_internal__OC_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 34
#endif
])), llvm_cbe_storemerge14);
if (AESL_DEBUG_TRACE) {
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__31);
}
  llvm_cbe_tmp__32__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  goto llvm_cbe_tmp__47;

  } while (1); /* end of syntactic loop '' */
llvm_cbe_tmp__48:
  if (((llvm_cbe_tmp__32&4294967295U) == (0u&4294967295U))) {
    goto llvm_cbe_tmp__50;
  } else {
    goto llvm_cbe_tmp__51;
  }

llvm_cbe_tmp__50:
if (AESL_DEBUG_TRACE)
printf("\n  %%49 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([21 x i8]* @aesl_internal_.str3, i64 0, i64 0)) nounwind, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_272_count);
  printf(( char *)((&aesl_internal__OC_str3[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 21
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__42);
}
  goto llvm_cbe_tmp__52;

llvm_cbe_tmp__51:
if (AESL_DEBUG_TRACE)
printf("\n  %%51 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([21 x i8]* @aesl_internal_.str4, i64 0, i64 0)) nounwind, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_274_count);
  printf(( char *)((&aesl_internal__OC_str4[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 21
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__43);
}
  goto llvm_cbe_tmp__52;

llvm_cbe_tmp__52:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @main}\n");
  return llvm_cbe_tmp__32;
}

