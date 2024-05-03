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
void Dobblesteen(bool , bool , bool , bool *, bool *, bool *, bool *);


/* Global Variable Definitions and Initialization */
static bool aesl_internal_main_OC_TB_GOLDEN_RESULT1[8] = { 0, 0, 1, 1, 1, 1, 0, 0 };
static bool aesl_internal_main_OC_TB_GOLDEN_RESULT2[8] = { 0, 1, 0, 1, 1, 1, 0, 0 };
static bool aesl_internal_main_OC_TB_GOLDEN_RESULT3[8] = { 0, 0, 0, 0, 0, 1, 0, 0 };
static bool aesl_internal_main_OC_TB_GOLDEN_RESULT4[8] = { 1, 0, 1, 0, 1, 0, 0, 0 };
static  char aesl_internal__OC_str[34] = "Error at row %d of truth table \n\r";
static  char aesl_internal__OC_str1[42] = "d[%d] = %d = TB_GOLDEN_RESULT[%d] = %d \n\r";
static  char aesl_internal__OC_str2[21] = "Testbench Success!\n\r";
static  char aesl_internal__OC_str3[21] = "Testbench Failure!\n\r";


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
  static  unsigned long long aesl_llvm_cbe_LED4_TB_count = 0;
  bool llvm_cbe_LED4_TB[8];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_LED3_TB_count = 0;
  bool llvm_cbe_LED3_TB[8];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_LED2_TB_count = 0;
  bool llvm_cbe_LED2_TB[8];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_LED1_TB_count = 0;
  bool llvm_cbe_LED1_TB[8];    /* Address-exposed local */
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
  bool *llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  bool *llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  bool *llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  bool *llvm_cbe_tmp__4;
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
  bool *llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  bool *llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  bool *llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  bool *llvm_cbe_tmp__8;
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
  bool *llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  bool *llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  bool *llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  bool *llvm_cbe_tmp__12;
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
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  bool *llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  bool *llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  bool *llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  bool *llvm_cbe_tmp__16;
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
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  bool *llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  bool *llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  bool *llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  bool *llvm_cbe_tmp__20;
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
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  bool *llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  bool *llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  bool *llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  bool *llvm_cbe_tmp__24;
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
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
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
  bool *llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  bool *llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  bool *llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  bool *llvm_cbe_tmp__28;
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
  bool *llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  bool *llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  bool *llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  bool *llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
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
  static  unsigned long long aesl_llvm_cbe_248_count = 0;
  static  unsigned long long aesl_llvm_cbe_249_count = 0;
  static  unsigned long long aesl_llvm_cbe_250_count = 0;
  static  unsigned long long aesl_llvm_cbe_251_count = 0;
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
  static  unsigned long long aesl_llvm_cbe_storemerge14_count = 0;
  unsigned int llvm_cbe_storemerge14;
  unsigned int llvm_cbe_storemerge14__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_269_count = 0;
  unsigned int llvm_cbe_tmp__33;
  unsigned int llvm_cbe_tmp__33__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_270_count = 0;
  unsigned long long llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_271_count = 0;
  bool *llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_272_count = 0;
  bool llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_273_count = 0;
  bool *llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_274_count = 0;
  bool llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_275_count = 0;
  bool llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_276_count = 0;
  static  unsigned long long aesl_llvm_cbe_277_count = 0;
  unsigned int llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_278_count = 0;
  static  unsigned long long aesl_llvm_cbe_279_count = 0;
  static  unsigned long long aesl_llvm_cbe_280_count = 0;
  static  unsigned long long aesl_llvm_cbe_281_count = 0;
  static  unsigned long long aesl_llvm_cbe_282_count = 0;
  unsigned int llvm_cbe_tmp__41;
  unsigned int llvm_cbe_tmp__41__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_283_count = 0;
  bool *llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_284_count = 0;
  bool llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_285_count = 0;
  bool *llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_286_count = 0;
  bool llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_287_count = 0;
  bool llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_288_count = 0;
  static  unsigned long long aesl_llvm_cbe_289_count = 0;
  unsigned int llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_290_count = 0;
  static  unsigned long long aesl_llvm_cbe_291_count = 0;
  static  unsigned long long aesl_llvm_cbe_292_count = 0;
  static  unsigned long long aesl_llvm_cbe_293_count = 0;
  static  unsigned long long aesl_llvm_cbe_294_count = 0;
  unsigned int llvm_cbe_tmp__48;
  unsigned int llvm_cbe_tmp__48__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_295_count = 0;
  bool *llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_296_count = 0;
  bool llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_297_count = 0;
  bool *llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_298_count = 0;
  bool llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_299_count = 0;
  bool llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_300_count = 0;
  static  unsigned long long aesl_llvm_cbe_301_count = 0;
  unsigned int llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_302_count = 0;
  static  unsigned long long aesl_llvm_cbe_303_count = 0;
  static  unsigned long long aesl_llvm_cbe_304_count = 0;
  static  unsigned long long aesl_llvm_cbe_305_count = 0;
  static  unsigned long long aesl_llvm_cbe_306_count = 0;
  unsigned int llvm_cbe_tmp__55;
  unsigned int llvm_cbe_tmp__55__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_307_count = 0;
  bool *llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_308_count = 0;
  bool llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_309_count = 0;
  bool *llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_310_count = 0;
  bool llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_311_count = 0;
  bool llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_312_count = 0;
  static  unsigned long long aesl_llvm_cbe_313_count = 0;
  unsigned int llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_314_count = 0;
  static  unsigned long long aesl_llvm_cbe_315_count = 0;
  static  unsigned long long aesl_llvm_cbe_316_count = 0;
  static  unsigned long long aesl_llvm_cbe_317_count = 0;
  static  unsigned long long aesl_llvm_cbe_318_count = 0;
  unsigned int llvm_cbe_tmp__62;
  unsigned int llvm_cbe_tmp__62__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_319_count = 0;
  bool llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_320_count = 0;
  unsigned int llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_321_count = 0;
  unsigned int llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_322_count = 0;
  unsigned int llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_323_count = 0;
  bool llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_324_count = 0;
  unsigned int llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_325_count = 0;
  unsigned int llvm_cbe_tmp__69;
  static  unsigned long long aesl_llvm_cbe_326_count = 0;
  unsigned int llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_327_count = 0;
  bool llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_328_count = 0;
  unsigned int llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_329_count = 0;
  unsigned int llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_330_count = 0;
  unsigned int llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_331_count = 0;
  bool llvm_cbe_tmp__75;
  static  unsigned long long aesl_llvm_cbe_332_count = 0;
  unsigned int llvm_cbe_tmp__76;
  static  unsigned long long aesl_llvm_cbe_333_count = 0;
  unsigned int llvm_cbe_tmp__77;
  static  unsigned long long aesl_llvm_cbe_334_count = 0;
  unsigned int llvm_cbe_tmp__78;
  static  unsigned long long aesl_llvm_cbe_335_count = 0;
  unsigned int llvm_cbe_tmp__79;
  static  unsigned long long aesl_llvm_cbe_336_count = 0;
  static  unsigned long long aesl_llvm_cbe_337_count = 0;
  static  unsigned long long aesl_llvm_cbe_338_count = 0;
  static  unsigned long long aesl_llvm_cbe_339_count = 0;
  static  unsigned long long aesl_llvm_cbe_340_count = 0;
  static  unsigned long long aesl_llvm_cbe_341_count = 0;
  static  unsigned long long aesl_llvm_cbe_342_count = 0;
  static  unsigned long long aesl_llvm_cbe_343_count = 0;
  static  unsigned long long aesl_llvm_cbe_344_count = 0;
  static  unsigned long long aesl_llvm_cbe_345_count = 0;
  static  unsigned long long aesl_llvm_cbe_346_count = 0;
  static  unsigned long long aesl_llvm_cbe_347_count = 0;
  static  unsigned long long aesl_llvm_cbe_348_count = 0;
  static  unsigned long long aesl_llvm_cbe_349_count = 0;
  static  unsigned long long aesl_llvm_cbe_350_count = 0;
  static  unsigned long long aesl_llvm_cbe_351_count = 0;
  static  unsigned long long aesl_llvm_cbe_352_count = 0;
  static  unsigned long long aesl_llvm_cbe_353_count = 0;
  static  unsigned long long aesl_llvm_cbe_354_count = 0;
  static  unsigned long long aesl_llvm_cbe_355_count = 0;
  static  unsigned long long aesl_llvm_cbe_356_count = 0;
  static  unsigned long long aesl_llvm_cbe_357_count = 0;
  static  unsigned long long aesl_llvm_cbe_358_count = 0;
  static  unsigned long long aesl_llvm_cbe_359_count = 0;
  static  unsigned long long aesl_llvm_cbe_360_count = 0;
  static  unsigned long long aesl_llvm_cbe_361_count = 0;
  static  unsigned long long aesl_llvm_cbe_362_count = 0;
  static  unsigned long long aesl_llvm_cbe_363_count = 0;
  static  unsigned long long aesl_llvm_cbe_364_count = 0;
  static  unsigned long long aesl_llvm_cbe_365_count = 0;
  static  unsigned long long aesl_llvm_cbe_366_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_367_count = 0;
  static  unsigned long long aesl_llvm_cbe_368_count = 0;
  static  unsigned long long aesl_llvm_cbe_369_count = 0;
  static  unsigned long long aesl_llvm_cbe_370_count = 0;
  unsigned int llvm_cbe_tmp__80;
  static  unsigned long long aesl_llvm_cbe_371_count = 0;
  static  unsigned long long aesl_llvm_cbe_372_count = 0;
  unsigned int llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_373_count = 0;
  static  unsigned long long aesl_llvm_cbe_374_count = 0;

  CODE_FOR_MAIN();
