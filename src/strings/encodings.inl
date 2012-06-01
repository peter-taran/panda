
#pragma once



/*namespace Impl
{
    template<class Encoding_>
    struct EncodingMethodsSpec: EncodingMethods
    {
        typedef Encoding_ Encoding;

        virtual Memoffs charMemSizeMax()
        {
            return Encoding::charMemSizeMax;
        }

        virtual Bool anyCharacterCanBeEncoded()
        {
            return Encoding::anyCharacterCanBeEncoded;
        }
    };
}



template<class EncodingClass>
Encoding::Encoding():
    _methods(uninitialized)
{
    _methods.memarea().construct< EncodingMethodsSpec<EncodingClass> >();
}

Encoding::~Encoding()
{
    _methods.memarea().destruct< EncodingMethods<EncodingClass> >();
}

Encoding::Encoding(const Encoding& from):
    _methods(uninitialized)
{
    _methods.memarea().construct<Impl::EncodingMethods>(
        from._methods.objAt<Impl::EncodingMethods>(0, dontcheck)
    );
}

Encoding& Encoding::operator=(const Encoding& from)
{
    // TODO
}

Memoffs Encoding::charMemSizeMax() const
{
    Memoffs result = _methods.objAt<Impl::EncodingMethods>(0, dontcheck).charMemSizeMax();
    return result
}

Bool Encoding::anyCharacterCanBeEncoded() const
{
    Bool result = _methods.objAt<Impl::EncodingMethods>(0, dontcheck).anyCharacterCanBeEncoded();
    return result;
}
*/