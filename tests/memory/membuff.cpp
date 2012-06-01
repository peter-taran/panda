
#include "../tests.h"

namespace Tests
{

BOOST_AUTO_TEST_CASE(Memory_Membuff)
{
    checkUninitialized< Membuff<15> >();

    BOOST_CHECK_EQUAL(sizeof(Membuff<1>), 1);
    BOOST_CHECK_EQUAL(sizeof(Membuff<2>), 2);
    BOOST_CHECK_EQUAL(sizeof(Membuff<3>), 3);
    BOOST_CHECK_EQUAL(sizeof(Membuff<4>), 4);
    BOOST_CHECK_EQUAL(sizeof(Membuff<17>), 17);
    BOOST_CHECK_EQUAL(sizeof(Membuff<1234567>), 1234567);

    // TODO: empty Membuff
    // Membuff<0> m0;

    Membuff<4> m1;
    BOOST_CHECK_EQUAL(m1.objAt<Int32>(0), 0);

    Membuff<4> m1a = Membuff<4>::filled(5);
    BOOST_CHECK_EQUAL(m1a.objAt<Uint32>(0), 0x05050505);
    
    BOOST_CHECK_EQUAL(sizeof(Membuff<1>), 1);

    Membuff<4> m2 = m1;
    BOOST_CHECK(m2 == m1);
    BOOST_CHECK(!(m2 != m1));

    m2.addrAt(0).objAt<Int32>() = -890;
    BOOST_CHECK(m2 != m1);

    BOOST_CHECK(m2.area() == Memarea(&m2, sizeof(m2)));

    Membuff<2> i16stor;
    Int16* i16 = &i16stor.construct<Int16>();
    BOOST_CHECK(*i16 == 0);
    i16 = &i16stor.construct<Int16>(76);
    BOOST_CHECK(*i16 == 76);
    i16stor.destruct<Int16>();
}

}