
MemArea::MemArea()
{}

MemArea::MemArea(Uninitialized):
    _start(uninitialized), _afterEnd(uninitialized)
{}

MemArea::MemArea(Addr start, Adif size):
    _start(start), _afterEnd(start+size)
{}

MemArea::MemArea(Addr start, Addr afterEnd):
    _start(start), _afterEnd(afterEnd)
{}

MemArea::MemArea(const MemArea &from):
    _start(from._start), _afterEnd(from._afterEnd)
{}

MemArea& MemArea::operator=(const MemArea &from)
{
    _start    = from._start;
    _afterEnd = from._afterEnd;
    return *this;
}

Addr MemArea::start() const
{
    return _start;
}

Addr MemArea::afterEnd() const
{
    return _afterEnd;
}

Adif MemArea::size() const
{
    return _afterEnd - _start;
}

Addr MemArea::byoffset(Adif offset) const
{
    return operator[](offset);
}

bool MemArea::operator<(const MemArea &y) const
{
    return _start < y._start;
}

bool MemArea::addrInside(Addr address) const
{
    return address >= _start && address < _afterEnd;
}
