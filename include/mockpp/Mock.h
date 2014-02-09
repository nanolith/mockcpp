#ifndef  MOCKPP_MOCK_HEADER_GUARD
# define MOCKPP_MOCK_HEADER_GUARD

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

} /* mockpp */

#endif //MOCKPP_MOCK_HEADER_GUARD
