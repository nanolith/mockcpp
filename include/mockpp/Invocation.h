#ifndef  MOCKPP_INVOCATION_HEADER_GUARD
# define MOCKPP_INVOCATION_HEADER_GUARD

#include <cstring>
#include <list>
#include <memory>
#include <tuple>
#include <utility>

namespace mockpp {

    /**
     * BaseInvocation is a base type that allows simple RTTI tracking of mocked
     * function call invocations.
     */
    class BaseInvocation
    {
    public:
        /**
         * BaseInvocation constructor.  Cache the hash code of the invocation.
         */
        BaseInvocation(std::size_t _hashCode)
            : hashCode_(_hashCode)
        {
        }

        /**
         * Virtual destructor for proper cleanup.
         */
        virtual ~BaseInvocation()
        {
        }

        /**
         * Get the unique hash code for this invocation type.
         */
        std::size_t hashCode() const
        {
            return hashCode_;
        }

    private:
        std::size_t hashCode_;
    };

    /**
     * Invocation is a base type that allows simple RTTI tracking of mocked
     * function call invocations.
     */
    template<
        typename BaseType,
        typename... ArgumentTypes> 
    class Invocation : public BaseInvocation
    {
    public:
        using ArgsType = std::tuple<ArgumentTypes...>;

        /**
         * Create an invocation from a list of arguments.
         */
        Invocation(ArgumentTypes... _args)
            : BaseInvocation(typeid(Invocation).hash_code())
            , args_(_args...)
        {
        }

        /**
         * Return the list of arguments as a tuple.
         */
        const ArgsType args() const
        {
            return args_;
        }

    private:
        ArgsType args_;
    };

    /**
     * A reference counted pointer to a particular invocation.
     */
    typedef
    std::shared_ptr<BaseInvocation>
    BaseInvocationPtr;

    /**
     * A list of invocations, which can be scanned for matching assertions in
     * unit tests.
     */
    typedef
    std::list<BaseInvocationPtr>
    InvocationList;

} /* namespace mockpp */

#endif //MOCKPP_INVOCATION_HEADER_GUARD
