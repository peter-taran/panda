
#include "../tests.h"

namespace Tests
{

BOOST_AUTO_TEST_CASE(Memory_Memarea)
{
    checkUninitialized<Memarea>();

    Memarea a0;
    BOOST_CHECK(a0.start() == 0);
    BOOST_CHECK(a0.size() == 0);
    BOOST_CHECK(a0.end() == 0);

    char x[5] = {0, 1, 2, 3, 4};
    Memarea a1(&x, x+5);
    BOOST_CHECK(a1.start() == &x);
    BOOST_CHECK(a1.size() == 5);
    BOOST_CHECK(a1.end() == x+5);

    Memarea a2(&x, 4);
    BOOST_CHECK(a2.start() == &x);
    BOOST_CHECK(a2.size() == 4);
    BOOST_CHECK(a2.end() == x+4);

    Memarea a3 = a2;
    BOOST_CHECK(a3 == a2);
    BOOST_CHECK(!(a3 != a2));

    Memarea a4 = Memarea(&x, Memoffs(0));
    a3 = a0;
    BOOST_CHECK(a4 == a3);
    BOOST_CHECK(!(a4 != a3));

    Memarea a5(&x, 5);
    BOOST_CHECK(a5.tail(0) == a5);
    BOOST_CHECK(a5.tail(2) == Memarea(x+2, x+5));
    BOOST_CHECK(a5.tail(-5) == a5);
    BOOST_CHECK(a5.tail(-4) == Memarea(x+1, x+5));

    BOOST_CHECK(a5.head(0) == a0);
    BOOST_CHECK(a5.head(2) == Memarea(x, x+2));
    BOOST_CHECK(a5.head(-5) == a0);
    BOOST_CHECK(a5.head(-4) == Memarea(x, x+1));

    BOOST_CHECK(a5.split(0) == std::make_pair(Memarea(), a5));
    BOOST_CHECK(a5.split(0) == a5.split(-5));
    BOOST_CHECK(a5.split(2)  == std::make_pair(Memarea(x+0, x+2), Memarea(x+2, x+5)));
    BOOST_CHECK(a5.split(-2) == std::make_pair(Memarea(x+0, x+3), Memarea(x+3, x+5)));

    BOOST_CHECK(a5.objAt<Uint8>(1) == 1);
    BOOST_CHECK(a5.objAt<Uint8>(4) == 4);
    BOOST_CHECK(a5.objAt<Uint16>(2) == 0x0302);
    //BOOST_CHECK_THROW(a5.objAt<Uint8>(5) == 4, ?);

    {
        Uint32 y = 0x04030201;
        Memarea a6(&y, sizeof(y));
        BOOST_CHECK(a6.memEqual(a6));
        BOOST_CHECK(!a6.memEqual(a5));
        BOOST_CHECK(a6.memEqual(a5.tail(-4)));
    }

    {
        int itersHead = 0;
        for(Memarea a6(&x, 5); !a6.empty(); ++itersHead)
        {
            Memarea c = a6.extractHead(1);
            BOOST_CHECK(c.size() == 1);
            BOOST_CHECK_EQUAL(c.objAt<Uint8>(), itersHead);
        }
        BOOST_CHECK_EQUAL(itersHead, 5);
    }

    {
        int itersTail = 0;
        for(Memarea a6(&x, 5); !a6.empty(); ++itersTail)
        {
            Memarea c = a6.extractTail(-1);
            BOOST_CHECK(c.size() == 1);
            BOOST_CHECK_EQUAL(c.objAt<Uint8>(), 4-itersTail);
        }
        BOOST_CHECK_EQUAL(itersTail, 5);
    }

    Memarea a6(&x, 5);
    BOOST_CHECK(a6.addrAt(0) == x+0);
    BOOST_CHECK(a6.addrAt(4) == x+4);
    BOOST_CHECK_EQUAL(a6.objAt<char>(2), 2);
    
    char y[3] = {0, 0, 0};
    Memarea a7(&y, 3);
    //BOOST_CHECK_THROW(a6.memCopyTo(a7), ?);
    a6.head(3).memCopyTo(a7);
    BOOST_CHECK_EQUAL(y[0], 0);
    BOOST_CHECK_EQUAL(y[1], 1);
    BOOST_CHECK_EQUAL(y[2], 2);
    char z[3] = {};
    a7.memCopyTo(Memaddr(&z));
    BOOST_CHECK_EQUAL(z[0], 0);
    BOOST_CHECK_EQUAL(z[1], 1);
    BOOST_CHECK_EQUAL(z[2], 2);

    Membuff<2> i16stor;
    Int16* i16 = &i16stor.area().construct<Int16>();
    BOOST_CHECK(*i16 == 0);
    i16 = &i16stor.area().construct<Int16>(76);
    BOOST_CHECK(*i16 == 76);
    i16stor.area().destruct<Int16>();
}

}