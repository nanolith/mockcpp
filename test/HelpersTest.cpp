#include <gtest/gtest.h>
#include <memory>
#include <mockpp/mockpp.h>

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
 * Mock the test interface.
 */
class MockA : public A, public mockpp::Mock<A>
{
public:
    MockA(Widget* widget) : A(widget) { }

    MOCK_FUNCTION_VOID(frobulate);
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
