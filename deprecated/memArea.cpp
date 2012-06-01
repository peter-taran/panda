
#include "../include/cppdragon.h"


Addr MemArea::operator[](Adif offset) const
{
    Addr result = _start + offset;
    ensure(result <= _afterEnd);
    return result;
}

MemArea MemArea::begArea(Adif size_) const
{
    ensure(size_ <= size());
    return MemArea(_start, size_);
}

MemArea MemArea::begArea(Addr afterEnd) const
{
    ensure(afterEnd >= _start && afterEnd <= _afterEnd);
    return MemArea(_start, afterEnd);
}

MemArea MemArea::midArea(Adif offset, Adif size_) const
{
    ensure(offset+size_ <= size());
    return MemArea(_start+offset, size_);
}

MemArea MemArea::endArea(Adif size_) const
{
    ensure(size_ <= size());
    return MemArea(_afterEnd-size_, size_);
}

MemArea MemArea::endArea(Addr start) const
{
    ensure(start >= _start && start <= _afterEnd);
    return MemArea(start, _afterEnd);
}
