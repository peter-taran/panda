
#include "../tests.h"

namespace Tests
{

template<class C>
void testChar()
{
    checkUninitialized<C>();

    C c0;
    C c1 = c0;

    BOOST_CHECK(c0 == c1);
    BOOST_CHECK(!(c0 != c1));
    BOOST_CHECK(c0.unicodePoint() == 0);

    C c2 = 'a';
    BOOST_CHECK(c2 == 'a');

    C c3 = L'z';
    BOOST_CHECK(c3 == L'z');
    BOOST_CHECK(c3.unicodePoint() == 'z');
}

BOOST_AUTO_TEST_CASE(Strings_Char)
{
    testChar< Char >();
    testChar< CharEnc<PANDACFG_DEFAULT_ENCODING> >();

    // TODO: check for different unicode characters: inside and outside BMP
}

}