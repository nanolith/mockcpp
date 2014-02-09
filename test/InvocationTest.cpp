#include <mockpp/Invocation.h>
#include <gtest/gtest.h>

using namespace mockpp;

typedef int DummyBaseType;

/**
 * The BaseInvocation constructor should initialize the hashCode value.
 */
TEST(BaseInvocation, constructor)
{
    const size_t HASH_CODE_VALUE = 124;

    BaseInvocation b(HASH_CODE_VALUE);
    ASSERT_EQ(HASH_CODE_VALUE, b.hashCode());

    //hashCode should be const safe
    const BaseInvocation cb = b;
    ASSERT_EQ(HASH_CODE_VALUE, b.hashCode());
}

/**
 * Two Invocation types should not have the same hashCode.
 */
TEST(Invocation, hashCodeInequality)
{
    Invocation<DummyBaseType, int> x(1);
    Invocation<DummyBaseType, bool> y(false);

    ASSERT_NE(x.hashCode(), y.hashCode());
}

/**
 * Two instances of the same invocation type should have the same hashCode.
 */
TEST(Invocation, hashCodeInstanceEquality)
{
    Invocation<DummyBaseType, int> x(7);
    Invocation<DummyBaseType, int> y(0);

    ASSERT_EQ(x.hashCode(), y.hashCode());
}

/**
 * Two instances of different invocation types with the same arguments should
 * have different hashCodes.
 */
TEST(Invocation, hashCodeDifferentInstanceInequality)
{
    Invocation<DummyBaseType, int> x(7);
    Invocation<bool, int> y(0);

    ASSERT_NE(x.hashCode(), y.hashCode());
}

/**
 * Two instances of different invocation types with similar but different named
 * structures should have different hashCodes.
 */
TEST(Invocation, hashCodeSameStructureDifferentName)
{
    struct Struct1Tag {};
    struct Struct2Tag {};

    Invocation<Struct1Tag, int> x(7);
    Invocation<Struct2Tag, int> y(7);

    ASSERT_NE(x.hashCode(), y.hashCode());
}