const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @main\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%0 = getelementptr inbounds [8 x i1]* %%LED4_TB, i64 0, i64 0, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_36_count);
  llvm_cbe_tmp__1 = (bool *)(&llvm_cbe_LED4_TB[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 0, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_37_count);
  llvm_cbe_tmp__2 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 0, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_38_count);
  llvm_cbe_tmp__3 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds [8 x i1]* %%LED1_TB, i64 0, i64 0, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_39_count);
  llvm_cbe_tmp__4 = (bool *)(&llvm_cbe_LED1_TB[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @Dobblesteen(i1 zeroext false, i1 zeroext false, i1 zeroext false, i1* %%0, i1* %%1, i1* %%2, i1* %%3) nounwind, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_40_count);
  Dobblesteen(0, 0, 0, (bool *)llvm_cbe_tmp__1, (bool *)llvm_cbe_tmp__2, (bool *)llvm_cbe_tmp__3, (bool *)llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",0);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds [8 x i1]* %%LED4_TB, i64 0, i64 1, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_57_count);
  llvm_cbe_tmp__5 = (bool *)(&llvm_cbe_LED4_TB[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 1, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_58_count);
  llvm_cbe_tmp__6 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 1, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_59_count);
  llvm_cbe_tmp__7 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds [8 x i1]* %%LED1_TB, i64 0, i64 1, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_60_count);
  llvm_cbe_tmp__8 = (bool *)(&llvm_cbe_LED1_TB[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @Dobblesteen(i1 zeroext false, i1 zeroext false, i1 zeroext true, i1* %%4, i1* %%5, i1* %%6, i1* %%7) nounwind, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_61_count);
  Dobblesteen(0, 0, 1, (bool *)llvm_cbe_tmp__5, (bool *)llvm_cbe_tmp__6, (bool *)llvm_cbe_tmp__7, (bool *)llvm_cbe_tmp__8);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",1);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds [8 x i1]* %%LED4_TB, i64 0, i64 2, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_86_count);
  llvm_cbe_tmp__9 = (bool *)(&llvm_cbe_LED4_TB[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 2, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_87_count);
  llvm_cbe_tmp__10 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 2, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_88_count);
  llvm_cbe_tmp__11 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds [8 x i1]* %%LED1_TB, i64 0, i64 2, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_89_count);
  llvm_cbe_tmp__12 = (bool *)(&llvm_cbe_LED1_TB[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @Dobblesteen(i1 zeroext false, i1 zeroext true, i1 zeroext false, i1* %%8, i1* %%9, i1* %%10, i1* %%11) nounwind, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_90_count);
  Dobblesteen(0, 1, 0, (bool *)llvm_cbe_tmp__9, (bool *)llvm_cbe_tmp__10, (bool *)llvm_cbe_tmp__11, (bool *)llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",0);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = getelementptr inbounds [8 x i1]* %%LED4_TB, i64 0, i64 3, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_107_count);
  llvm_cbe_tmp__13 = (bool *)(&llvm_cbe_LED4_TB[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 3, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_108_count);
  llvm_cbe_tmp__14 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 3, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_109_count);
  llvm_cbe_tmp__15 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds [8 x i1]* %%LED1_TB, i64 0, i64 3, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_110_count);
  llvm_cbe_tmp__16 = (bool *)(&llvm_cbe_LED1_TB[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @Dobblesteen(i1 zeroext false, i1 zeroext true, i1 zeroext true, i1* %%12, i1* %%13, i1* %%14, i1* %%15) nounwind, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_111_count);
  Dobblesteen(0, 1, 1, (bool *)llvm_cbe_tmp__13, (bool *)llvm_cbe_tmp__14, (bool *)llvm_cbe_tmp__15, (bool *)llvm_cbe_tmp__16);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",1);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds [8 x i1]* %%LED4_TB, i64 0, i64 4, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_144_count);
  llvm_cbe_tmp__17 = (bool *)(&llvm_cbe_LED4_TB[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 4, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_145_count);
  llvm_cbe_tmp__18 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 4, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_146_count);
  llvm_cbe_tmp__19 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = getelementptr inbounds [8 x i1]* %%LED1_TB, i64 0, i64 4, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_147_count);
  llvm_cbe_tmp__20 = (bool *)(&llvm_cbe_LED1_TB[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @Dobblesteen(i1 zeroext true, i1 zeroext false, i1 zeroext false, i1* %%16, i1* %%17, i1* %%18, i1* %%19) nounwind, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_148_count);
  Dobblesteen(1, 0, 0, (bool *)llvm_cbe_tmp__17, (bool *)llvm_cbe_tmp__18, (bool *)llvm_cbe_tmp__19, (bool *)llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",0);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = getelementptr inbounds [8 x i1]* %%LED4_TB, i64 0, i64 5, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_165_count);
  llvm_cbe_tmp__21 = (bool *)(&llvm_cbe_LED4_TB[(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 5, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_166_count);
  llvm_cbe_tmp__22 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 5, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_167_count);
  llvm_cbe_tmp__23 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = getelementptr inbounds [8 x i1]* %%LED1_TB, i64 0, i64 5, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_168_count);
  llvm_cbe_tmp__24 = (bool *)(&llvm_cbe_LED1_TB[(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @Dobblesteen(i1 zeroext true, i1 zeroext false, i1 zeroext true, i1* %%20, i1* %%21, i1* %%22, i1* %%23) nounwind, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_169_count);
  Dobblesteen(1, 0, 1, (bool *)llvm_cbe_tmp__21, (bool *)llvm_cbe_tmp__22, (bool *)llvm_cbe_tmp__23, (bool *)llvm_cbe_tmp__24);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",0);
printf("\nArgument  = 0x%X",1);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = getelementptr inbounds [8 x i1]* %%LED4_TB, i64 0, i64 6, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_194_count);
  llvm_cbe_tmp__25 = (bool *)(&llvm_cbe_LED4_TB[(((signed long long )6ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 6, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_195_count);
  llvm_cbe_tmp__26 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )6ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 6, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_196_count);
  llvm_cbe_tmp__27 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )6ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = getelementptr inbounds [8 x i1]* %%LED1_TB, i64 0, i64 6, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_197_count);
  llvm_cbe_tmp__28 = (bool *)(&llvm_cbe_LED1_TB[(((signed long long )6ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @Dobblesteen(i1 zeroext true, i1 zeroext true, i1 zeroext false, i1* %%24, i1* %%25, i1* %%26, i1* %%27) nounwind, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_198_count);
  Dobblesteen(1, 1, 0, (bool *)llvm_cbe_tmp__25, (bool *)llvm_cbe_tmp__26, (bool *)llvm_cbe_tmp__27, (bool *)llvm_cbe_tmp__28);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",0);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = getelementptr inbounds [8 x i1]* %%LED4_TB, i64 0, i64 7, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_215_count);
  llvm_cbe_tmp__29 = (bool *)(&llvm_cbe_LED4_TB[(((signed long long )7ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 7, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_216_count);
  llvm_cbe_tmp__30 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )7ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 7, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_217_count);
  llvm_cbe_tmp__31 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )7ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = getelementptr inbounds [8 x i1]* %%LED1_TB, i64 0, i64 7, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_218_count);
  llvm_cbe_tmp__32 = (bool *)(&llvm_cbe_LED1_TB[(((signed long long )7ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @Dobblesteen(i1 zeroext true, i1 zeroext true, i1 zeroext true, i1* %%28, i1* %%29, i1* %%30, i1* %%31) nounwind, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_219_count);
  Dobblesteen(1, 1, 1, (bool *)llvm_cbe_tmp__29, (bool *)llvm_cbe_tmp__30, (bool *)llvm_cbe_tmp__31, (bool *)llvm_cbe_tmp__32);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",1);
printf("\nArgument  = 0x%X",1);
}
  llvm_cbe_storemerge14__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  llvm_cbe_tmp__33__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__82;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__82:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge14 = phi i32 [ 0, %%.preheader8 ], [ %%87, %%69  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_storemerge14_count);
  llvm_cbe_storemerge14 = (unsigned int )llvm_cbe_storemerge14__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__79);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = phi i32 [ 0, %%.preheader8 ], [ %%70, %%69  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_269_count);
  llvm_cbe_tmp__33 = (unsigned int )llvm_cbe_tmp__33__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__33);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__62);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = sext i32 %%storemerge14 to i64, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_270_count);
  llvm_cbe_tmp__34 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge14);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__34);
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = getelementptr inbounds [8 x i1]* %%LED4_TB, i64 0, i64 %%34, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_271_count);
  llvm_cbe_tmp__35 = (bool *)(&llvm_cbe_LED4_TB[(((signed long long )llvm_cbe_tmp__34))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__34));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__34) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'LED4_TB' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = load i1* %%35, align 1, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_272_count);
  llvm_cbe_tmp__36 = (bool )((*llvm_cbe_tmp__35)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = getelementptr inbounds [8 x i1]* @aesl_internal_main.TB_GOLDEN_RESULT4, i64 0, i64 %%34, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_273_count);
  llvm_cbe_tmp__37 = (bool *)(&aesl_internal_main_OC_TB_GOLDEN_RESULT4[(((signed long long )llvm_cbe_tmp__34))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__34));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__34) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_main.TB_GOLDEN_RESULT4' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = load i1* %%37, align 1, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_274_count);
  llvm_cbe_tmp__38 = (bool )((*llvm_cbe_tmp__37)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__38);
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = xor i1 %%36, %%38, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_275_count);
  llvm_cbe_tmp__39 = (bool )((llvm_cbe_tmp__36 ^ llvm_cbe_tmp__38)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__39);
  if (llvm_cbe_tmp__39) {
    goto llvm_cbe_tmp__83;
  } else {
    llvm_cbe_tmp__41__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__33;   /* for PHI node */
    goto llvm_cbe_tmp__84;
  }

