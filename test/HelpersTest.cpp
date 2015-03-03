#include <gtest/gtest.h>
#include <memory>
#include <mockpp/mockpp.h>
#include <string>

using namespace mockpp;
using namespace std;

/**
 * Widget interface.
 */
class Widget
{
public:
    virtual bool isReady() = 0;
    virtual void performAction(int) = 0;
    virtual ~Widget() { }
};

/**
 * Our test interface.
 */
class A
{
public:
    A(Widget* widget) : widget_(widget) { }

    virtual void frobulate() = 0;

private:
    std::shared_ptr<Widget> widget_;
};

/**
 * Const test interface.
 */
class B
{
public:

    virtual void frobulate() const = 0;
    virtual bool testIt(int x) const = 0;
};

/**
 * reference test interface.
 */
class C
{
public:

    virtual void testRef(const string&) const = 0;
};

/**
 * polymorphic test interface
 */
class Poly
{
public:

    virtual void testPoly(const int&) const = 0;
    virtual void testPoly(const string&) const = 0;
};

/**
 * Mock the Widget interface.
 */
class MockWidget : public Widget, public mockpp::Mock<Widget>
{
public:
    ~MockWidget() { }

    MOCK_FUNCTION(bool, isReady);
    MOCK_FUNCTION_VOID_ARGS(performAction, int);
};

/**
 * Mock the Widget interface (relaxed).
 */
class RelaxedMockWidget : public Widget, public mockpp::RelaxedMock<Widget>
{
public:
    ~RelaxedMockWidget() { }

    MOCK_FUNCTION(bool, isReady);
    MOCK_FUNCTION_VOID_ARGS(performAction, int);
};

/**
 * Mock the test interface.
 */
class MockA : public A, public mockpp::Mock<A>
{
public:
    MockA(Widget* widget) : A(widget) { }

    MOCK_FUNCTION_VOID(frobulate);
};

/**
 * Mock const test interface.
 */
class MockB : public B, public mockpp::Mock<B>
{
public:

    MOCK_CONST_FUNCTION_VOID(frobulate);
    MOCK_CONST_FUNCTION_ARGS(bool, testIt, int);
};

/**
 * Mock reference test interface.
 */
class MockC : public mockpp::Mock<C>
{
public:

    MOCK_CONST_FUNCTION_VOID_ARGS(testRef, const string&);
};

/**
 * Mock poly test interface.
 */
class MockPoly : public mockpp::Mock<Poly>
{
public:

    MOCK_POLY_CONST_FUNCTION_VOID_ARGS(testPoly,testPolyInt,const int&);
    MOCK_POLY_CONST_FUNCTION_VOID_ARGS(testPoly,testPolyString,const string&);
};

/**
 * Test construction of mocks.
 */
TEST(HelperTest, construction)
{
    auto widget = new MockWidget(); //A takes ownership
    auto a = make_shared<MockA>(widget);
}

/**
 * Test Probing and Validation (documented example, more or less)
 */
TEST(HelperTest, basics)
{
    auto widget = new MockWidget(); //A takes ownership

    PROBE(*widget, isReady).toReturn(true);
    PROBE(*widget, performAction).toDo([](int i) { ASSERT_EQ(i, 1); });

    auto a = make_shared<MockA>(widget);
    PROBE(*a, frobulate).toDo([&]() {
            if (widget->isReady())
                widget->performAction(1);
    });

    a->frobulate();

    ASSERT_TRUE(VALIDATE(*widget, isReady).called());
    ASSERT_TRUE(VALIDATE(*widget, performAction).called(1));
}

/**
 * Test Probing and Validation (relaxed mock example 1)
 */
TEST(HelperTest, basics_relaxed_in_order)
{
    auto widget = new RelaxedMockWidget(); //A takes ownership

    PROBE(*widget, isReady).toReturn(true);
    PROBE(*widget, performAction).toDo([](int i) { ASSERT_EQ(i, 1); });

    auto a = make_shared<MockA>(widget);
    PROBE(*a, frobulate).toDo([&]() {
            if (widget->isReady())
                widget->performAction(1);
    });

    a->frobulate();

    //test the invocations in order
    ASSERT_TRUE(VALIDATE(*widget, isReady).called());
    ASSERT_TRUE(VALIDATE(*widget, performAction).called(1));

    //our test consumed all invocations
    ASSERT_EQ(0, widget->invocations().size());
}

/**
 * Test Probing and Validation out of order (relaxed mock example 1)
 */
