#ifndef  MOCKPP_MOCK_VALIDATOR_HEADER_GUARD
# define MOCKPP_MOCK_VALIDATOR_HEADER_GUARD

#include <functional>
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

        bool called(ArgumentTypes... args)
        {
            auto expectedArgs = std::tuple<ArgumentTypes...>(args...);

            return
                mockRef.called([&](const BaseInvocation* inv) -> bool {
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
                        ptr->args() == expectedArgs;
                });
        }

    private:
        BaseMock& mockRef;
    };

} /* namespace mockpp */

#endif //MOCKPP_MOCK_VALIDATOR_HEADER_GUARD
