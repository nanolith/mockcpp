#ifndef  MOCKPP_HELPERS_HEADER_GUARD
# define MOCKPP_HELPERS_HEADER_GUARD

#include <mockpp/variadic_macro_helpers.h>

#define MOCK_FUNCTION(returnType, functionName) \
    returnType functionName() \
    { \
        functionName##_VALIDATE.addInvocation(*this); \
        \
        return functionName##_PROBE(); \
    }\
    \
    ::mockpp::MockProbe<returnType> functionName##_PROBE; \
    ::mockpp::MockValidator<returnType> functionName##_VALIDATE;

#define MOCK_FUNCTION_VOID(functionName) \
	void functionName() \
    { \
        functionName##_VALIDATE.addInvocation(*this); \
        \
        return functionName##_PROBE(); \
    }\
    \
    ::mockpp::MockProbe<void> functionName##_PROBE; \
    ::mockpp::MockValidator<void> functionName##_VALIDATE;

#define MOCK_FUNCTION_VOID_ARGS(functionName,...) \
	void functionName(MAKE_PARAMS(__VA_ARGS__)) \
    { \
        functionName##_VALIDATE.addInvocation(*this, MAKE_ARGS(__VA_ARGS__)); \
        \
        return functionName##_PROBE(MAKE_ARGS(__VA_ARGS__)); \
    }\
    \
    ::mockpp::MockProbe<void,__VA_ARGS__> functionName##_PROBE; \
    ::mockpp::MockValidator<void,__VA_ARGS__> functionName##_VALIDATE;

#define MOCK_FUNCTION_ARGS(returnType,functionName,...) \
	returnType functionName(MAKE_PARAMS(__VA_ARGS__)) \
    { \
        functionName##_VALIDATE.addInvocation(*this, MAKE_ARGS(__VA_ARGS__)); \
        \
        return functionName##_PROBE(MAKE_ARGS(__VA_ARGS__)); \
    }\
    \
    ::mockpp::MockProbe<returnType,__VA_ARGS__> functionName##_PROBE; \
    ::mockpp::MockValidator<returnType,__VA_ARGS__> functionName##_VALIDATE;

#define PROBE(obj, method) (obj).method##_PROBE
#define VALIDATE(obj, method) (obj).method##_VALIDATE.validationBuilder(obj)

#endif //MOCKPP_HELPERS_HEADER_GUARD