TEST(HelperTest, basics_relaxed_out_of_order)
{
    auto widget = new RelaxedMockWidget(); //A takes ownership

    PROBE(*widget, isReady).toReturn(true);
    PROBE(*widget, performAction).toDo([](int i) { ASSERT_EQ(i, 1); });

    auto a = make_shared<MockA>(widget);
    PROBE(*a, frobulate).toDo([&]() {
            if (widget->isReady())
                widget->performAction(1);
    });

    a->frobulate();

    //test the invocations in order
    ASSERT_TRUE(VALIDATE(*widget, performAction).called(1));
    ASSERT_TRUE(VALIDATE(*widget, isReady).called());

    //our test consumed all invocations
    ASSERT_EQ(0, widget->invocations().size());
}

/**
 * Test Probing and Validation with Ignore (example 3)
 */
TEST(HelperTest, basics_with_ignore)
{
    auto widget = new MockWidget(); //A takes ownership

    PROBE(*widget, isReady).toReturn(true);
    PROBE(*widget, performAction).toDo([](int i) { ASSERT_EQ(i, 1); });

    auto a = make_shared<MockA>(widget);
    PROBE(*a, frobulate).toDo([&]() {
            if (widget->isReady())
                widget->performAction(1);
    });

    a->frobulate();

    ASSERT_TRUE(VALIDATE(*widget, isReady).called());
    ASSERT_TRUE(VALIDATE(*widget, performAction).called(Ignore()));
}

/**
 * Test Probing and Validation with lambda expressions (example 4)
 */
TEST(HelperTest, basics_with_lambda)
{
    auto widget = new MockWidget(); //A takes ownership

    PROBE(*widget, isReady).toReturn(true);

    auto a = make_shared<MockA>(widget);
    PROBE(*a, frobulate).toDo([&]() {
            if (widget->isReady())
                widget->performAction(6); //note that this is > 5
    });

    a->frobulate();

    ASSERT_TRUE(VALIDATE(*widget, isReady).called());
    ASSERT_TRUE(VALIDATE(*widget, performAction).called([](int x) { return x > 5; }));
}

/**
 * Test validation on an empty invocation list.
 */
TEST(HelperTest, validation_empty)
{
    auto widget = new RelaxedMockWidget(); //A takes ownership
    auto a = make_shared<MockA>(widget);

    ASSERT_FALSE(VALIDATE(*widget, isReady).called());
}

/**
 * Test validation on a non-empty invocation list without the given invocation.
 */
TEST(HelperTest, validation_none)
{
    auto widget = new RelaxedMockWidget(); //A takes ownership
    auto a = make_shared<MockA>(widget);

    PROBE(*a, frobulate).toDo([&]() {
        widget->performAction(1);
    });

    //perform the frobulation operation.
    a->frobulate();

    //there should now be one invocation
    ASSERT_EQ(1, widget->invocations().size());

    //it isn't our invocation
    ASSERT_FALSE(VALIDATE(*widget, isReady).called());

    //there should still be one invocation
    ASSERT_EQ(1, widget->invocations().size());
}

/**
 * Should be able to instantiate and use MockB interface with constant
 * functions
 */
TEST(HelperTest, const_member_functions)
{
    auto b = make_shared<MockB>();

    ASSERT_FALSE(VALIDATE(*b, frobulate).called());
    ASSERT_FALSE(VALIDATE(*b, testIt).called(0));

    b->frobulate();
    b->testIt(0);

    EXPECT_TRUE(VALIDATE(*b, frobulate).called());
    EXPECT_TRUE(VALIDATE(*b, testIt).called(0));
}

/**
 * Should be able to store values to references.
 */
TEST(HelperTest, reference_removal)
{
    const string EXPECTED_STRING("This is a test.");
    auto c = make_shared<MockC>();

    ASSERT_FALSE(VALIDATE(*c, testRef).called(EXPECTED_STRING));

    //create a temporary
    string x = EXPECTED_STRING;

    c->testRef(x);

    //mutate this temporary
    x = "Some other value.";

    EXPECT_TRUE(VALIDATE(*c, testRef).called(EXPECTED_STRING));
}

/**
 * Should be able to mock polymorphic functions.
 */
TEST(HelperTest, polymorphic_mock)
{
    const int EXPECTED_INT = 31;
    const string EXPECTED_STRING("This is a test.");
    auto c = make_shared<MockPoly>();

    ASSERT_FALSE(VALIDATE(*c, testPolyString).called(EXPECTED_STRING));
    ASSERT_FALSE(VALIDATE(*c, testPolyInt).called(EXPECTED_INT));

    //create a temporary
    string x = EXPECTED_STRING;
    int y = EXPECTED_INT;

    c->testPoly(x);
    c->testPoly(y);

    //mutate this temporary
    x = "Some other value.";
    y = 21;

    EXPECT_TRUE(VALIDATE(*c, testPolyString).called(EXPECTED_STRING));
    EXPECT_TRUE(VALIDATE(*c, testPolyInt).called(EXPECTED_INT));
}
