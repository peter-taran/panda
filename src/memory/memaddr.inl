
#pragma once



Memaddr::Memaddr():
    _addr(0)
{}

Memaddr::Memaddr(const Uninitialized&)
{}

Memaddr::Memaddr(const void* const from):
    _addr(const_cast<void*>(from))
{}

Memaddr::Memaddr(const Memaddr& from):
    _addr(from._addr)
{}

Memaddr& Memaddr::operator=(const Memaddr& from)
{
    _addr = from._addr;
    return *this;
}

void* Memaddr::raw() const
{
    return _addr;
}

bool Memaddr::operator<(const Memaddr &y) const
{
    return _addr < y._addr;
}

bool Memaddr::operator==(const Memaddr &y) const
{
    return _addr == y._addr;
}

template<class Object>
Object& Memaddr::objAt() const
{
    return *static_cast<Object*>(_addr);
}

Memaddr& Memaddr::operator++()
{
    _addr = static_cast<Byte*>(_addr) + 1;
    return *this;
}

Memaddr& Memaddr::operator--()
{
    _addr = static_cast<Byte*>(_addr) - 1;
    return *this;
}

Memaddr& Memaddr::operator+=(const Memoffs& y)
{
    _addr = static_cast<Byte*>(_addr) + y.raw();
    return *this;
}

Memaddr& Memaddr::operator-=(const Memoffs& y)
{
    _addr = static_cast<Byte*>(_addr) - y.raw();
    return *this;
}

Memoffs Memaddr::operator-(const Memaddr& y) const
{
    Memoffs result(static_cast<Byte*>(_addr) - static_cast<Byte*>(y._addr));
    return result;
}
