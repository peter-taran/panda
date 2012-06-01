
#pragma once



Memarea::Memarea()
{}

Memarea::Memarea(const Uninitialized&):
    _start(uninitialized), _size(uninitialized)
{}

Memarea::Memarea(const Memaddr& start, const Memaddr& end):
    _start(start), _size(end - start)
{
    ensure(end >= start);
}

Memarea::Memarea(const Memaddr& start, const Memoffs& size):
    _start(start), _size(size)
{}

Memarea::Memarea(const Memarea& from):
    _start(from._start), _size(from._size)
{}

Memarea& Memarea::operator=(const Memarea& from)
{
    if( this != &from )
    {
        _start = from._start;
        _size  = from._size;
    }
    return *this;
}

Bool Memarea::operator==(const Memarea& y) const
{
    if( _size != y._size )
        return false;
    if( _size == 0 )
        return true;
    return _start == y._start;
}

Bool Memarea::memEqual(const Memarea& y) const
{
    Bool result = Impl::memoryEqual(_start, _size, y._start, y._size);
    return result;
}

void Memarea::memCopyTo(const Memaddr& to) const
{
    Impl::memoryCopy(to, _start, _size);
}

void Memarea::memCopyTo(const Memarea& to) const
{
    ensure(_size == to._size);
    memCopyTo(to.start());
}

Memaddr Memarea::start() const
{
    return _start;
}

Memaddr Memarea::end() const
{
    return _start + _size;
}

Memoffs Memarea::size() const
{
    return _size;
}

Bool Memarea::empty() const
{
    return 0 == _size;
}

template<class Object>
Object& Memarea::objAt(const Memoffs& offset) const
{
    ensure(offset+sizeof(Object) <= _size);
    return objAt<Object>(offset, dontcheck);
}

template<class Object>
Object& Memarea::objAt(const Memoffs& offset, const Dontcheck&) const
{
    return (_start+offset).objAt<Object>();
}

Memaddr Memarea::addrAt(const Memoffs& offset) const
{
    ensure(offset < _size); // TODO: а может давать вычислять и адрес за пределами области?
    return addrAt(offset, dontcheck);
}

Memaddr Memarea::addrAt(const Memoffs& offset, const Dontcheck&) const
{
    Memaddr result(_start+offset);
    return result;
}

Memarea Memarea::head(const Memoffs& offset) const
{
    if( offset < 0 )
    {
        ensure(-offset <= _size);
        Memarea result(_start, _size+offset);
        return result;
    }
    else
    {
        ensure(offset <= _size);
        Memarea result(_start, _start+offset);
        return result;
    }
}

Memarea Memarea::tail(const Memoffs& offset) const
{
    if( offset < 0 )
    {
        ensure(-offset <= _size);
        Memarea result(_start+_size+offset, -offset);
        return result;
    }
    else
    {
        ensure(offset <= _size);
        Memarea result(_start+offset, _size-offset);
        return result;
    }
}

std::pair<Memarea, Memarea> Memarea::split(const Memoffs& offset) const
{
    std::pair<Memarea, Memarea> result(
        head(offset),
        tail(offset)
    );
    return result;
}

Memarea Memarea::extractHead(const Memoffs& offset)
{
    Memarea result(head(offset));
    *this = tail(offset); // TODO: optimize this
    return result;
}

Memarea Memarea::extractTail(const Memoffs& offset)
{
    Memarea result(tail(offset));
    *this = head(offset); // TODO: optimize this
    return result;
}
