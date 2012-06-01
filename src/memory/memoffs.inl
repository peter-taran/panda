
#pragma once



Memoffs::Memoffs():
    _offs(0)
{}

Memoffs::Memoffs(const Uninitialized&)
{}

/*Memoffs::Memoffs(const Memoffs::Int& from):
    _offs(from.raw())
{}

Memoffs::Memoffs(const UnsignedInt& from):
    _offs( static_cast<Raw>(from.raw()) )
{}*/

Memoffs::Memoffs(Raw from):
    _offs(from)
{}

Memoffs::Memoffs(const Memoffs& from):
    _offs(from._offs)
{}

Memoffs& Memoffs::operator=(const Memoffs& from)
{
    _offs = from._offs;
    return *this;
}

/*Memoffs::Int Memoffs::asInt() const
{
    return Int(_offs);
}

Memoffs::UnsignedInt Memoffs::asUnsigned() const
{
    return UnsignedInt( static_cast<UnsignedInt::Raw>(_offs) );
}*/

Memoffs::Raw Memoffs::raw() const
{
    return _offs;
}

Bool Memoffs::operator<(const Memoffs &y) const
{
    return _offs < y._offs;
}

Bool Memoffs::operator<(const Raw &y) const
{
    return _offs < y;
}

Bool Memoffs::operator==(const Memoffs &y) const
{
    return _offs == y._offs;
}

Bool Memoffs::operator==(const Raw &y) const
{
    return _offs == y;
}

Memoffs& Memoffs::operator++()
{
    ++_offs;
    return *this;
}

Memoffs& Memoffs::operator--()
{
    --_offs;
    return *this;
}

Memoffs Memoffs::operator-() const
{
    Memoffs result(-_offs);
    return result;
}

Memoffs& Memoffs::operator+=(const Memoffs& y)
{
    _offs += y._offs;
    return *this;
}

Memoffs& Memoffs::operator-=(const Memoffs& y)
{
    _offs -= y._offs;
    return *this;
}
