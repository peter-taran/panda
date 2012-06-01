
Adif::Adif():
    _diff(0)
{}

Adif::Adif(Uninitialized)
{}

Adif::Adif(Umem difference):
    _diff(difference)
{}

Adif::Adif(const Adif &from):
    _diff(from._diff)
{}

Adif& Adif::operator=(const Adif &from)
{
    _diff = from._diff;
    return *this;
}

Umem Adif::asRaw() const
{
    return _diff;
}

bool Adif::zero() const
{
    return 0 == _diff;
}

Adif& Adif::operator++()
{
    ++_diff;
    return *this;
}

Adif& Adif::operator--()
{
    if( _diff > 0 )
        --_diff;
    return *this;
}

Adif& Adif::operator+=(Adif y)
{
    _diff += y._diff;
    return *this;
}

Adif& Adif::operator+=(Umem y)
{
    _diff += y;
    return *this;
}

Adif& Adif::operator-=(Adif y)
{
    _diff -= y._diff;
    return *this;
}

Adif& Adif::operator-=(Umem y)
{
    _diff -= y;
    return *this;
}

Adif& Adif::operator*=(Umem y)
{
    _diff *= y;
    return *this;
}

Adif& Adif::operator/=(Umem y)
{
    _diff /= y;
    return *this;
}

Adif& Adif::roundUp(Umem exp2bound)
{
    _diff = ::roundUp(_diff, exp2bound);
    return *this;
}

Adif Adif::roundedUp(Umem exp2bound) const
{
    Adif result(*this);
    return result.roundUp(exp2bound);
}

Adif Adif::roundedUp4() const
{
    Adif result(*this);
    return result.roundUp4();
}

Adif Adif::roundedUp8() const
{
    Adif result(*this);
    return result.roundUp8();
}

Adif Adif::roundedUp16() const
{
    Adif result(*this);
    return result.roundUp16();
}

Adif& Adif::roundUp4()
{
    _diff +=  LOWSETBITS(2);
    _diff &= ~LOWSETBITS(2);
    return *this;
}

Adif& Adif::roundUp8()
{
    _diff +=  LOWSETBITS(3);
    _diff &= ~LOWSETBITS(3);
    return *this;
}

Adif& Adif::roundUp16()
{
    _diff +=  LOWSETBITS(4);
    _diff &= ~LOWSETBITS(4);
    return *this;
}

bool Adif::operator<(Adif y) const
{
    return _diff < y._diff;
}

bool Adif::operator==(Adif y) const
{
    return _diff == y._diff;
}

bool Adif::operator<(Umem y) const
{
    return _diff < y;
}

bool Adif::operator>(Umem y) const
{
    return _diff > y;
}

bool Adif::operator==(Umem y) const
{
    return _diff == y;
}
