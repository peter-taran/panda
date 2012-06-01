
#pragma once



namespace Impl
{
    extern void MemEmpty_init(Mem::Implementation& impl);
    extern void MemDynBuff_init(Mem::Implementation& impl, const Memoffs& size,
                                Bool fillByZeroes);

    template<Memoffs::Raw buffSize_>
    struct MembuffWrapper: Mem::Methods
    {
        static const Memoffs::Raw buffSize = buffSize_;

        const Membuff<buffSize>& _wrapped;

        MembuffWrapper(const Membuff<buffSize>& from):
            _wrapped(from)
        {}

        virtual ~MembuffWrapper()
        {}

        virtual void clone(Mem::Implementation& cloneTo)
        {
            MemDynBuff_init(cloneTo, buffSize, false);
            memcpy(cloneTo->area().start().raw(), &_wrapped, buffSize);
        }

        virtual Memoffs size()
        {
            return buffSize;
        }

        virtual Memarea area()
        {
            Memarea result = _wrapped.area();
            return result;
        }

        virtual Bool wrapper()
        {
            return true;
        }
    };
}

Mem::Mem(const Memoffs& size)
{
    if( 0 == size )
        Impl::MemEmpty_init(_impl);
    else
        Impl::MemDynBuff_init(_impl, size, true);
}

Mem::Mem(const Memoffs& size, const Uninitialized&)
{
    if( 0 == size )
        Impl::MemEmpty_init(_impl);
    else
        Impl::MemDynBuff_init(_impl, size, false);
}

template<Memoffs::Raw buffSize>
Mem::Mem(const Membuff<buffSize>& from)
{
    _impl._stor.construct< Impl::MembuffWrapper<buffSize> >(from);
}

Mem::Mem(const Mem& from):
    _impl(from._impl)
{}

Mem& Mem::operator=(const Mem& from)
{
    _impl = from._impl;
    return *this;
}

void Mem::swap(Mem& y)
{
    (std::swap)(_impl, y._impl);
}

Mem::~Mem()
{}

Bool Mem::operator==(const Mem& y) const
{
    return area().memEqual(y.area());
}

Memoffs Mem::size() const
{
    Memoffs result = _impl->size();
    return result;
}

Bool Mem::empty() const
{
    return 0 == _impl->size();
}

Memarea Mem::area() const
{
    Memarea result = _impl->area();
    return result;
}

Mem::operator Memarea() const
{
    Memarea result = _impl->area();
    return result;
}

Memaddr Mem::addrAt(const Memoffs& offset) const
{
    Memaddr result = _impl->area().addrAt(offset);
    return result;
}

Memaddr Mem::addrAt(const Memoffs& offset, const Dontcheck&) const
{
    Memaddr result = _impl->area().addrAt(offset, dontcheck);
}

template<class Object>
Object& Mem::objAt(const Memoffs& offset) const
{
    return _impl->area().objAt<Object>(offset);
}

template<class Object>
Object& Mem::objAt(const Memoffs& offset, const Dontcheck&) const
{
    return _impl->area().objAt<Object>(offset, dontcheck);
}

Bool Mem::wrapper() const
{
    return _impl->wrapper();
}

Mem::This& Mem::unwrap()
{
    if( !_impl->wrapper() )
        return *this;
    Implementation temp;
    _impl->clone(temp);
    (std::swap)(temp, _impl);
    return *this;
}

Mem::Mem(Implementation*& implPointer)
{
    implPointer = &_impl;
}