llvm_cbe_tmp__85:
if (AESL_DEBUG_TRACE)
printf("\n  %%70 = phi i32 [ 1, %%67 ], [ %%61, %%60  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_318_count);
  llvm_cbe_tmp__62 = (unsigned int )llvm_cbe_tmp__62__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__62);
printf("\n = 0x%X",1u);
printf("\n = 0x%X",llvm_cbe_tmp__55);
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__34) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'LED3_TB' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%71 = load i1* %%44, align 1, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_319_count);
  llvm_cbe_tmp__63 = (bool )((*llvm_cbe_tmp__42)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__63);
if (AESL_DEBUG_TRACE)
printf("\n  %%72 = zext i1 %%71 to i32, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_320_count);
  llvm_cbe_tmp__64 = (unsigned int )((unsigned int )(bool )llvm_cbe_tmp__63&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__64);
if (AESL_DEBUG_TRACE)
printf("\n  %%73 = zext i1 %%38 to i32, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_321_count);
  llvm_cbe_tmp__65 = (unsigned int )((unsigned int )(bool )llvm_cbe_tmp__38&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__65);
if (AESL_DEBUG_TRACE)
printf("\n  %%74 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([42 x i8]* @aesl_internal_.str1, i64 0, i64 0), i32 %%storemerge14, i32 %%72, i32 %%storemerge14, i32 %%73) nounwind, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_322_count);
  printf(( char *)((&aesl_internal__OC_str1[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 42
#endif
])), llvm_cbe_storemerge14, llvm_cbe_tmp__64, llvm_cbe_storemerge14, llvm_cbe_tmp__65);
if (AESL_DEBUG_TRACE) {
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__64);
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__65);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__66);
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__34) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'LED3_TB' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%75 = load i1* %%44, align 1, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_323_count);
  llvm_cbe_tmp__67 = (bool )((*llvm_cbe_tmp__42)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__67);
