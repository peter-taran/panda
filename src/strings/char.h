
#pragma once



// Abstract Unicode character
class Char: public
    boost::totally_ordered<Char
    >
{
public:
    // This type
    typedef Char This;

    // initialization
    inline Char(); // zero character
    inline Char(const Uninitialized&);
    inline Char(const UnicodePoint& unicodePoint);
    inline Char(wchar_t charCode);
    inline Char(char charCode);

    // copy-n-assignment
    inline Char(const Char& from);
    inline Char& operator=(const Char& from);

    // unicode point, encoding this character
    inline UnicodePoint unicodePoint() const;

    // comparison
    inline Bool operator==(const Char& y) const;
    inline Bool operator<(const Char& y) const;
    
    // TODO: unicode properties of character

private:
    UnicodePoint _codePoint;
};


// Char contains one character in selected encoding
template<class Encoding_ = PANDACFG_DEFAULT_ENCODING>
class CharEnc: public
    boost::totally_ordered<CharEnc<Encoding_>
    >
{
public:
    // Type parameters
    typedef Encoding_ Encoding;

    // This type
    typedef CharEnc This;

    // initialization
    inline CharEnc(); // zero character
    inline CharEnc(const Uninitialized&);
    inline CharEnc(const UnicodePoint& unicodePoint);
    inline CharEnc(wchar_t charCode);
    inline CharEnc(char charCode);

    // copy-n-assignment
    inline CharEnc(const CharEnc& from);
    inline CharEnc& operator=(const CharEnc& from);
    // TODO: copy with reencoding

    // unicode entry, encoding this character
    inline UnicodePoint unicodePoint() const;

    // can be silently transformed to abstract character
    Char asChar() const;
    operator Char() const;

    // comparison
    inline Bool operator==(const CharEnc& y) const;
    inline Bool operator<(const CharEnc& y) const;
    // TODO: compare with chars encoded differently

private:
    Membuff<Encoding::charMemSizeMax> _data;
};
