#include <mockpp/MockValidator.h>
#include <gtest/gtest.h>

using namespace mockpp;

/**
 * MockValidator can be instantiated
 */
TEST(MockValidator, instantiation)
{
    MockValidator<void, int> dummy1;

    MockValidator<void> dummy2;
}

/**
 * MockValidator adds invocations to a mock.
 */
TEST(MockValidator, addInvocations)
{
    struct DummyType { };
    Mock<DummyType> dummyMock;

    MockValidator<void> dummyFunc;

    ASSERT_EQ(0, dummyMock.invocations().size());

    dummyFunc.addInvocation(dummyMock);

    //there is now an invocation in the mock
    ASSERT_EQ(1, dummyMock.invocations().size());

    //that invocation matches our method.
    ASSERT_EQ(
        typeid(Invocation<MockValidator<void>>).hash_code(),
        dummyMock.invocations(0)->hashCode());
}

/**
 * MockValidator adds invocations with arguments to a mock.
 */
TEST(MockValidator, addInvocationsWithArgs)
{
    const int INT_VALUE = 17;
    const bool BOOL_VALUE = true;
    struct DummyType { };
    Mock<DummyType> dummyMock;

    MockValidator<void, int, bool> dummyFunc;

    ASSERT_EQ(0, dummyMock.invocations().size());

    dummyFunc.addInvocation(dummyMock, INT_VALUE, BOOL_VALUE);

    //there is now an invocation in the mock
    ASSERT_EQ(1, dummyMock.invocations().size());

    //that invocation matches our method.
    ASSERT_EQ(
        typeid(Invocation<MockValidator<void, int, bool>, int, bool>).hash_code(),
        dummyMock.invocations(0)->hashCode());
}

/**
 * MockValidator has a validationBuilder function which returns an appropriate
 * ValidationBuilder for the type.
 */
TEST(MockValidator, validationBuilderBasics)
{
    const int INT_VALUE = 17;
    const bool BOOL_VALUE = true;
    struct DummyType { };
    Mock<DummyType> dummyMock;

    MockValidator<void, int, bool> dummyFunc;

    dummyFunc.validationBuilder(dummyMock);
}

/**
 * ValidationBuilder provides a called method which queries the base mock about
 * whether a certain invocation has been made.
 */
TEST(MockValidator, validationBuilder_called)
{
    struct DummyType { };
    Mock<DummyType> dummyMock;

    MockValidator<void> dummyFunc;

    //no invocations have occurred
    ASSERT_EQ(0, dummyMock.invocations().size());

    //the validator DOES NOT match this invocation
    ASSERT_FALSE(dummyFunc.validationBuilder(dummyMock).called());

    dummyFunc.addInvocation(dummyMock);

    //there is now an invocation in the mock
    ASSERT_EQ(1, dummyMock.invocations().size());

    //the validator matches this invocation
    ASSERT_TRUE(dummyFunc.validationBuilder(dummyMock).called());
}

/**
 * ValidationBuilder provides a called method which queries the base mock about
 * whether a certain invocation has been made, including arguments.
 */
TEST(MockValidator, validationBuilder_called_args)
{
    const int INT_VALUE = 17;
    const bool BOOL_VALUE = true;
    struct DummyType { };
    Mock<DummyType> dummyMock;

    MockValidator<void, int, bool> dummyFunc;

    //no invocations have occurred
    ASSERT_EQ(0, dummyMock.invocations().size());

    //the validator DOES NOT match this invocation
    ASSERT_FALSE(
        dummyFunc.validationBuilder(dummyMock).called(INT_VALUE, BOOL_VALUE));

    //add an invocation
    dummyFunc.addInvocation(dummyMock, INT_VALUE, BOOL_VALUE);

    //there is now an invocation in the mock
    ASSERT_EQ(1, dummyMock.invocations().size());

    //the validator matches this invocation
    ASSERT_TRUE(
        dummyFunc.validationBuilder(dummyMock).called(INT_VALUE, BOOL_VALUE));

    //reset the mock
    dummyMock.clear();

    //add an invocation
    dummyFunc.addInvocation(dummyMock, INT_VALUE, BOOL_VALUE);

    //the validator DOES NOT match this invocation, because the arguments don't
    //match
    ASSERT_FALSE(
        dummyFunc.validationBuilder(dummyMock).called(0, false));
}

/**
 * ValidationBuilder.called returns false when a different invocation was made.
 */
TEST(MockValidator, validationBuilder_called_different_function)
{
    const int INT_VALUE = 17;
    const bool BOOL_VALUE = true;
    struct DummyType { };
    Mock<DummyType> dummyMock;

    MockValidator<void, int, bool> dummyFunc;
    MockValidator<bool> otherFunc;

    //no invocations have occurred
    ASSERT_EQ(0, dummyMock.invocations().size());

    //the validator DOES NOT match this invocation
    ASSERT_FALSE(
        otherFunc.validationBuilder(dummyMock).called());

    //add an invocation
    dummyFunc.addInvocation(dummyMock, INT_VALUE, BOOL_VALUE);

    //there is now an invocation in the mock
    ASSERT_EQ(1, dummyMock.invocations().size());

    //the validator DOES NOT match this invocation; it was a dummyFunc
    //invocation.
    ASSERT_FALSE(
        otherFunc.validationBuilder(dummyMock).called());
}
