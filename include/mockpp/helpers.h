#ifndef  MOCKPP_HELPERS_HEADER_GUARD
# define MOCKPP_HELPERS_HEADER_GUARD

#include <type_traits>
#include <mockpp/variadic_macro_helpers.h>

#define MOCK_POLY_FUNCTION(returnType, functionName, helperName) \
    returnType functionName() \
    { \
        helperName##_VALIDATE.addInvocation(*this); \
        \
        return helperName##_PROBE(); \
    }\
    \
    ::mockpp::MockProbe<returnType> helperName##_PROBE; \
    ::mockpp::MockValidator<returnType> helperName##_VALIDATE;

#define MOCK_POLY_FUNCTION_VOID(functionName, helperName) \
	void functionName() \
    { \
        helperName##_VALIDATE.addInvocation(*this); \
        \
        return helperName##_PROBE(); \
    }\
    \
    ::mockpp::MockProbe<void> helperName##_PROBE; \
    ::mockpp::MockValidator<void> helperName##_VALIDATE;

#define MOCK_POLY_FUNCTION_VOID_ARGS(functionName,helperName,...) \
	void functionName(MAKE_PARAMS(__VA_ARGS__)) \
    { \
        helperName##_VALIDATE.addInvocation(*this, MAKE_ARGS(__VA_ARGS__)); \
        \
        return helperName##_PROBE(MAKE_ARGS(__VA_ARGS__)); \
    }\
    \
    ::mockpp::MockProbe<void,REMOVE_REFS(__VA_ARGS__)> helperName##_PROBE; \
    ::mockpp::MockValidator<void,REMOVE_REFS(__VA_ARGS__)> helperName##_VALIDATE;

#define MOCK_POLY_FUNCTION_ARGS(returnType,functionName,helperName,...) \
	returnType functionName(MAKE_PARAMS(__VA_ARGS__)) \
    { \
        helperName##_VALIDATE.addInvocation(*this, MAKE_ARGS(__VA_ARGS__)); \
        \
        return helperName##_PROBE(MAKE_ARGS(__VA_ARGS__)); \
    }\
    \
    ::mockpp::MockProbe<returnType,REMOVE_REFS(__VA_ARGS__)> helperName##_PROBE; \
    ::mockpp::MockValidator<returnType,REMOVE_REFS(__VA_ARGS__)> helperName##_VALIDATE;


#define MOCK_POLY_CONST_FUNCTION(returnType, functionName, helperName) \
    returnType functionName() const \
    { \
        helperName##_VALIDATE.addInvocation(*this); \
        \
        return helperName##_PROBE(); \
    }\
    \
    mutable ::mockpp::MockProbe<returnType> helperName##_PROBE; \
    mutable ::mockpp::MockValidator<returnType> helperName##_VALIDATE;

#define MOCK_POLY_CONST_FUNCTION_VOID(functionName, helperName) \
	void functionName() const \
    { \
        helperName##_VALIDATE.addInvocation(*this); \
        \
        return helperName##_PROBE(); \
    }\
    \
    mutable ::mockpp::MockProbe<void> helperName##_PROBE; \
    mutable ::mockpp::MockValidator<void> helperName##_VALIDATE;

#define MOCK_POLY_CONST_FUNCTION_VOID_ARGS(functionName,helperName,...) \
	void functionName(MAKE_PARAMS(__VA_ARGS__)) const \
    { \
        helperName##_VALIDATE.addInvocation(*this, MAKE_ARGS(__VA_ARGS__)); \
        \
        return helperName##_PROBE(MAKE_ARGS(__VA_ARGS__)); \
    }\
    \
    mutable ::mockpp::MockProbe<void,REMOVE_REFS(__VA_ARGS__)> helperName##_PROBE; \
    mutable ::mockpp::MockValidator<void,REMOVE_REFS(__VA_ARGS__)> helperName##_VALIDATE;

#define MOCK_POLY_CONST_FUNCTION_ARGS(returnType,functionName,helperName,...) \
	returnType functionName(MAKE_PARAMS(__VA_ARGS__)) const \
    { \
        helperName##_VALIDATE.addInvocation(*this, MAKE_ARGS(__VA_ARGS__)); \
        \
        return helperName##_PROBE(MAKE_ARGS(__VA_ARGS__)); \
    }\
    \
    mutable ::mockpp::MockProbe<returnType,REMOVE_REFS(__VA_ARGS__)> helperName##_PROBE; \
    mutable ::mockpp::MockValidator<returnType,REMOVE_REFS(__VA_ARGS__)> helperName##_VALIDATE;

#define MOCK_FUNCTION(returnType, functionName) \
    MOCK_POLY_FUNCTION(returnType, functionName, functionName)

#define MOCK_FUNCTION_VOID(functionName) \
    MOCK_POLY_FUNCTION_VOID(functionName, functionName)

#define MOCK_FUNCTION_VOID_ARGS(functionName,...) \
    MOCK_POLY_FUNCTION_VOID_ARGS(functionName,functionName,__VA_ARGS__)

#define MOCK_FUNCTION_ARGS(returnType,functionName,...) \
    MOCK_POLY_FUNCTION_ARGS(returnType,functionName,functionName,__VA_ARGS__)

#define MOCK_CONST_FUNCTION(returnType, functionName) \
    MOCK_POLY_CONST_FUNCTION(returnType,functionName,functionName)

#define MOCK_CONST_FUNCTION_VOID(functionName) \
    MOCK_POLY_CONST_FUNCTION_VOID(functionName,functionName)

#define MOCK_CONST_FUNCTION_VOID_ARGS(functionName,...) \
    MOCK_POLY_CONST_FUNCTION_VOID_ARGS(functionName,functionName,__VA_ARGS__)

#define MOCK_CONST_FUNCTION_ARGS(returnType,functionName,...) \
    MOCK_POLY_CONST_FUNCTION_ARGS(returnType,functionName,functionName,__VA_ARGS__)

#define PROBE(obj, method) (obj).method##_PROBE
#define VALIDATE(obj, method) (obj).method##_VALIDATE.validationBuilder(obj)

#endif //MOCKPP_HELPERS_HEADER_GUARD
