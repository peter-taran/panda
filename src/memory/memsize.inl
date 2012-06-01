
#pragma once



Memsize::Memsize():
    _offs(0)
{}

Memsize::Memsize(const Uninitialized&)
{}

Memsize::Memsize(Raw from):
    _offs(from)
{}

Memsize::Memsize(const Memsize& from):
    _offs(from._offs)
{}

Memsize& Memsize::operator=(const Memsize& from)
{
    _offs = from._offs;
    return *this;
}

Memsize::Raw Memsize::raw() const
{
    return _offs;
}

Bool Memsize::operator<(const Memsize &y) const
{
    return _offs < y._offs;
}

Bool Memsize::operator<(const Raw &y) const
{
    return _offs < y;
}

Bool Memsize::operator==(const Memsize &y) const
{
    return _offs == y._offs;
}

Bool Memsize::operator==(const Raw &y) const
{
    return _offs == y;
}

Memsize& Memsize::operator++()
{
    ++_offs;
    return *this;
}

Memsize& Memsize::operator--()
{
    --_offs;
    return *this;
}

Memsize& Memsize::operator+=(const Memsize& y)
{
    _offs += y._offs;
    // TODO: check for overflow
    return *this;
}

Memsize& Memsize::operator-=(const Memsize& y)
{
    _offs -= y._offs;
    // TODO: check for underflow
    return *this;
}
