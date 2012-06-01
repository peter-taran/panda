
#pragma once



template<Memoffs::Raw size>
Membuff<size>::Membuff()
{
    Impl::StaticMemArea<size>::zero(&_data);
}

template<Memoffs::Raw size>
Membuff<size>::Membuff(const Uninitialized&)
{}

template<Memoffs::Raw size>
Membuff<size> Membuff<size>::filled(const Byte& filler)
{
    Membuff<size> result = uninitialized;
    result.fill(filler);
    return result;
}

template<Memoffs::Raw size>
template<class Object>
Membuff<size>::Membuff(const Object& object)
{
    // TODO: check object to be POD: ensure_static(Type::POD<Object>)
    ensure_static(sizeof(object) == size);
    Impl::StaticMemArea<size>::copy(&_data, &object);
}

template<Memoffs::Raw size>
Membuff<size>::Membuff(const Membuff& from)
{
    Impl::StaticMemArea<size>::copy(&_data, &from._data);
}

template<Memoffs::Raw size>
Membuff<size>& Membuff<size>::operator=(const Membuff& from)
{
    if( &from == this )
        return *this;
    this->~Membuff();
    new(this) Membuff(from);
    return *this;
}

template<Memoffs::Raw size>
typename Membuff<size>::This& Membuff<size>::fill(Byte byte)
{
    if( byte == 0 )
    {
        Impl::StaticMemArea<size>::zero(&_data);
    }
    else
    {
        for(Memoffs i = 0; i < size; ++i)
            _data[i.raw()] = byte;
    }
    return *this;
}

template<Memoffs::Raw size>
Bool Membuff<size>::operator==(const Membuff& y) const
{
    return Impl::StaticMemArea2<size, size>::equal(&_data, &y._data);
}

template<Memoffs::Raw size>
Membuff<size>::operator Memarea() const
{
    Memarea result(&_data, _data+size);
    return result;
}

template<Memoffs::Raw size>
Memarea Membuff<size>::area() const
{
    Memarea result(&_data, _data+size);
    return result;
}

template<Memoffs::Raw size>
Memaddr Membuff<size>::addrAt(const Memoffs& offset) const
{
    ensure(offset < size);
    return addrAt(offset, dontcheck);
}

template<Memoffs::Raw size>
Memaddr Membuff<size>::addrAt(const Memoffs& offset, const Dontcheck&) const
{
    Memaddr result(Memaddr(&_data) + offset);
    return result;
}

template<Memoffs::Raw size>
template<class Object>
const Object& Membuff<size>::cobjAt(const Memoffs& offset) const
{
    ensure(offset >= 0 && offset+sizeof(Object) <= size);
    return objAt<Object>(offset, dontcheck);
}

template<Memoffs::Raw size>
template<class Object>
const Object& Membuff<size>::cobjAt(const Memoffs& offset, const Dontcheck&) const
{
    return *static_cast<const Object*>(static_cast<const void*>(&_data[offset.raw()]));
}

template<Memoffs::Raw size>
template<class Object>
Object& Membuff<size>::objAt(const Memoffs& offset)
{
    ensure(offset >= 0 && offset+sizeof(Object) <= size);
    return objAt<Object>(offset, dontcheck);
}

template<Memoffs::Raw size>
template<class Object>
Object& Membuff<size>::objAt(const Memoffs& offset, const Dontcheck&)
{
    return *static_cast<Object*>(static_cast<void*>(&_data[offset.raw()]));
}
