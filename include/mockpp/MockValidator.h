#ifndef  MOCKPP_MOCK_VALIDATOR_HEADER_GUARD
# define MOCKPP_MOCK_VALIDATOR_HEADER_GUARD

#include <functional>
#include <memory>
#include <mockpp/detail/ArgumentMatcher.h>
#include <mockpp/Matchers.h>
#include <mockpp/Mock.h>
#include <mockpp/Invocation.h>

namespace mockpp {

    /**
     * Forward declaration for ValidationBuilder.
     */
    template<
        typename ReturnType,
        typename... ArgumentTypes>
    class ValidationBuilder;

    /**
     * The mock validator helper class tracks invocations and provides a
     * builder framework for querying these invocations.
     */
    template<
        typename ReturnType,
        typename... ArgumentTypes>
    class MockValidator
    {
    public:
        /**
         * Add an invocation with the given arguments.
         */
        void addInvocation(BaseMock& mock, ArgumentTypes... args)
        {
            mock.invocations().push_back(
                std::make_shared< Invocation<MockValidator, ArgumentTypes...> >(
                    args...));
        }

        /**
         * Create a ValidationBuilder for this mock.
         */
        ValidationBuilder<ReturnType, ArgumentTypes...>
        validationBuilder(BaseMock& mock)
        {
            return
                ValidationBuilder<ReturnType, ArgumentTypes...>(mock);
        }
    };

    /**
     * The ValidationBuilder class provides a simple wrapper around a base mock
     * object so that validation queries can be performed against it.  In most
     * test code, this is created as a temporary to allow simplified matching
     * semantics.
     */
    template<
        typename ReturnType,
        typename... ArgumentTypes>
    class ValidationBuilder
    {
    public:
        ValidationBuilder(BaseMock& mock) : mockRef(mock) { }

        template<
            typename... ArgTypes>
        bool called(ArgTypes... args)
        {
            return
                mockRef.called(buildCallMatcher(args...));
        }

    protected:

        /**
         * Build a lambda expression for matching our arguments.
         */
        template<
            typename... ArgTypes>
        std::function<bool (const BaseInvocation*)>
        buildCallMatcher(ArgTypes... args)
        {
            auto argsMatcher =
                detail::ArgumentMatcher<0, std::tuple<ArgumentTypes...> >(args...);

            return [=](const BaseInvocation* inv) -> bool {
                //cast this invocation to our invocation type
                auto ptr =
                    dynamic_cast<
                        const Invocation<
                            MockValidator<ReturnType, ArgumentTypes...>,
                            ArgumentTypes...>* >(inv);

                //this was an invocation for a different function.
                if (ptr == nullptr)
                    return false;

                //it must match our expected args
                return
                    argsMatcher(ptr->args());
            };
        }

        /**
         * Build a lambda expression for matching our arguments.
         * This version handles no arguments.
         */
        std::function<bool (const BaseInvocation*)>
        buildCallMatcher()
        {
            return [=](const BaseInvocation* inv) -> bool {
                //cast this invocation to our invocation type
                auto ptr =
                    dynamic_cast<
                        const Invocation<
                            MockValidator<ReturnType, ArgumentTypes...>,
                            ArgumentTypes...>* >(inv);

                //if the pointer is not null, then it is an invocation for this
                //function.
                return
                    ptr != nullptr;
            };
        }

    private:
        BaseMock& mockRef;
    };

} /* namespace mockpp */

#endif //MOCKPP_MOCK_VALIDATOR_HEADER_GUARD
