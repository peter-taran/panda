
#pragma once



// Element of Unicode, unsigned integer, designating a single character
typedef IntOf<Unsigned, 4, PANDA_INT_ARITHMETIC_CYCLIC> UnicodePoint;
// TODO: specialized int-type for this; range 0..0x10FFFF



#include "encodings_impl.h"



// class of abstract encoding
class Encoding
{
public:
    // This type
    typedef Encoding This;

    // initialization
    template<class EncodingClass>
    inline Encoding();

    // destruction
    inline ~Encoding();

    // copy-n-assignment
    inline Encoding(const Encoding& from);
    inline Encoding& operator=(const Encoding& from);

    // maximum memory, needed to encode one character
    inline Memoffs charMemSizeMax() const;

    // can encoding represent ANY unicode character?
    inline Bool anyCharacterCanBeEncoded() const;

private:
    typedef Membuff<sizeof(Impl::EncodingMethods)> MethodsStor;
    mutable MethodsStor _methods;
};


// TODO: class templates for new Encoding_*** classes


#include "encodings/ascii.h"
#include "encodings/utf.h"