if (AESL_DEBUG_TRACE)
printf("\n  %%76 = zext i1 %%75 to i32, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_324_count);
  llvm_cbe_tmp__68 = (unsigned int )((unsigned int )(bool )llvm_cbe_tmp__67&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__68);
if (AESL_DEBUG_TRACE)
printf("\n  %%77 = zext i1 %%47 to i32, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_325_count);
  llvm_cbe_tmp__69 = (unsigned int )((unsigned int )(bool )llvm_cbe_tmp__45&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__69);
if (AESL_DEBUG_TRACE)
printf("\n  %%78 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([42 x i8]* @aesl_internal_.str1, i64 0, i64 0), i32 %%storemerge14, i32 %%76, i32 %%storemerge14, i32 %%77) nounwind, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_326_count);
  printf(( char *)((&aesl_internal__OC_str1[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 42
#endif
])), llvm_cbe_storemerge14, llvm_cbe_tmp__68, llvm_cbe_storemerge14, llvm_cbe_tmp__69);
if (AESL_DEBUG_TRACE) {
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__68);
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__69);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__70);
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__34) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'LED3_TB' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%79 = load i1* %%44, align 1, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_327_count);
  llvm_cbe_tmp__71 = (bool )((*llvm_cbe_tmp__42)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__71);
