Mock++: A Portable Mocking Framework for C++
============================================

The Mock++ framework provides portable mocking support for unit testing C++
applications.  This framework makes use of concepts available in C++11, such as
variadic templates and tuples, and combines these with simple macros to make the
creation and use of mock objects as easy as possible in a language that lacks
runtime reflection.

Other frameworks may take advantage of non-portable vtable implementation
details, but this framework should work with any compiler that is compliant with
the C++11 standard.  Using this framework does not require a migration to C++11,
however, as code can be written in C++98 or whichever subsets one chooses to
use. Only the unit tests themselves must make use of these features.

##Usage Example

The following example illustrates the use of this library.  As with any OO code
that can be mocked, one must first create an interface or abstract base class:

```c++
class Widget
{
public:
    virtual bool isReady() = 0;
    virtual void performAction(int) = 0;
    virtual ~Widget() = 0;
};
```

Let's assume that this interface is being passed to an object we intend to unit
test.  We'll call this object A.

```c++
class A
{
public:
    ///Construct an A using a Widget.  A owns this widget.
    A(Widget*);

    ///frobulate the widget
    void frobulate();

private:
    std::shared_ptr<Widget> widget_;
};
```

Now, we can pass a mock Widget to A, but first we need to create a mock of
Widget.  Unlike reflective languages, there is a bit of scaffolding, but helper
macros make this simple.

```c++
class MockWidget : public Widget, public mockpp::Mock<Widget>
{
public:

    ~MockWidget() { }

    MOCK_FUNCTION(bool, isReady);
    MOCK_FUNCTION_VOID_ARGS(performAction, int);
};
```

Within our unit test, we can construct the MockWidget, and control how it works.

```c++
    using mockpp;

    auto widget = new MockWidget();

    PROBE(widget, isReady).toReturn(true);
    PROBE(widget, performAction).toDo([](int i) { ASSERT_EQ(i, 1); });
    auto aObj = make_shared<A>(widget); //a takes ownership of widget

    aObj->frobulate();

    //assuming Google Test semantics here.
    ASSERT_TRUE(VALIDATE(widget, isReady).called());
    ASSERT_TRUE(VALIDATE(widget, performAction).withArgs(1).called());
```

Mocks have several different selectors, which allow the user to access
functionality.  The first selector here is PROBE.  The probe selector allows us
to control behavior of the mock object.  In this case, we probe the isReady
function to return true when called. By default, a mocked function will return
whichever value is considered the default value initialization for a constructed
type.  In this case, bools return false.  Ints return 0.  Pointers return
nullptr.

The mock is then passed to the constructor of A.  When the frobulate method of A
is called, it uses the mock object.  We can then validate its use of the mock by
using the validate selector.  This selector allows us to verify that methods in
the mock object were called, and we can even test the values passed to the
methods by adding them to the call.  The default behavior of the validate
selector is to test each invocation in order.  For instance, this test would
have failed if performAction were called before isReady.  Also, the called()
method fails if the arguments passed to the selector are invalid.  So, if the
above assertion were changed to validate(widget).performAction(2).called(), the
result would be false, which would cause the Google Test assertion to fail.

##Header Naming Convention

Headers in mockpp are differentiated between class headers and package headers.
Class headers always begin with a capital letter, as do the classes they
contain.  Class headers are always named the same as the type they contain.
Package headers are convenient utility headers that contain all classes in a
given namespace.  Finally, package forwarding headers contain just the forward
declarations of classes in a given namespace, which is convenient for handling
cyclic resolution issues, or for facilitating a faster compilation on systems
that don't support precompiled headers.

mockpp/mockpp.h effectively includes world.  This is a quick and dirty way to
get started.
