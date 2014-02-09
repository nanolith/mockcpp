#include <mockpp/Mock.h>
#include <gtest/gtest.h>

using namespace mockpp;
using namespace std;

struct EmptyType { };

/**
 * Mock can be instantiated.
 */
TEST(Mock, instantiation)
{
    Mock<EmptyType> mock;
}

/**
 * Mock has an invocations method which returns the invocationList.
 */
TEST(Mock, invocationsAccessor)
{
    Mock<EmptyType> mock;

    ASSERT_EQ(0, mock.invocations().size());
}

/**
 * Mock has an invocations method which returns the invocation at a given offset
 * in the list.
 */
TEST(Mock, invocationsWithOffsetAccessor)
{
    Mock<EmptyType> mock;

    ASSERT_EQ(0, mock.invocations().size());

    mock.invocations().push_back(make_shared<Invocation<BaseMock>>());

    ASSERT_EQ(1, mock.invocations().size());

    //Make sure this invocation matches our type, and test the accessor.
    ASSERT_EQ(typeid(Invocation<BaseMock>).hash_code(), mock.invocations(0)->hashCode());
}
