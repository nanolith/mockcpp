#ifndef  MOCKPP_DETAIL_ARGUMENT_MATCHER_HEADER_GUARD
# define MOCKPP_DETAIL_ARGUMENT_MATCHER_HEADER_GUARD

#include <functional>
#include <mockpp/Matchers.h>
#include <tuple>

namespace mockpp { namespace detail {

    /**
     * ArgumentMatcher is a recursively defined functor which accepts a list of
     * arguments, and matches against either these arguments, a defined Matcher,
     * or a lambda expression that returns true or false.  The argument for the
     * ArgumentMatcher functor is an argument of the given type, and the result
     * is true or false.
     */
    template<
        int offset,
        typename TupleType>
    struct ArgumentMatcher
    {
        //Helper for the argument type
        typedef
        typename std::tuple_element<offset, TupleType>::type
        ArgumentType;

        /**
         * The single element constructor.
         */
        ArgumentMatcher(
            ArgumentType argument)
        {
            matcher_ =
                [=](const TupleType& toCompare) -> bool {
                    return std::get<offset>(toCompare) == argument;
                };
        }

        /**
         * The default constructor creates an ArgumentMatcher which matches
         * against the given value.
         */
        template<
            typename... Args>
        ArgumentMatcher(
            ArgumentType argument,
            Args... args)
        {
            auto tailMatcher = ArgumentMatcher<offset+1, TupleType>(args...);

            matcher_ =
                [=](const TupleType& toCompare) -> bool {
                    return std::get<offset>(toCompare) == argument
                        && tailMatcher(toCompare);
                };
        }

        /**
         * This constructor ignores the last argument.
         */
        ArgumentMatcher(Ignore)
        {
            matcher_ =
                [](const TupleType& toCompare) -> bool {
                    return true;
                };
        }

        /**
         * This constructor ignores the argument.
         */
        template<
            typename... Args>
        ArgumentMatcher(Ignore, Args... args)
        {
            auto tailMatcher = ArgumentMatcher<offset+1, TupleType>(args...);

            matcher_ =
                [=](const TupleType& toCompare) -> bool {
                    return true
                        && tailMatcher(toCompare);
                };
        }

        /**
         * This constructor allows the last argument to be a user specified
         * functor.
         */
        ArgumentMatcher(
            std::function<bool (ArgumentType)> userFunctor)
        {
            matcher_ =
                [=](const TupleType& toCompare) -> bool {
                    return userFunctor(std::get<offset>(toCompare));
                };
        }

        /**
         * This constructor allows the matching functor to be specified by the
         * user.
         */
        template<
            typename... Args>
        ArgumentMatcher(
            std::function<bool (ArgumentType)> userFunctor,
            Args... args)
        {
            auto tailMatcher = ArgumentMatcher<offset+1, TupleType>(args...);

            matcher_ =
                [=](const TupleType& toCompare) -> bool {
                    return userFunctor(std::get<offset>(toCompare))
                        && tailMatcher(toCompare);
                };
        }

        /**
         * This functor operator wraps our internal lambda expression.
         */
        bool operator()(const TupleType& tuple) const
        {
            return matcher_(tuple);
        }

    private:
        std::function<bool (const TupleType& toCompare)> matcher_;
    };

} /* namespace detail */ } /* namespace mockpp */

#endif //MOCKPP_DETAIL_ARGUMENT_MATCHER_HEADER_GUARD
