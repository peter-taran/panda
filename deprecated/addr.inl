
Addr::Addr():
    _addr(0)
{}

Addr::Addr(Uninitialized)
{}

Addr::Addr(const void* address):
    _addr(static_cast<const char*>(address))
{}

Addr::Addr(const Addr &from):
    _addr(from._addr)
{}

Addr& Addr::operator=(const Addr &from)
{
    _addr = from._addr;
    return *this;
}

Addr Addr::sys(Umem address)
{
    return Addr(reinterpret_cast<void*>(address));
}

void* Addr::asVoid() const
{
    return const_cast<char*>(_addr);
}

char* Addr::asPtr() const
{
    return const_cast<char*>(_addr);
}

Umem Addr::asFlat() const
{
    return reinterpret_cast<Umem>(static_cast<const void*>(_addr));
}

Addr& Addr::operator+=(Adif offset)
{
    _addr += offset._diff;
    return *this;
}

Addr& Addr::operator+=(Umem offset)
{
    _addr += offset;
    return *this;
}

Addr& Addr::operator-=(Adif offset)
{
    _addr -= offset._diff;
    return *this;
}

Addr& Addr::operator-=(Umem offset)
{
    _addr -= offset;
    return *this;
}

Addr& Addr::operator++()
{
    ++_addr;
    return *this;
}

Addr& Addr::operator--()
{
    --_addr;
    return *this;
}

Addr& Addr::alignUp(Umem exp2bound)
{
    Umem addr = ::roundUp(reinterpret_cast<Umem>(_addr), exp2bound);
    _addr = reinterpret_cast<const char *>(addr);
    return *this;
}

Addr Addr::alignedUp(Umem exp2bound) const
{
    Addr result(*this);
    result.alignUp(exp2bound);
    return result;
}

Addr& Addr::alignDown(Umem exp2bound)
{
    Umem addr = ::roundDown(reinterpret_cast<Umem>(_addr), exp2bound);
    _addr = reinterpret_cast<const char *>(addr);
    return *this;
}

Addr Addr::alignedDown(Umem exp2bound) const
{
    Addr result(*this);
    result.alignDown(exp2bound);
    return result;
}

Adif Addr::operator-(const Addr &y) const
{
    Adif result(_addr - y._addr);
    return result;
}

bool Addr::operator<(const Addr &y) const
{
    return _addr < y._addr;
}

bool Addr::operator==(const Addr &y) const
{
    return _addr == y._addr;
}

bool Addr::operator!() const
{
    return 0 == _addr;
}

Addr::operator Addr::BoolCheckable() const
{
    return 0 == _addr ? 0 : &Addr::operator!;
}
