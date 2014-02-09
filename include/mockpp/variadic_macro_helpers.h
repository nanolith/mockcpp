#ifndef  MOCKPP_VARIADIC_MACRO_HELPERS_HEADER_GUARD
# define MOCKPP_VARIADIC_MACRO_HELPERS_HEADER_GUARD

//Determine the number of arguments passed to a variadic template
#define _NUM_ARGS2(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,N,...) N
#define NUM_ARGS(...) _NUM_ARGS2(0, ##__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

//turn types into a parameter list with arg1, arg2, ...

#define MAKE_PARAMS_0()
#define MAKE_PARAMS_1(type1) \
    type1 arg1
#define MAKE_PARAMS_2(type1, type2) \
    MAKE_PARAMS_1(type1), \
    type2 arg2
#define MAKE_PARAMS_3(type1, type2, type3) \
	MAKE_PARAMS_2(type1, type2), \
    type3 arg3
#define MAKE_PARAMS_4(type1, type2, type3, type4) \
    MAKE_PARAMS_3(type1, type2, type3), \
    type4 arg4
#define MAKE_PARAMS_5(type1, type2, type3, type4, type5) \
    MAKE_PARAMS_4(type1, type2, type3, type4), \
    type5 arg5
#define MAKE_PARAMS_6(type1, type2, type3, type4, type5, type6) \
    MAKE_PARAMS_5(type1, type2, type3, type4, type5), \
    type6 arg6
#define MAKE_PARAMS_7(type1, type2, type3, type4, type5, type6, type7) \
    MAKE_PARAMS_6(type1, type2, type3, type4, type5, type6), \
    type7 arg7
#define MAKE_PARAMS_8(type1, type2, type3, type4, type5, type6, type7, type8) \
    MAKE_PARAMS_7(type1, type2, type3, type4, type5, type6, type7), \
    type8 arg8
#define MAKE_PARAMS_9(type1, type2, type3, type4, type5, type6, type7, type8, \
                      type9) \
    MAKE_PARAMS_8(type1, type2, type3, type4, type5, type6, type7, type8), \
    type9 arg9
#define MAKE_PARAMS_10(type1, type2, type3, type4, type5, type6, type7, type8,\
                      type9, type10) \
    MAKE_PARAMS_9(type1, type2, type3, type4, type5, type6, type7, type8, \
                  type9), \
    type10 arg10
#define MAKE_PARAMS_11(type1, type2, type3, type4, type5, type6, type7, type8,\
                      type9, type10, type11) \
    MAKE_PARAMS_10(type1, type2, type3, type4, type5, type6, type7, type8,\
                   type9, type10), \
    type11 arg11
#define MAKE_PARAMS_12(type1, type2, type3, type4, type5, type6, type7, type8,\
                      type9, type10, type11, type12) \
    MAKE_PARAMS_11(type1, type2, type3, type4, type5, type6, type7, type8,\
                   type9, type10, type11), \
    type12 arg12
#define MAKE_PARAMS_13(type1, type2, type3, type4, type5, type6, type7, type8,\
                      type9, type10, type11, type12, type13) \
    MAKE_PARAMS_12(type1, type2, type3, type4, type5, type6, type7, type8,\
                      type9, type10, type11, type12), \
    type13 arg13
#define MAKE_PARAMS_14(type1, type2, type3, type4, type5, type6, type7, type8,\
                      type9, type10, type11, type12, type13, type14) \
    MAKE_PARAMS_13(type1, type2, type3, type4, type5, type6, type7, type8,\
                      type9, type10, type11, type12, type13), \
    type14 arg14
#define MAKE_PARAMS_15(type1, type2, type3, type4, type5, type6, type7, type8,\
                      type9, type10, type11, type12, type13, type14, type15) \
    MAKE_PARAMS_14(type1, type2, type3, type4, type5, type6, type7, type8,\
                      type9, type10, type11, type12, type13, type14), \
    type15 arg15
#define MAKE_PARAMS_16(type1, type2, type3, type4, type5, type6, type7, type8,\
                      type9, type10, type11, type12, type13, type14, type15, \
                      type16) \
    MAKE_PARAMS_15(type1, type2, type3, type4, type5, type6, type7, type8,\
                   type9, type10, type11, type12, type13, type14, type15), \
    type16 arg16
#define MAKE_PARAMS_N(N, ...) MAKE_PARAMS_##N(__VA_ARGS__)
#define MAKE_PARAMS_FORCE_N(N, ...) MAKE_PARAMS_N(N, __VA_ARGS__)
#define MAKE_PARAMS(...) MAKE_PARAMS_FORCE_N(NUM_ARGS(__VA_ARGS__), __VA_ARGS__)

//get the arguments for a particular type list
#define MAKE_ARGS_0()
#define MAKE_ARGS_1(type) \
    arg1
#define MAKE_ARGS_2(t1, t2) \
    MAKE_ARGS_1(t1), \
    arg2
#define MAKE_ARGS_3(t1, t2, t3) \
    MAKE_ARGS_2(t1, t2), \
    arg3
#define MAKE_ARGS_4(t1, t2, t3, t4) \
    MAKE_ARGS_3(t1, t2, t3), \
    arg4
#define MAKE_ARGS_5(t1, t2, t3, t4, t5) \
    MAKE_ARGS_4(t1, t2, t3, t4), \
    arg5
#define MAKE_ARGS_6(t1, t2, t3, t4, t5, t6) \
    MAKE_ARGS_5(t1, t2, t3, t4, t5), \
    arg6
#define MAKE_ARGS_7(t1, t2, t3, t4, t5, t6, t7) \
    MAKE_ARGS_6(t1, t2, t3, t4, t5, t6), \
    arg7
#define MAKE_ARGS_8(t1, t2, t3, t4, t5, t6, t7, t8) \
    MAKE_ARGS_7(t1, t2, t3, t4, t5, t6, t7), \
    arg8
#define MAKE_ARGS_9(t1, t2, t3, t4, t5, t6, t7, t8, t9) \
    MAKE_ARGS_8(t1, t2, t3, t4, t5, t6, t7, t8), \
    arg9
#define MAKE_ARGS_10(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10) \
    MAKE_ARGS_9(t1, t2, t3, t4, t5, t6, t7, t8, t9), \
    arg10
#define MAKE_ARGS_11(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11) \
    MAKE_ARGS_10(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10), \
    arg11
#define MAKE_ARGS_12(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12) \
    MAKE_ARGS_11(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11), \
    arg12
#define MAKE_ARGS_13(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13) \
    MAKE_ARGS_12(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12), \
    arg13
#define MAKE_ARGS_14(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, \
                     t14) \
    MAKE_ARGS_13(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13), \
    arg14
#define MAKE_ARGS_15(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, \
                     t14, t15) \
    MAKE_ARGS_14(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14) \
    arg15
#define MAKE_ARGS_16(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, \
                     t14, t15, t16) \
    MAKE_ARGS_15(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, \
                 t15) \
    arg16

#define MAKE_ARGS_N(N, ...) MAKE_ARGS_##N(__VA_ARGS__)
#define MAKE_ARGS_FORCE_N(N, ...) MAKE_ARGS_N(N, __VA_ARGS__)
#define MAKE_ARGS(...) MAKE_ARGS_FORCE_N(NUM_ARGS(__VA_ARGS__), __VA_ARGS__)

#endif //MOCKPP_VARIADIC_MACRO_HELPERS_HEADER_GUARD
