
#include "../tests.h"

namespace Tests
{

BOOST_AUTO_TEST_CASE(Memory_Memaddr)
{
    // initialization and assignment
    checkUninitialized<Memaddr>();

    Memaddr a1;
    BOOST_CHECK(a1.raw() == 0);
    a1 = 0;
    BOOST_CHECK(a1.raw() == 0);

    const Int i1 = 12345;
    Int i2 = -54321;

    Memaddr a3a(&i1);
    BOOST_CHECK(a3a.raw() == &i1);
    Memaddr a3b = &i1;
    BOOST_CHECK(a3b.raw() == &i1);
    Memaddr a3c = &i2;
    BOOST_CHECK(a3c.raw() == &i2);
    
    a3a = a3b = &i2;
    BOOST_CHECK(a3a.raw() == &i2);
    BOOST_CHECK(a3b.raw() == &i2);

    a3a = &i1;

    Memaddr a2a;
    a2a = a1;
    BOOST_CHECK(a2a.raw() == 0);
 
    // getting raw value
    Memaddr a4 = &i2;
    void* ptr1 = a4.raw();
    const void* ptr2 = a3c.raw();
    BOOST_CHECK(ptr1 == &i2);
    BOOST_CHECK(ptr2 == &i2);

    BOOST_CHECK(0 == Memaddr().raw());

    // equality of Memaddr's and Memaddr's against void*
    Memaddr a5;
    Memaddr a6;
    BOOST_CHECK(a5 == a6);
    
    a5 = &i1;
    const void* ptr3 = &i1;
    BOOST_CHECK(a5 == ptr3);
    BOOST_CHECK(ptr3 == a5);
    BOOST_CHECK(!(a5 != ptr3));
    BOOST_CHECK(a5 != &i2);
    BOOST_CHECK(&i2 != a5);
    BOOST_CHECK(!(a5 == &i2));
    BOOST_CHECK(0 == Memaddr());
    BOOST_CHECK(Memaddr() == 0);

    // ordering of Memaddr's and Memaddr's against void*
    const char* strs[] = {"first", "second", "third"};
    BOOST_CHECK(strs+0 < strs+1 && strs+1 < strs+2);
    
    const Memaddr a7[] = {strs+0, strs+1, strs+2};
    BOOST_CHECK(a7[0] < a7[1] && a7[1] < a7[2]);
    BOOST_CHECK(a7[2] > a7[0]);
    BOOST_CHECK(a7[1] >= a7[1]);
    BOOST_CHECK(a7[2] >= a7[1]);
    BOOST_CHECK(a7[1] <= a7[1]);
    BOOST_CHECK(a7[1] <= a7[2]);

    BOOST_CHECK(strs+0 < a7[1] && strs+1 < a7[2]);
    BOOST_CHECK(strs+2 > a7[0]);
    BOOST_CHECK(strs+1 >= a7[1]);
    BOOST_CHECK(strs+2 >= a7[1]);
    BOOST_CHECK(strs+1 <= a7[1]);
    BOOST_CHECK(strs+1 <= a7[2]);

    // treat address as pointer to object
    Uint i3 = 5;
    Memaddr a8 = &i3;
    BOOST_CHECK(a8.objAt<Uint>() == i3);
    BOOST_CHECK(Memaddr(&i3).objAt<const Int>() == i3);
    
    // shouldn't compile:
    //a8.as<Uint*&>();
    //a8.as<Bool>();

    // bool-like checks (if we implement them)
    /*Int i4 = 0;
    Memaddr a9  = 0;
    Memaddr a10 = &i4;
    if( a9 )
        BOOST_ERROR("a9 is null");
    if( !a10 )
        BOOST_ERROR("a10 is not null");*/

    // increment/decrement
    Uint8 x[2] = {10, 20};
    Memaddr a11 = &x;
    BOOST_CHECK(a11 == x);
    BOOST_CHECK(a11++ == x);
    BOOST_CHECK(a11 == x+1);
    BOOST_CHECK(--a11 == x);

    // arithmetic with offsets and raw integers (silently converted to Memoffs'es)
    Memaddr a12 = &x;
    BOOST_CHECK(a12 + 1 == x+1);
    a12 += 1;
    BOOST_CHECK(a12 - 1 == x+0);
    BOOST_CHECK(a12 + Memoffs(-1) == x+0);
    a12 -= Memoffs(1);
    BOOST_CHECK(a12 - Memoffs(-1) == x+1);
}

}