if (AESL_DEBUG_TRACE)
printf("\n  %%80 = zext i1 %%79 to i32, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_328_count);
  llvm_cbe_tmp__72 = (unsigned int )((unsigned int )(bool )llvm_cbe_tmp__71&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__72);
if (AESL_DEBUG_TRACE)
printf("\n  %%81 = zext i1 %%56 to i32, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_329_count);
  llvm_cbe_tmp__73 = (unsigned int )((unsigned int )(bool )llvm_cbe_tmp__52&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__73);
if (AESL_DEBUG_TRACE)
printf("\n  %%82 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([42 x i8]* @aesl_internal_.str1, i64 0, i64 0), i32 %%storemerge14, i32 %%80, i32 %%storemerge14, i32 %%81) nounwind, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_330_count);
  printf(( char *)((&aesl_internal__OC_str1[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 42
#endif
])), llvm_cbe_storemerge14, llvm_cbe_tmp__72, llvm_cbe_storemerge14, llvm_cbe_tmp__73);
if (AESL_DEBUG_TRACE) {
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__72);
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__73);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__74);
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__34) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'LED3_TB' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%83 = load i1* %%44, align 1, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_331_count);
  llvm_cbe_tmp__75 = (bool )((*llvm_cbe_tmp__42)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__75);
