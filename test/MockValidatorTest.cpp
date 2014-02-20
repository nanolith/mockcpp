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

/**
 * The called method accepts Ignore as arguments, and ignores these arguments
 * when evaluating whether a method was called.
 */
TEST(MockValidator, validationBuilder_called_ignore)
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

    //the validator matches these arguments because they are ignored.
    ASSERT_TRUE(
        dummyFunc.validationBuilder(dummyMock).called(Ignore(), Ignore()));
}

/**
 * The called method accepts Ignore as a single argument.
 */
TEST(MockValidator, validationBuilder_called_single_ignore)
{
    const int INT_VALUE = 17;
    struct DummyType { };
    Mock<DummyType> dummyMock;

    MockValidator<void, int> dummyFunc;

    //no invocations have occurred
    ASSERT_EQ(0, dummyMock.invocations().size());

    //the validator DOES NOT match this invocation
    ASSERT_FALSE(
        dummyFunc.validationBuilder(dummyMock).called(Ignore()));

    //add an invocation
    dummyFunc.addInvocation(dummyMock, INT_VALUE);

    //there is now an invocation in the mock
    ASSERT_EQ(1, dummyMock.invocations().size());

    //the validator matches these arguments because they are ignored.
    ASSERT_TRUE(
        dummyFunc.validationBuilder(dummyMock).called(Ignore()));
}

/**
 * The called method accepts Ignore as arguments, and ignores these arguments
 * when evaluating whether a method was called.  It returns false when the
 * function was not called.
 */
TEST(MockValidator, validationBuilder_called_ignore_no_invocation)
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

    //No invocations for this mock exist
    ASSERT_EQ(0, dummyMock.invocations().size());

    //the validator matches these arguments because they are ignored.
    //It returns false because no invocation of this function was made.
    ASSERT_FALSE(
        dummyFunc.validationBuilder(dummyMock).called(Ignore(), Ignore()));
}

/**
 * The called method returns false when a different method was called, even when
 * arguments are ignored.
 */
TEST(MockValidator, validationBuilder_called_ignore_different_function)
{
    const int INT_VALUE = 17;
    const bool BOOL_VALUE = true;
    struct DummyType { };
    Mock<DummyType> dummyMock;

    MockValidator<void, int, bool> dummyFunc;
    MockValidator<void, int> differentFunc;

    //no invocations have occurred
    ASSERT_EQ(0, dummyMock.invocations().size());

    //the validator DOES NOT match this invocation
    ASSERT_FALSE(
        dummyFunc.validationBuilder(dummyMock).called(INT_VALUE, BOOL_VALUE));

    //add an invocation of the other function
    differentFunc.addInvocation(dummyMock, INT_VALUE);

    //there is now an invocation in the mock
    ASSERT_EQ(1, dummyMock.invocations().size());

    //the validator returns false because a different function was invoked
    ASSERT_FALSE(
        dummyFunc.validationBuilder(dummyMock).called(Ignore(), Ignore()));
}

/**
 * The called method accepts lambda arguments, and invokes these arguments to
 * decide whether the call matches.
 */
TEST(MockValidator, validationBuilder_called_ignore_lambda)
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

    //the validator matches these arguments
    ASSERT_TRUE(
        dummyFunc.validationBuilder(dummyMock).called([](int x) -> bool { return x > 5; }, Ignore()));
}

/**
 * The called method accepts a single lambda argument for a function that takes
 * one argument.
 */
TEST(MockValidator, validationBuilder_called_single_lambda)
{
    const int INT_VALUE = 17;
    struct DummyType { };
    Mock<DummyType> dummyMock;

    MockValidator<void, int> dummyFunc;

    //no invocations have occurred
    ASSERT_EQ(0, dummyMock.invocations().size());

    //the validator DOES NOT match this invocation
    ASSERT_FALSE(
        dummyFunc.validationBuilder(dummyMock).called(INT_VALUE));

    //add an invocation
    dummyFunc.addInvocation(dummyMock, INT_VALUE);

    //there is now an invocation in the mock
    ASSERT_EQ(1, dummyMock.invocations().size());

    //the validator matches these arguments
    ASSERT_TRUE(
        dummyFunc.validationBuilder(dummyMock).called([](int x) -> bool { return x > 5; }));

    //clear the mock
    dummyMock.clear();

    //this validator does not match these arguments
    ASSERT_FALSE(
        dummyFunc.validationBuilder(dummyMock).called([](int x) -> bool { return x > 5; }));

    //add an invocation
    dummyFunc.addInvocation(dummyMock, INT_VALUE);

    //this validator does not match these arguments
    ASSERT_FALSE(
        dummyFunc.validationBuilder(dummyMock).called([](int x) -> bool { return x < 5; }));
}
