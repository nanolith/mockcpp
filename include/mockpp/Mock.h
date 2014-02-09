#ifndef  MOCKPP_MOCK_HEADER_GUARD
# define MOCKPP_MOCK_HEADER_GUARD

#include <algorithm>
#include <functional>
#include <mockpp/Invocation.h>

namespace mockpp {

    /**
     * The base mock class contains an invocation list and some helper
     * functions.
     */
    class BaseMock
    {
    public:
        /**
         * Clear all invocation history from the mock object.
         */
        void clear()
        {
            invocations_.clear();
        }

        /**
         * accessor for the list of invocations
         */
        InvocationList& invocations()
        {
            return invocations_;
        }

        /**
         * accessor to return an invocation at the given offset
         */
        InvocationList::value_type& invocations(size_t offset)
        {
            auto iter = invocations_.begin();
            std::advance(iter, offset);

            return *iter;
        }

        /**
         * Called validator.  See if a particular invocation matcher matches an
         * invocation.
         */
        virtual bool called(
            std::function<bool (const BaseInvocation*)> matcher) = 0;

    private:
        InvocationList invocations_;
    };

    /**
     * Mock is a wrapper template that provides mocking facilities for a given
     * type.  Mock uses strict checking for invocations, meaning that assertions
     * based on invocations must be given in the order that they were made.
     * Users who wish for assertions without the strict order of evaluation
     * should used RelaxedMock.
     */
    template <
        typename MockedType>
    class Mock : public BaseMock
    {
    protected:

        /**
         * Perform strict order evaluation of method invocations using the
         * provided matcher.
         */
        virtual bool called(
            std::function<bool (const BaseInvocation*)> matcher)
        {
            if (invocations().empty())
                return false;

            auto v = invocations().front();
            invocations().pop_front();

            return
                matcher(v.get());
        }
    };

    /**
     * RelaxedMock is a wrapper template that provides mocking facilities for a
     * given type.  Mock uses relaxed checking for invocations, meaning that
     * assertions can be made in any order, but as with Mock, cannot be
     * duplicated.  This allows the code under unit test to be refactored in a
     * way that changes the order of invocation of mock methods without breaking
     * the unit test.
     */
    template <
        typename MockedType>
    class RelaxedMock : public BaseMock
    {
    protected:

        /**
         * Perform non-strict order evaluation of method invocations using the
         * provided matcher.
         */
        virtual bool called(
            std::function<bool (const BaseInvocation*)> matcher)
        {
            auto& inv = invocations();

            //no need to go further if the invocations are empty
            if (inv.empty())
                return false;

            //find an invocation that matches our matcher.
            auto v = std::find_if(
                        begin(inv),
                        end(inv),
                        [&](const BaseInvocationPtr& ptr) -> bool {
                            return matcher(ptr.get()); } );

            //stop if no matching entries were found
            if (v == inv.end())
                return false;

            //result found.  Remove it.
            inv.erase(v);

            //success
            return true;
        }
    };

} /* mockpp */

#endif //MOCKPP_MOCK_HEADER_GUARD