if (AESL_DEBUG_TRACE)
printf("\n  %%84 = zext i1 %%83 to i32, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_332_count);
  llvm_cbe_tmp__76 = (unsigned int )((unsigned int )(bool )llvm_cbe_tmp__75&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__76);
if (AESL_DEBUG_TRACE)
printf("\n  %%85 = zext i1 %%65 to i32, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_333_count);
  llvm_cbe_tmp__77 = (unsigned int )((unsigned int )(bool )llvm_cbe_tmp__59&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__77);
if (AESL_DEBUG_TRACE)
printf("\n  %%86 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([42 x i8]* @aesl_internal_.str1, i64 0, i64 0), i32 %%storemerge14, i32 %%84, i32 %%storemerge14, i32 %%85) nounwind, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_334_count);
  printf(( char *)((&aesl_internal__OC_str1[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 42
#endif
])), llvm_cbe_storemerge14, llvm_cbe_tmp__76, llvm_cbe_storemerge14, llvm_cbe_tmp__77);
if (AESL_DEBUG_TRACE) {
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__76);
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__77);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__78);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%87 = add nsw i32 %%storemerge14, 1, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_335_count);
  llvm_cbe_tmp__79 = (unsigned int )((unsigned int )(llvm_cbe_storemerge14&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__79&4294967295ull)));
  if (((llvm_cbe_tmp__79&4294967295U) == (8u&4294967295U))) {
    goto llvm_cbe_tmp__86;
  } else {
    llvm_cbe_storemerge14__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__79;   /* for PHI node */
    llvm_cbe_tmp__33__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__62;   /* for PHI node */
    goto llvm_cbe_tmp__82;
  }

llvm_cbe_tmp__87:
if (AESL_DEBUG_TRACE)
printf("\n  %%61 = phi i32 [ 1, %%58 ], [ %%52, %%51  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_306_count);
  llvm_cbe_tmp__55 = (unsigned int )llvm_cbe_tmp__55__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__55);
