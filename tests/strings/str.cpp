
#include "../tests.h"

namespace Tests
{

BOOST_AUTO_TEST_CASE(Strings_Str)
{
    Str s0 = null;

    BOOST_CHECK_THROW(s0.length(), const char*);
    BOOST_CHECK_THROW(s0[7], const char*);
    BOOST_CHECK_THROW(s0.at(0), const char*);
    BOOST_CHECK_THROW(s0 == Str(null), const char*);
    BOOST_CHECK_THROW((!(s0 != Str(null))), const char*);

    BOOST_CHECK_THROW(Str(0), const char*); // это перестанет компилироваться и не страшно!
    BOOST_CHECK_THROW(Str(""), const char*);

    Str s1 = "abcde";
    BOOST_CHECK(s1.length() == 5);
    BOOST_CHECK(s1[0] == 'a');
    BOOST_CHECK_THROW(s1[5], const char*);
    BOOST_CHECK(!s1.wrapper()); // 'cause short strings embeds to Str

    Str s2 = "Hello, dirty cruel world!";
    BOOST_CHECK(s2.length() == 25);
    BOOST_CHECK(s2[0] == 'H');
    BOOST_CHECK(s2[5] == ',');
    BOOST_CHECK_THROW(s2[25], const char*);
    BOOST_CHECK(s2.wrapper());
    
    Str s3 = s2;
    BOOST_CHECK(!s3.wrapper());
    BOOST_CHECK(s2 == s3);
    BOOST_CHECK(!(s2 != s3));

    // TODO: много, много проверок надо
}

}