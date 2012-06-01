
// implementation of all UTF algorithms
#include "../../panda.h"



struct NullStr: Str::Methods
{
    virtual void clone(Str::Implementation& copyTo)
    {
        copyTo._stor.construct<NullStr>();
    }

    virtual Memoffs length()
    {
        // TODO: normal exception
        throw "String is null, length cannot be evaluated";
    }

    virtual Char charAt(const Memoffs& index)
    {
        // TODO: normal exception
        throw "String is null, no access to characters";
    }

    virtual Bool wrapper()
    {
        return false;
    }
};

namespace Impl
{
    void NullStr_init(Str::Implementation& impl)
    {
        impl._stor.construct<NullStr>();
    }
}

struct SharedStr: Str::Methods // TODO: only ACSII characters yet
{
    // shared data is:
    //    -4    32-bit unsigned, reference counter
    //     0    character data
    Memoffs _length;
    Memaddr _sharedData;

    SharedStr(const Memaddr& sharedData, const Memoffs& length):
        _sharedData(sharedData), _length(length)
    {
        ++(_sharedData-4).objAt<Uint32>();
    }

    SharedStr(const Memarea& asciizChars):
        _length(asciizChars.size()), _sharedData(new char[(_length + 4).raw()])
    {
        _sharedData.objAt<Uint32>() = 1;
        _sharedData += 4;
        memcpy(_sharedData.raw(), asciizChars.start().raw(), _length.raw());
    }

    virtual ~SharedStr()
    {
        Uint32& counter = (_sharedData-4).objAt<Uint32>();
        --counter;
        if( counter == 0 )
            delete[] (_sharedData-4).raw();
    }

    virtual void clone(Str::Implementation& copyTo)
    {
        copyTo._stor.construct<SharedStr>(_sharedData, _length);
    }

    virtual Memoffs length()
    {
        return _length;
    }

    virtual Char charAt(const Memoffs& index)
    {
        if( index < 0 || index >= _length )
            throw "Index out of string bounds"; // TODO: normal error
        
        return Encoding_ASCII::decodeChar( (_sharedData + index).objAt< Membuff<1> >() );
    }

    virtual Bool wrapper()
    {
        return false;
    }
};

struct AcsiizWrappedStr: Str::Methods
{
    Memarea _chars;

    AcsiizWrappedStr(const Memaddr& firstChar, const Memoffs& length):
        _chars(firstChar, length)
    {}

    virtual void clone(Str::Implementation& copyTo)
    {
        copyTo._stor.construct<SharedStr>(_chars);
    }

    virtual Memoffs length()
    {
        return _chars.size(); // size in bytes is equal to length
    }

    virtual Char charAt(const Memoffs& index)
    {
        if( index < 0 || index >= _chars.size() )
            throw "Index out of string bounds"; // TODO: normal error
        
        return Encoding_ASCII::decodeChar( _chars.objAt< Membuff<1> >(index) );
    }

    virtual Bool wrapper()
    {
        return true;
    }
};

struct ShortStr: Str::Methods // TODO: ACSII encoding now, more later
{
    static const Memoffs::Raw maxLength = Str::Implementation::storageSize - 1;
    Membuff<maxLength> _chars;
    Uint8 _length;

    ShortStr(const Memaddr& firstChar, const Uint8& length):
        _chars(uninitialized), _length(length)
    {
        memcpy(_chars.addrAt(0, dontcheck).raw(), firstChar.raw(), length);
    }

    virtual void clone(Str::Implementation& copyTo)
    {
        copyTo._stor.construct<ShortStr>(_chars.addrAt(0, dontcheck), _length);
    }

    virtual Memoffs length()
    {
        return _length;
    }

    virtual Char charAt(const Memoffs& index)
    {
        if( index < 0 || index >= _length )
            throw "Index out of string bounds"; // TODO: normal error
        return Encoding_ASCII::decodeChar(_chars.objAt< Membuff<1> >(index));
    }

    virtual Bool wrapper()
    {
        return false;
    }
};

namespace Impl
{
    void AcsiizWrappedStr_init(Str::Implementation& impl, const char* asciiCharsZeroTerm)
    {
        if( 0 == asciiCharsZeroTerm || 0 == asciiCharsZeroTerm[0] )
            throw "empty string cannot be used to initialize Str; use Str0 instead";

        //Memoffs length;
        Memoffs length;
        for(const char* p = asciiCharsZeroTerm; 0 != *p; ++p, ++length) {}

        if( length <= ShortStr::maxLength )
        {
            impl._stor.construct<ShortStr>(asciiCharsZeroTerm, length.raw()); // TODO: replace with appropriate method
        }
        else
        {
            impl._stor.construct<AcsiizWrappedStr>(asciiCharsZeroTerm, length);
        }
    }
}
