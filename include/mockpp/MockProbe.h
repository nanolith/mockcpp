#ifndef  MOCKPP_MOCK_PROBE_HEADER_GUARD
# define MOCKPP_MOCK_PROBE_HEADER_GUARD

#include <functional>

namespace mockpp {

    /**
     * The mock probe helper class allows the user to compose custom behaviors
     * for mocked functions.
     */
    template<
        typename ReturnType,
        typename... ArgumentTypes>
    class MockProbe
    {
    public:
        /**
         * Default constructor.
         */
        MockProbe()
            : override_(nullptr)
            , returnVal_()
        {
        }

        /**
         * Perform the probed operation, or return the defined return type if not
         * probed.
         */
        ReturnType operator()(ArgumentTypes... args)
        {
            if (override_ != nullptr)
            {
                return override_(args...);
            }
            else
            {
                return returnVal_;
            }
        }

        /**
         * Allow the user to override the default return type.
         */
        void toReturn(const ReturnType& val)
        {
            returnVal_ = val;
        }

        /**
         * Allow the user to override the default action.
         */
        void toDo(std::function<ReturnType (ArgumentTypes...)> func)
        {
            override_ = func;
        }

    private:
        std::function<ReturnType (ArgumentTypes...)> override_;
        bool overrideSet_;

        ReturnType returnVal_;
    };

    /**
     * The mock probe helper class allows the user to compose custom behaviors
     * for mocked functions.
     */
    template<
        typename... ArgumentTypes>
    class MockProbe<void, ArgumentTypes...>
    {
    public:
        MockProbe()
            : override_(nullptr)
        {
        }

        ///Perform the probed operation, or do nothing if not probed.
        void operator()(ArgumentTypes... args)
        {
            if (override_ != nullptr)
            {
                override_(args...);
            }
        }

        ///Override the default action.
        void toDo(std::function<void (ArgumentTypes...)> func)
        {
            override_ = func;
        }

    private:
        std::function<void (ArgumentTypes...)> override_;
    };

} /* namespace mockpp */

#endif //MOCKPP_MOCK_PROBE_HEADER_GUARD
