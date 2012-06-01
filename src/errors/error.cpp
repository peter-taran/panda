
#include "../../panda.h"



struct AssertionImpl
{
    static const Error::Methods _methods;

    Str _text;

    AssertionImpl(const Str& text):
        _text(text)
    {}

    static inline AssertionImpl& impl(Error::InternalStorage& storage)
    {
        return storage.objAt<AssertionImpl>(0);
    }

    static void destruct(Error::InternalStorage& storage)
    {
        impl(storage).~AssertionImpl();
    }

    static void clone(Error::InternalStorage& storage, Error::InternalStorage& copyTo)
    {
        new(&impl(copyTo)) AssertionImpl(impl(storage));
    }

    static void throwThis(const Error& error)
    {
        throw static_cast<const AssertionError&>(error);
    }

    static Str description(Error::InternalStorage& storage)
    {
        return impl(storage)._text;
    }
};

const Error::Methods AssertionImpl::_methods =
{
    &destruct,
    &clone,
    &throwThis,
    &description,
};

AssertionError::AssertionError(const Str& text)
{
    _methods = &AssertionImpl::_methods;
    _storage.construct<AssertionImpl>(text);
}
