
#pragma once



namespace Impl
{
    extern void NullStr_init(Str::Implementation& impl);
    extern void AcsiizWrappedStr_init(Str::Implementation& impl, const char* asciiCharsZeroTerm);
}



Str::Str(const Null&)
{
    Impl::NullStr_init(_impl);
}

Str::Str(const char* asciiCharsZeroTerm)
{
    Impl::AcsiizWrappedStr_init(_impl, asciiCharsZeroTerm);
}

Str::Str(const Str& from):
    _impl(from._impl)
{}

Str& Str::operator=(const Str& from)
{
    _impl = from._impl;
    return *this;
}

Str::~Str()
{}

Memoffs Str::length() const
{
    Memoffs result = _impl->length();
    return result;
}

Char Str::at(const Memoffs& index) const
{
    Char result = _impl->charAt(index);
    return result;
}

Char Str::operator[](const Memoffs& index) const
{
    Char result = _impl->charAt(index);
    return result;
}

Bool Str::operator==(const Str& y) const
{
    // TODO: optimization needed
    Memoffs l = length();
    if( l != y.length() )
        return false;
    for(Memoffs i = 0; i < l; ++i)
        if( at(i) != y.at(i) )
            return false;
    return true;
}

Bool Str::wrapper() const
{
    return _impl->wrapper();
}

void Str::swap(Str& y)
{
    (std::swap)(_impl, y._impl);
}

Str::Str(Implementation*& implPointer)
{
    implPointer = &_impl;
}
