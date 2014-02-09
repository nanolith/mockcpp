#include <mockpp/MockProbe.h>
#include <gtest/gtest.h>

using namespace mockpp;

/**
 * MockProbe can be instantiated
 */
TEST(MockProbe, instantiation)
{
    MockProbe<void, int> dummy;
}

/**
 * MockProbe returns the default value of a type by default.
 */
TEST(MockProbe, returnDefaults)
{
    ASSERT_EQ(false, MockProbe<bool>()());
    ASSERT_EQ(0, MockProbe<int>()());
    ASSERT_EQ(0, MockProbe<char>()());
}

/**
 * MockProbe has a toReturn accessor, which sets the return type of the probed
 * function.
 */
TEST(MockProbe, toReturnBool)
{
    MockProbe<bool> probe;

    probe.toReturn(true);

    ASSERT_EQ(true, probe());
}

/**
 * MockProbe has a toDo accessor, which sets the action to be performed when the
 * functor is called.
 */
TEST(MockProbe, toDoVoid)
{
    MockProbe<void, int> probe;
    bool called = false;

    probe.toDo([&](int x) { called = true; } );

    //call the provided action
    probe(17);

    //called should be set to true.
    ASSERT_EQ(true, called);
}

/**
 * MockProbe has a toDo accessor, which sets the action to be performed when the
 * functor is called. This version returns a value.
 */
TEST(MockProbe, toDoReturn)
{
    const int RETURN_VAL = 17;
    MockProbe<int, bool> probe;
    bool called = false;

    probe.toDo([&called](bool x) -> int { called = true; return RETURN_VAL; } );

    //call the provided action
    ASSERT_EQ(RETURN_VAL, probe(false));

    //called should be set to true.
    ASSERT_EQ(true, called);
}
