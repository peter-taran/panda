
#pragma once



struct Encoding_ASCII
{
    // maximum memory, needed to encode one character
    static const Memoffs::Raw charMemSizeMax = 1;

    // can encoding represent ANY unicode character?
    static const Bool anyCharacterCanBeEncoded = false;

    // decode unicode point from encoded character data
    static UnicodePoint decodeChar(const Membuff<charMemSizeMax>& charData)
    {
        return charData.cobjAt<Byte>(0, dontcheck);
    }

    // encode unicode point to character data
    static Membuff<charMemSizeMax> encodeChar(const UnicodePoint& unicodePoint)
    {
        ensure(unicodePoint >= 0 && unicodePoint < 128);

        Membuff<charMemSizeMax> result = uninitialized;
        result.objAt<Byte>(0, dontcheck) = static_cast<Byte>(unicodePoint.raw());
        return result;
    }
};

