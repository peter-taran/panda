
#pragma once



template<class Value>
IntDivRes<Value>::IntDivRes(Value& result, const Value& remainder):
    _res(result), _rem(remainder)
{}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>::IntOf():
    _value(0)
{}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>::IntOf(const Uninitialized&)
{}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>::IntOf(Raw from):
    _value(from)
{}

template<class SignTag, unsigned byteCount, class Traits>
template<class From_SignTag, unsigned From_byteCount, class From_Traits>
IntOf<SignTag, byteCount, Traits>::IntOf(const IntOf<From_SignTag, From_byteCount, From_Traits>& from):
    _value(from._value)
{
    typedef IntOf<From_SignTag, From_byteCount, From_Traits> From;
    
    // if value can be out of our range, check for validity
    if( !(This::largest_static  >= From::largest_static &&   // TODO: ensure, this condition evaluated at compile time
          This::smallest_static <= From::smallest_static) )
        if( from < This::smallest() || from >= This::largest() )
            throw "out of bounds"; // TODO: replace with normal exception class
}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>::IntOf(const IntOf& from):
    _value(from._value)
{}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>&
    IntOf<SignTag, byteCount, Traits>::operator=(const IntOf& from)
{
    _value = from._value;
    return *this;
}

template<class SignTag, unsigned byteCount, class Traits>
typename IntOf<SignTag, byteCount, Traits>::Raw
    IntOf<SignTag, byteCount, Traits>::raw() const
{
    return _value;
}

template<class SignTag, unsigned byteCount, class Traits>
Bool IntOf<SignTag, byteCount, Traits>::operator==(const IntOf& y) const
{
    return _value == y._value;
}

template<class SignTag, unsigned byteCount, class Traits>
Bool IntOf<SignTag, byteCount, Traits>::operator<(const IntOf& y) const
{
    return _value < y._value;
}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>&
    IntOf<SignTag, byteCount, Traits>::operator++()
{
    ++_value;
    return *this;
}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>&
    IntOf<SignTag, byteCount, Traits>::operator--()
{
    --_value;
    return *this;
}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>&
    IntOf<SignTag, byteCount, Traits>::operator+=(const IntOf& y)
{
    return add(y);
}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>&
    IntOf<SignTag, byteCount, Traits>::operator-=(const IntOf& y)
{
    return subtract(y);
}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>&
    IntOf<SignTag, byteCount, Traits>::add(const IntOf& y)
{
    _plus<SignTag, byteCount>(_value, y._value);
    return *this;
}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>&
    IntOf<SignTag, byteCount, Traits>::add(const IntOf& y, const Dontcheck&)
{
    _value += y._value;
    return *this;
}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>&
    IntOf<SignTag, byteCount, Traits>::subtract(const IntOf& y)
{
    _minus<SignTag, byteCount>(_value, y._value);
    return *this;
}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>&
    IntOf<SignTag, byteCount, Traits>::subtract(const IntOf& y, const Dontcheck&)
{
    _value -= y._value;
    return *this;
}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>&
    IntOf<SignTag, byteCount, Traits>::operator*=(const IntOf& y)
{
    return multiply(y);
}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>&
    IntOf<SignTag, byteCount, Traits>::multiply(const IntOf& y)
{
    _multiply<SignTag, byteCount>(_value, y._value);
    return *this;
}

template<class SignTag, unsigned byteCount, class Traits>
IntOf<SignTag, byteCount, Traits>&
    IntOf<SignTag, byteCount, Traits>::multiply(const IntOf& y, const Dontcheck&)
{
    _value *= y;
    return *this;
}

template<class SignTag, unsigned byteCount, class Traits>
IntDivRes< typename IntOf<SignTag, byteCount, Traits>::This >
    IntOf<SignTag, byteCount, Traits>::operator/=(const IntOf& y)
{
    return divide(y);
}

template<class SignTag, unsigned byteCount, class Traits>
IntDivRes< typename IntOf<SignTag, byteCount, Traits>::This >
    IntOf<SignTag, byteCount, Traits>::divide(const IntOf& y)
{
    Raw old =_value;
    _value /= y._value;
    return IntDivRes<This>(
        *this,
        This(old % y._value)
    );
    // TODO: implement divide according to selected arithmetic
}

template<class SignTag, unsigned byteCount, class Traits>
IntDivRes< typename IntOf<SignTag, byteCount, Traits>::This >
    IntOf<SignTag, byteCount, Traits>::divide(const IntOf& y, const Dontcheck&)
{
    Raw old =_value;
    _value /= y._value;
    return IntDivRes<This>(
        *this,
        This(old % y._value)
    );
    // TODO: check optimality
}