printf("\n = 0x%X",1u);
printf("\n = 0x%X",llvm_cbe_tmp__48);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = getelementptr inbounds [8 x i1]* %%LED1_TB, i64 0, i64 %%34, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_307_count);
  llvm_cbe_tmp__56 = (bool *)(&llvm_cbe_LED1_TB[(((signed long long )llvm_cbe_tmp__34))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__34));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__34) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'LED1_TB' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%63 = load i1* %%62, align 1, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_308_count);
  llvm_cbe_tmp__57 = (bool )((*llvm_cbe_tmp__56)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__57);
if (AESL_DEBUG_TRACE)
printf("\n  %%64 = getelementptr inbounds [8 x i1]* @aesl_internal_main.TB_GOLDEN_RESULT1, i64 0, i64 %%34, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_309_count);
  llvm_cbe_tmp__58 = (bool *)(&aesl_internal_main_OC_TB_GOLDEN_RESULT1[(((signed long long )llvm_cbe_tmp__34))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__34));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__34) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_main.TB_GOLDEN_RESULT1' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%65 = load i1* %%64, align 1, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_310_count);
  llvm_cbe_tmp__59 = (bool )((*llvm_cbe_tmp__58)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__59);
if (AESL_DEBUG_TRACE)
printf("\n  %%66 = xor i1 %%63, %%65, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_311_count);
  llvm_cbe_tmp__60 = (bool )((llvm_cbe_tmp__57 ^ llvm_cbe_tmp__59)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__60);
  if (llvm_cbe_tmp__60) {
    goto llvm_cbe_tmp__88;
  } else {
    llvm_cbe_tmp__62__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__55;   /* for PHI node */
    goto llvm_cbe_tmp__85;
  }

llvm_cbe_tmp__89:
if (AESL_DEBUG_TRACE)
printf("\n  %%52 = phi i32 [ 1, %%49 ], [ %%43, %%42  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_294_count);
  llvm_cbe_tmp__48 = (unsigned int )llvm_cbe_tmp__48__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__48);
printf("\n = 0x%X",1u);
printf("\n = 0x%X",llvm_cbe_tmp__41);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = getelementptr inbounds [8 x i1]* %%LED2_TB, i64 0, i64 %%34, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_295_count);
  llvm_cbe_tmp__49 = (bool *)(&llvm_cbe_LED2_TB[(((signed long long )llvm_cbe_tmp__34))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__34));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__34) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'LED2_TB' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = load i1* %%53, align 1, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_296_count);
  llvm_cbe_tmp__50 = (bool )((*llvm_cbe_tmp__49)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__50);
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = getelementptr inbounds [8 x i1]* @aesl_internal_main.TB_GOLDEN_RESULT2, i64 0, i64 %%34, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_297_count);
  llvm_cbe_tmp__51 = (bool *)(&aesl_internal_main_OC_TB_GOLDEN_RESULT2[(((signed long long )llvm_cbe_tmp__34))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__34));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__34) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_main.TB_GOLDEN_RESULT2' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = load i1* %%55, align 1, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_298_count);
  llvm_cbe_tmp__52 = (bool )((*llvm_cbe_tmp__51)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__52);
if (AESL_DEBUG_TRACE)
printf("\n  %%57 = xor i1 %%54, %%56, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_299_count);
  llvm_cbe_tmp__53 = (bool )((llvm_cbe_tmp__50 ^ llvm_cbe_tmp__52)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__53);
  if (llvm_cbe_tmp__53) {
    goto llvm_cbe_tmp__90;
  } else {
    llvm_cbe_tmp__55__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__48;   /* for PHI node */
    goto llvm_cbe_tmp__87;
  }

llvm_cbe_tmp__84:
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = phi i32 [ 1, %%40 ], [ %%33, %%32  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_282_count);
  llvm_cbe_tmp__41 = (unsigned int )llvm_cbe_tmp__41__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__41);
