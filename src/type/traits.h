
#pragma once



namespace Type
{

    template<class This, class Base = Null>
    struct POD: Base // TODO: add different base classes here
    {};

}

#define PANDA_POD(This) \
    This() \
    This(const Uninitialized&); \
    This(const This& from); \
    This& operator=(const This& from)

namespace Impl
{
    template<class This, class Any>
    struct TF {};
}
