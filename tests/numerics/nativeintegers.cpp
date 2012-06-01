
#include "../tests.h"

namespace Tests
{

template<class T, class TC>
void testIntOf_cmp(const TC tc, const TC less, const TC more)
{
    const T t0;
    const T t1 = tc;

    BOOST_CHECK(t0 == TC());
    BOOST_CHECK(t1 == tc);
    BOOST_CHECK(t0 != tc);
    BOOST_CHECK(t1 != TC());

    BOOST_CHECK(TC() == t0);
    BOOST_CHECK(tc == t1);
    BOOST_CHECK(tc != t0);
    BOOST_CHECK(TC() != t1);

    BOOST_CHECK(t1 < more); BOOST_CHECK(t1 <= more);
    BOOST_CHECK(more > t1); BOOST_CHECK(more >= t1);
    BOOST_CHECK(t1 > less); BOOST_CHECK(t1 >= less);
    BOOST_CHECK(less < t1); BOOST_CHECK(less <= t1);

    BOOST_CHECK(t1 <= t1);   BOOST_CHECK(t1 >= t1);
    BOOST_CHECK(!(t1 < t1)); BOOST_CHECK(!(t1 > t1));

    BOOST_CHECK(t1 <= tc);   BOOST_CHECK(t1 >= tc);
    BOOST_CHECK(!(t1 < tc)); BOOST_CHECK(!(t1 > tc));
}

template<class T>
void testIntOf_ari()
{
    const T tmin = T::smallest();
    const T tmax = T::largest();
    
    T t1 = tmin;
    t1 += 10;
    BOOST_CHECK(tmin+10 == t1);
    BOOST_CHECK(tmin < t1);
    t1 -= 10;
    BOOST_CHECK(tmin == t1);

    T t2 = tmax;
    t2 -= 10;
    BOOST_CHECK(tmax-10 == t2);
    BOOST_CHECK(tmax > t2);
    t2 += 10;
    BOOST_CHECK(tmax == t2);

    T t3 = tmax - 5;
    BOOST_CHECK(t3 + 5 == tmax);
    BOOST_CHECK(t3 == tmax - 5);
}

template<class SignTag, unsigned byteCount>
void testIntOf_boundsXY(
    const IntOf<SignTag, byteCount>& x,
    const IntOf<SignTag, byteCount>& y)
{
    typedef IntOf<SignTag, byteCount> T;

    typedef IntOf<SignTag, sizeof(int)>::Raw Reference;
    Reference xr = x.raw();
    Reference yr = y.raw();

    // plus
    {
        Reference plusRef = xr + yr;
        T::Raw plusRaw = x.raw() + y.raw();
        bool plusOkRef = (plusRef == plusRaw);
        bool plusOk = false;
        T plus = uninitialized;
        try {
            plus = x + y;
            plusOk = true;
        }
        catch(...)
        {}
        if( plusOk != plusOkRef )
        {
            char msg[256];
            #pragma warning(disable: 4996)
            const char* msgFmt = T::signedType()
                ? "%s[%u] %d + %d: %s"
                : "%s[%u] %u + %u: %s";
            sprintf(msg, msgFmt,
                T::signedType() ? "Signed" : "Unsigned",
                byteCount,
                xr, yr,
                plusOk ? "undetected bounds violation" :
                         "wrong detected bounds violation"
            );
            BOOST_ERROR(msg);
        }
        else if( plusOk )
            BOOST_CHECK_EQUAL(plusRef, plus.raw());
    }

    // minus
    {
        Reference minusRef = xr - yr;
        T::Raw minusRaw = x.raw() - y.raw();
        bool minusOkRef = (minusRef == minusRaw);
        bool minusOk = false;
        T minus = uninitialized;
        try {
            minus = x - y;
            minusOk = true;
        }
        catch(...)
        {}
        if( minusOk != minusOkRef )
        {
            char msg[256];
            #pragma warning(disable: 4996)
            const char* msgFmt = T::signedType()
                ? "%s[%u] %d - %d: %s"
                : "%s[%u] %u - %u: %s";
            sprintf(msg, msgFmt,
                T::signedType() ? "Signed" : "Unsigned",
                byteCount,
                xr, yr,
                minusOk ? "undetected bounds violation" :
                          "wrong detected bounds violation"
            );
            BOOST_ERROR(msg);
        }
        else if( minusOk )
            BOOST_CHECK_EQUAL(minusRef, minus.raw());
    }
    // multiply
    {
        Reference mulRef = xr * yr;
        T::Raw mulRaw = x.raw() * y.raw();
        bool mulOkRef = (mulRef == mulRaw);
        bool mulOk = false;
        T mul = uninitialized;
        try {
            mul = x * y;
            mulOk = true;
        }
        catch(...)
        {}
        if( mulOk != mulOkRef )
        {
            char msg[256];
            #pragma warning(disable: 4996)
            const char* msgFmt = T::signedType()
                ? "%s[%u] %d * %d: %s"
                : "%s[%u] %u * %u: %s";
            sprintf(msg, msgFmt,
                T::signedType() ? "Signed" : "Unsigned",
                byteCount,
                xr, yr,
                mulOk ? "undetected bounds violation" :
                        "wrong detected bounds violation"
            );
            BOOST_ERROR(msg);
        }
        else if( mulOk )
            BOOST_CHECK_EQUAL(mulRef, mul.raw());
    }
}

template<class SignTag, unsigned byteCount>
void testIntOf_bounds()
{
    typedef IntOf<SignTag, byteCount, PANDA_INT_ARITHMETIC_BOUNDED> T;

    ensure_static(sizeof(T) < sizeof(int));

    T x = T::smallest();
    do
    {
        T y = T::smallest();
        do
        {
            testIntOf_boundsXY(x, y);
            ++y;
        }
        while(y < T::largest());
        ++x;
    }
    while(x < T::largest());
}

template<class SignTag, unsigned byteCount>
void testIntOf()
{
    typedef IntOf<SignTag, byteCount> T;

    BOOST_CHECK_EQUAL(sizeof(T), byteCount);
    
    // initialization
    checkUninitialized<T>();
    T t1;
    T t2 = 0;
    T t3(0);
    T t4 = 123;
    T t5(123);
    BOOST_CHECK(t1.raw() == 0);
    BOOST_CHECK(t2.raw() == 0);
    BOOST_CHECK(t3.raw() == 0);
    BOOST_CHECK(t4.raw() == 123);
    BOOST_CHECK(t5.raw() == 123);

    // assignment
    t1 = t2 = t4;
    BOOST_CHECK(t1.raw() == t4.raw());
    BOOST_CHECK(t2.raw() == t4.raw());
    t5 = 100;
    BOOST_CHECK(t5.raw() == 100);

    const T::Raw r1 = 5;
    T t8 = r1;
    T t9(r1);
    BOOST_CHECK(t8.raw() == r1);
    BOOST_CHECK(t9.raw() == r1);

    // comparison
    testIntOf_cmp<T, T>(T(45), T(44), T(46));
    testIntOf_cmp<T, T::Raw>(45, 44, 46);

    // increment/decrement
    T t10 = t9;
    --++t10;
    BOOST_CHECK(t9 == t10);
    ++--t10;
    BOOST_CHECK(t9 == t10);
    BOOST_CHECK(t10++ == t9);
    --t10;
    BOOST_CHECK(t10-- == t9);

    // short plus/minus
    T t11 = 100;
    BOOST_CHECK(t11.subtract(40) == 60);
    BOOST_CHECK(t11.add(40) == 100);

    // detailed plus/minus
    typedef IntOf<SignTag, byteCount, PANDA_INT_ARITHMETIC_BOUNDED> TBnd;
    typedef IntOf<SignTag, byteCount, PANDA_INT_ARITHMETIC_CYCLIC> TCyc;
    testIntOf_ari<TBnd>(); // tests w/o bounds violaing
    testIntOf_ari<TCyc>();

    // min-max
    T count = T::largest();
    count.subtract(T::smallest(),  dontcheck);
    count.add(1, dontcheck);
    BOOST_CHECK(count == 0);

    // short multiply
    const T m0;
    const T m1 = 1;
    const T m5 = 5;
    BOOST_CHECK(m0 * m5 == 0);
    BOOST_CHECK(m0 * m1 == 0);
    BOOST_CHECK(m0 * m0 == m0);
    BOOST_CHECK(m1 * m5 == 5);
    BOOST_CHECK(m5 * m5 == 25);

    // TODO: detailed multiply

    // TODO: divide (now IntOf has divide interface with stubs)
    T d1 = 100;
    BOOST_CHECK(d1 / 3 == 33);
    BOOST_CHECK((d1 /= 33).rem() == 1);
    //BOOST_CHECK((d1 / 3).rem() == 1);
}

BOOST_AUTO_TEST_CASE(Numerics_Nativeintegers)
{
    testIntOf<Signed, 1>();
    testIntOf<Unsigned, 1>();

    testIntOf<Signed, 2>();
    testIntOf<Unsigned, 2>();

    testIntOf<Signed, 4>();
    testIntOf<Unsigned, 4>();

    testIntOf<Signed, 8>();
    testIntOf<Unsigned, 8>();

    typedef IntOf<Signed,   1> S1;
    typedef IntOf<Unsigned, 1> U1;
    typedef IntOf<Signed,   4> S4;
    typedef IntOf<Unsigned, 4> U4;
    BOOST_CHECK(S1::smallest() == -128);
    BOOST_CHECK(S1::largest()  ==  127);
    BOOST_CHECK(U1::smallest() ==  0);
    BOOST_CHECK(U1::largest()  ==  255);
    
    BOOST_CHECK(S4::smallest() == -2147483647 - 1);
    BOOST_CHECK(S4::largest()  ==  2147483647);
    BOOST_CHECK(U4::smallest() ==  0);
    BOOST_CHECK(U4::largest()  ==  4294967295);

    // tests for bound violations
    //testIntOf_bounds<Unsigned, 1>();
    //testIntOf_bounds<Signed, 1>();

    //PANDA_DECLARE_INTOF(U8, Unsigned, 1);
    //testIntOf<U8>();
}

}