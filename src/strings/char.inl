
#pragma once



namespace Impl
{
    template<Memoffs::Raw size>
    struct BuiltInEncoding
    {};

    template<>
    struct BuiltInEncoding<1>
    {
        typedef Encoding_ASCII Type;
    };

    template<>
    struct BuiltInEncoding<2>
    {
        typedef Encoding_UTF16BMP Type;
    };

    template<>
    struct BuiltInEncoding<4>
    {
        typedef Encoding_UTF32 Type;
    };
}



Char::Char()
{}

Char::Char(const Uninitialized&):
    _codePoint(uninitialized)
{}

Char::Char(const UnicodePoint& unicodePoint):
    _codePoint(unicodePoint)
{}

Char::Char(wchar_t charCode):
    _codePoint(Impl::BuiltInEncoding<sizeof(charCode)>::Type::decodeChar(
            Membuff<Impl::BuiltInEncoding<sizeof(charCode)>::Type::charMemSizeMax>(charCode)))
{}

Char::Char(char charCode):
    _codePoint(Impl::BuiltInEncoding<sizeof(charCode)>::Type::decodeChar(
            Membuff<Impl::BuiltInEncoding<sizeof(charCode)>::Type::charMemSizeMax>(charCode)))
{}

Char::Char(const Char& from):
    _codePoint(from._codePoint)
{}

Char& Char::operator=(const Char& from)
{
    _codePoint = from._codePoint;
    return *this;
}

UnicodePoint Char::unicodePoint() const
{
    return _codePoint;
}

Bool Char::operator==(const Char& y) const
{
    return _codePoint == y._codePoint;
}

Bool Char::operator<(const Char& y) const
{
    return _codePoint < y._codePoint;
}


    
template<class Encoding>
CharEnc<Encoding>::CharEnc()
{}

template<class Encoding>
CharEnc<Encoding>::CharEnc(const Uninitialized&):
    _data(uninitialized)
{}

template<class Encoding>
CharEnc<Encoding>::CharEnc(const UnicodePoint& unicodePoint):
    _data(Encoding::encodeChar(unicodePoint))
{}

template<class Encoding>
CharEnc<Encoding>::CharEnc(wchar_t charCode):
    _data(Encoding::encodeChar(
        Impl::BuiltInEncoding<sizeof(charCode)>::Type::decodeChar(
            Membuff<Impl::BuiltInEncoding<sizeof(charCode)>::Type::charMemSizeMax>(charCode))))
{}

template<class Encoding>
CharEnc<Encoding>::CharEnc(char charCode):
    _data(Encoding::encodeChar(
        Impl::BuiltInEncoding<sizeof(charCode)>::Type::decodeChar(
            Membuff<Impl::BuiltInEncoding<sizeof(charCode)>::Type::charMemSizeMax>(charCode))))
{}

template<class Encoding>
CharEnc<Encoding>::CharEnc(const CharEnc& from):
    _data(from._data)
{}

template<class Encoding>
CharEnc<Encoding>& CharEnc<Encoding>::operator=(const CharEnc& from)
{
    _data = from._data;
    return *this;
}

template<class Encoding>
UnicodePoint CharEnc<Encoding>::unicodePoint() const
{
    return Encoding::decodeChar(_data);
}

template<class Encoding>
Char CharEnc<Encoding>::asChar() const
{
    Char result(unicodePoint());
    return result;
}

template<class Encoding>
CharEnc<Encoding>::operator Char() const
{
    Char result(unicodePoint());
    return result;
}

template<class Encoding>
Bool CharEnc<Encoding>::operator==(const CharEnc& y) const
{
    return unicodePoint() == y.unicodePoint();
}

template<class Encoding>
Bool CharEnc<Encoding>::operator<(const CharEnc& y) const
{
    return unicodePoint() < y.unicodePoint();
}
