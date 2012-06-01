
#include "../tests.h"

namespace Tests
{

template<Memoffs::Raw size>
void testMemFuncs_statLen()
{
    char x[size];
    char y[size];

    Impl::StaticMemArea<size>::zero(&x);
    for(Memoffs::Raw i = 0; i < size; ++i)
        BOOST_CHECK_EQUAL(x[i], 0);
    
    BOOST_CHECK((Impl::StaticMemArea2<size, size>::equal(&x, &x)));

    Impl::StaticMemArea<size>::zero(&y);
    BOOST_CHECK((Impl::StaticMemArea2<size, size>::equal(&x, &y)));
    BOOST_CHECK(!(Impl::StaticMemArea2<size, size-1>::equal(&x, &y)));
    y[size-1] = 'x';
    BOOST_CHECK(!(Impl::StaticMemArea2<size, size>::equal(&x, &y)));
    BOOST_CHECK((Impl::StaticMemArea2<size-1, size-1>::equal(&x, &y)));

    Impl::StaticMemArea<size>::copy(&x, &y);
    if( size > 1 )
        BOOST_CHECK_EQUAL(x[0], 0);
    BOOST_CHECK_EQUAL(x[size-1], 'x');
}
    
void testMemFuncs()
{
    // TODO: use <0> when Array will be implemented and use Array<char, size> in testMemFuncs_statLen
     //testMemFuncs_statLen<0>();
     testMemFuncs_statLen<1>();
     testMemFuncs_statLen<2>();
     testMemFuncs_statLen<3>();
     testMemFuncs_statLen<4>();
     testMemFuncs_statLen<5>();
     testMemFuncs_statLen<6>();
     testMemFuncs_statLen<7>();
     testMemFuncs_statLen<8>();
     testMemFuncs_statLen<9>();
     testMemFuncs_statLen<10>();
     testMemFuncs_statLen<11>();
     testMemFuncs_statLen<12>();
     testMemFuncs_statLen<13>();
     testMemFuncs_statLen<14>();
     testMemFuncs_statLen<16>();
     testMemFuncs_statLen<17>();
     testMemFuncs_statLen<18>();
     testMemFuncs_statLen<19>();
     testMemFuncs_statLen<20>();

     // TODO: test of nonstatic functions
}

BOOST_AUTO_TEST_CASE(Memory_Byte)
{
    // TODO

    testMemFuncs();
}

}