#pragma once

#include<stdint.h>

typedef int8_t    s0;
typedef int16_t   s1;
typedef int32_t   s2;
typedef int64_t   s3;

typedef uint8_t   u0;
typedef uint16_t  u1;
typedef uint32_t  u2;
typedef uint64_t  u3;

typedef float     f2;
typedef double    f3;

#define ARG_T_SIZE_CALC_1(k) PP_POW2(k)
#define ARG_T_SIZE_CALC_2(k) PP_POW2(PP_DEC(k))
#define ARG_T_SIZE_CALC_4(k) PP_POW2(PP_DEC(PP_DEC(k)))
#define ARG_T_SIZE_CALC_8(k) PP_POW2(PP_DEC(PP_DEC(PP_DEC(k))))
#define CREATE_ARG_T(k) union PP_CONCAT(Arg_t_,k)               \
{                                                               \
    struct{u3 PP_AUTO_IDENTIFIER(UL,ARG_T_SIZE_CALC_8(k),8);};  \
    struct{u3 UL[ARG_T_SIZE_CALC_8(k)];};                       \
                                                                \
    struct{s3 PP_AUTO_IDENTIFIER(L,ARG_T_SIZE_CALC_8(k),8);};   \
    struct{s3 L[ARG_T_SIZE_CALC_8(k)];};                        \
                                                                \
    struct{f3 PP_AUTO_IDENTIFIER(D,ARG_T_SIZE_CALC_8(k),8);};   \
    struct{f3 D[ARG_T_SIZE_CALC_8(k)];};                        \
                                                                \
    struct{u2 PP_AUTO_IDENTIFIER(U,ARG_T_SIZE_CALC_4(k),4);};   \
    struct{u2 U[ARG_T_SIZE_CALC_4(k)];};                        \
                                                                \
    struct{s2 PP_AUTO_IDENTIFIER(I,ARG_T_SIZE_CALC_4(k),4);};   \
    struct{s2 I[ARG_T_SIZE_CALC_4(k)];};                        \
                                                                \
    struct{f2 PP_AUTO_IDENTIFIER(F,ARG_T_SIZE_CALC_4(k),4);};   \
    struct{f2 F[ARG_T_SIZE_CALC_4(k)];};                        \
                                                                \
    struct{u1 PP_AUTO_IDENTIFIER(US,ARG_T_SIZE_CALC_2(k),2);};  \
    struct{u1 US[ARG_T_SIZE_CALC_2(k)];};                       \
                                                                \
    struct{s1 PP_AUTO_IDENTIFIER(SH,ARG_T_SIZE_CALC_2(k),2);};  \
    struct{s1 SH[ARG_T_SIZE_CALC_2(k)];};                       \
                                                                \
    struct{u0 PP_AUTO_IDENTIFIER(byte,ARG_T_SIZE_CALC_1(k),1);};\
    struct{u0 byte[ARG_T_SIZE_CALC_1(k)];};                     \
                                                                \
    struct{s0 PP_AUTO_IDENTIFIER(sbyte,ARG_T_SIZE_CALC_1(k),1);};\
    struct{s0 sbyte[ARG_T_SIZE_CALC_1(k)];};                    \
                                                                \
    struct{void PP_AUTO_IDENTIFIER(*P,ARG_T_SIZE_CALC_8(k),8);};\
    struct{void *P[ARG_T_SIZE_CALC_8(k)];};                     \
};

//Arg_t_{3/4/5/6}
CREATE_ARG_T(3)
CREATE_ARG_T(4)
CREATE_ARG_T(5)
CREATE_ARG_T(6)
CREATE_ARG_T(7)

#undef ARG_T_SIZE_CALC_8
#undef ARG_T_SIZE_CALC_4
#undef ARG_T_SIZE_CALC_2
#undef ARG_T_SIZE_CALC_1
#undef CREATE_ARG_T
