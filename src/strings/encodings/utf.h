
#pragma once



// UTF32 encoding
// character represented with one 32-bit word
struct Encoding_UTF32
{
    // maximum memory, needed to encode one character
    static const Memoffs::Raw charMemSizeMax = 4;

    // can encoding represent ANY unicode character?
    static const Bool anyCharacterCanBeEncoded = true;

    // decode unicode point from encoded character data
    static UnicodePoint decodeChar(const Membuff<charMemSizeMax>& charData)
    {
        UnicodePoint result = charData.cobjAt<Uint32>(0, dontcheck);
        return result;
    }

    // encode unicode point to character data
    static Membuff<charMemSizeMax> encodeChar(const UnicodePoint& unicodePoint)
    {
        Membuff<charMemSizeMax> result = uninitialized;
        result.objAt<Uint32>(0, dontcheck) = unicodePoint.raw();
        return result;
    }
};


// UTF16 encoding
// character represented with one or two 16-bit words
struct Encoding_UTF16
{
    // maximum memory, needed to encode one character
    static const Memoffs::Raw charMemSizeMax = 4;

    // can encoding represent ANY unicode character?
    static const Bool anyCharacterCanBeEncoded = true;

    // decode unicode point from encoded character data
    static UnicodePoint decodeChar(const Membuff<charMemSizeMax>& charData)
    {
        UnicodePoint result = uninitialized;
        Uint16 first = charData.cobjAt<Uint16>(0, dontcheck);
        if( first < 0xD800 || first >= 0xC000 )
        {
            result = first;
        }
        else
        {
            Uint16 second = charData.cobjAt<Uint16>(2, dontcheck);
            // TODO: check the first to be inside 0xD800..0xDBFF
            // TODO: check the second to be inside 0xDC00..0xDFFF
            result = Uint32(0x10000) + (Uint32(first - 0xD800) << 10) + Uint32(second - 0xDC00);
        }
        return result;
    }

    // encode unicode point to character data
    static Membuff<charMemSizeMax> encodeChar(const UnicodePoint& unicodePoint)
    {
        // unicodePoint must be inside BMP
        Membuff<charMemSizeMax> result = uninitialized;
        if(unicodePoint < 0xD800 || unicodePoint >= 0xC000)
        {
            result.objAt<Uint16>(0, dontcheck) = static_cast<Uint16>(unicodePoint.raw());
        }
        else
        {
            Uint32 temp = (unicodePoint - 0x10000).raw();
            result.objAt<Uint16>(0, dontcheck) = 0xD800 + ((temp >> 10) & 0x3FF);
            result.objAt<Uint16>(2, dontcheck) = 0xDC00 + (temp & 0x3FF);
        }
        return result;
    }
};


// UTF16 encoding, limited by BMP (basic multilingual plane) characters
// any character encoded with one 16-bit word
struct Encoding_UTF16BMP
{
    // maximum memory, needed to encode one character
    static const Memoffs::Raw charMemSizeMax = 2;

    // can encoding represent ANY unicode character?
    static const Bool anyCharacterCanBeEncoded = false;

    // decode unicode point from encoded character data
    static UnicodePoint decodeChar(const Membuff<charMemSizeMax>& charData)
    {
        return charData.cobjAt<Uint16>(0, dontcheck);
    }

    // encode unicode point to character data
    static Membuff<charMemSizeMax> encodeChar(const UnicodePoint& unicodePoint)
    {
        // unicodePoint must be inside BMP
        ensure(unicodePoint < 0xD800 || unicodePoint >= 0xC000);

        Membuff<charMemSizeMax> result = uninitialized;
        result.objAt<Uint16>(0, dontcheck) = static_cast<Uint16>(unicodePoint.raw());
        return result;
    }
};


/*struct Encoding_UTF16BE
{
};

struct Encoding_UTF16LE
{
};

struct Encoding_UTF32BE
{
};

struct Encoding_UTF32LE
{
};

*/


struct Encoding_UTF8
{
    // maximum memory, needed to encode one character
    static const Memoffs::Raw charMemSizeMax = 4;

    // can encoding represent ANY unicode character?
    static const Bool anyCharacterCanBeEncoded = true;

    // decode unicode point from encoded character data
    static UnicodePoint decodeChar(const Membuff<charMemSizeMax>& charData);

    // encode unicode point to character data
    static Membuff<charMemSizeMax> encodeChar(const UnicodePoint& unicodePoint);
};

// TODO: Encoding_UTF8Java
// Java-modified encoding

// TODO: интересное кодирование уникода со сжатием:
// http://www.unicode.org/reports/tr6/  http://en.wikipedia.org/wiki/Standard_Compression_Scheme_for_Unicode
// или это:
// http://www.unicode.org/notes/tn6/    http://en.wikipedia.org/wiki/Binary_Ordered_Compression_for_Unicode
// сравнение: http://www.unicode.org/notes/tn14/

// опенсорсная библиотека для поддержки уникода: http://en.wikipedia.org/wiki/International_Components_for_Unicode