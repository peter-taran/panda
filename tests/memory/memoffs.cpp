
#include "../tests.h"

namespace Tests
{

BOOST_AUTO_TEST_CASE(Memory_Memoffs)
{
    checkUninitialized<Memoffs>();

    // initializing & comparison with raw integer
    Memoffs m1, m2;
    BOOST_CHECK(m1 == m2);
    BOOST_CHECK(m1 == Memoffs(0));
    BOOST_CHECK(!(m1 != m2));
    /*BOOST_CHECK(m1.asInt() == 0);*/
    BOOST_CHECK(m1.raw() == 0);
    BOOST_CHECK(m1 == 0);

    Memoffs m3 = 10, m4 = -30;
    /*BOOST_CHECK(m3.asInt() == 10);*/
    BOOST_CHECK(m3.raw() == 10);
    /*BOOST_CHECK(m3.asUnsigned() == 10);
    BOOST_CHECK(m4.asInt() == -30);
    typedef IntOf<Unsigned, sizeof(void*)>::Raw MUint;
    BOOST_CHECK(m4.asUnsigned() == MUint(-30) );*/
    BOOST_CHECK(m3 == 10);
    BOOST_CHECK(m4 == -30);

    // offsets comparison
    BOOST_CHECK(m3 != 0);
    BOOST_CHECK(m3 > 0);
    BOOST_CHECK(m4 < 0);

    BOOST_CHECK(m4 < m3);
    BOOST_CHECK(m4 <= m3);
    BOOST_CHECK(m3 > m4);
    BOOST_CHECK(m3 >= m4);
    BOOST_CHECK(m3 != m4);

    Memoffs m5 = m3;
    BOOST_CHECK(m5 == m3);
    BOOST_CHECK(m5 <= m3);
    BOOST_CHECK(m5 >= m3);
    BOOST_CHECK(!(m5 < m3));
    BOOST_CHECK(!(m5 > m3));

    // increment
    BOOST_CHECK(++m3 == 11);
    BOOST_CHECK(m3 == 11);
    BOOST_CHECK(m3++ == 11);
    BOOST_CHECK(m3 == 12);

    // decrement
    BOOST_CHECK(--m5 == 9);
    BOOST_CHECK(m5 == 9);
    BOOST_CHECK(m5-- == 9);
    BOOST_CHECK(m5 == 8);

    // unary minus
    BOOST_CHECK(-m5 == -8);

    // add&subtract offsets
    Memoffs m6 = -50;
    BOOST_CHECK(-40 == (m6 += 10));
    BOOST_CHECK(-50 == (m6 -= 10));
    Memoffs m7 = m6 + m6;
    BOOST_CHECK(m7 == -100);
    Memoffs m8 = m6 - m6;
    BOOST_CHECK(m8 == 0);

    // offset + address -> address
    const char x[6] = {};
    Memaddr x3 = x+3;
    Memaddr x1 = Memoffs(-2) + x3;
    BOOST_CHECK(x1 == x + 1);
    
    // shouldn't compile
    // Memaddr x5 = Memoffs(-2) - x3;
}

}