printf("\n = 0x%X",1u);
printf("\n = 0x%X",llvm_cbe_tmp__33);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = getelementptr inbounds [8 x i1]* %%LED3_TB, i64 0, i64 %%34, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_283_count);
  llvm_cbe_tmp__42 = (bool *)(&llvm_cbe_LED3_TB[(((signed long long )llvm_cbe_tmp__34))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__34));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__34) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'LED3_TB' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = load i1* %%44, align 1, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_284_count);
  llvm_cbe_tmp__43 = (bool )((*llvm_cbe_tmp__42)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__43);
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = getelementptr inbounds [8 x i1]* @aesl_internal_main.TB_GOLDEN_RESULT3, i64 0, i64 %%34, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_285_count);
  llvm_cbe_tmp__44 = (bool *)(&aesl_internal_main_OC_TB_GOLDEN_RESULT3[(((signed long long )llvm_cbe_tmp__34))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__34));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__34) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_main.TB_GOLDEN_RESULT3' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = load i1* %%46, align 1, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_286_count);
  llvm_cbe_tmp__45 = (bool )((*llvm_cbe_tmp__44)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__45);
if (AESL_DEBUG_TRACE)
printf("\n  %%48 = xor i1 %%45, %%47, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_287_count);
  llvm_cbe_tmp__46 = (bool )((llvm_cbe_tmp__43 ^ llvm_cbe_tmp__45)&1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__46);
  if (llvm_cbe_tmp__46) {
    goto llvm_cbe_tmp__91;
  } else {
    llvm_cbe_tmp__48__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__41;   /* for PHI node */
    goto llvm_cbe_tmp__89;
  }

llvm_cbe_tmp__83:
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([34 x i8]* @aesl_internal_.str, i64 0, i64 0), i32 %%storemerge14) nounwind, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_277_count);
  printf(( char *)((&aesl_internal__OC_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 34
#endif
])), llvm_cbe_storemerge14);
if (AESL_DEBUG_TRACE) {
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__40);
}
  llvm_cbe_tmp__41__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  goto llvm_cbe_tmp__84;

llvm_cbe_tmp__91:
if (AESL_DEBUG_TRACE)
printf("\n  %%50 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([34 x i8]* @aesl_internal_.str, i64 0, i64 0), i32 %%storemerge14) nounwind, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_289_count);
  printf(( char *)((&aesl_internal__OC_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 34
#endif
])), llvm_cbe_storemerge14);
if (AESL_DEBUG_TRACE) {
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__47);
}
  llvm_cbe_tmp__48__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  goto llvm_cbe_tmp__89;

llvm_cbe_tmp__90:
if (AESL_DEBUG_TRACE)
printf("\n  %%59 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([34 x i8]* @aesl_internal_.str, i64 0, i64 0), i32 %%storemerge14) nounwind, !dbg !8 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_301_count);
  printf(( char *)((&aesl_internal__OC_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 34
#endif
])), llvm_cbe_storemerge14);
if (AESL_DEBUG_TRACE) {
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__54);
}
  llvm_cbe_tmp__55__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  goto llvm_cbe_tmp__87;

llvm_cbe_tmp__88:
if (AESL_DEBUG_TRACE)
printf("\n  %%68 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([34 x i8]* @aesl_internal_.str, i64 0, i64 0), i32 %%storemerge14) nounwind, !dbg !9 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_313_count);
  printf(( char *)((&aesl_internal__OC_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 34
#endif
])), llvm_cbe_storemerge14);
if (AESL_DEBUG_TRACE) {
printf("\nArgument storemerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__61);
}
  llvm_cbe_tmp__62__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  goto llvm_cbe_tmp__85;

  } while (1); /* end of syntactic loop '' */
llvm_cbe_tmp__86:
  if (((llvm_cbe_tmp__62&4294967295U) == (0u&4294967295U))) {
    goto llvm_cbe_tmp__92;
  } else {
    goto llvm_cbe_tmp__93;
  }

llvm_cbe_tmp__92:
if (AESL_DEBUG_TRACE)
printf("\n  %%91 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([21 x i8]* @aesl_internal_.str2, i64 0, i64 0)) nounwind, !dbg !10 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_370_count);
  printf(( char *)((&aesl_internal__OC_str2[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 21
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__80);
}
  goto llvm_cbe_tmp__94;

llvm_cbe_tmp__93:
if (AESL_DEBUG_TRACE)
printf("\n  %%93 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([21 x i8]* @aesl_internal_.str3, i64 0, i64 0)) nounwind, !dbg !10 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_372_count);
  printf(( char *)((&aesl_internal__OC_str3[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 21
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__81);
}
  goto llvm_cbe_tmp__94;

llvm_cbe_tmp__94:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @main}\n");
  return llvm_cbe_tmp__62;
}

