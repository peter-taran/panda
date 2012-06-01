
#include "../tests.h"

namespace Tests
{

static Membuff<64> _fixedMem;

struct FixedMemPage: public Mem::Methods
{
    FixedMemPage() {
        _fixedMem.objAt<Uint8>() = 100;
    }
    ~FixedMemPage() {
        _fixedMem.objAt<Uint8>() = 200;
    }
    virtual Bool wrapper() {
        return false;
    }
    virtual void clone(Mem::Implementation& cloneTo) {
        throw "static memory cannot be cloned";
    }
    virtual Memoffs size() {
        return _fixedMem.size;
    }
    virtual Memarea area() {
        return _fixedMem;
    }
};

void memCustomImpl()
{
    {
        Mem::Implementation* mi;
        Mem m(mi);
        mi->_stor.construct<FixedMemPage>();

        BOOST_CHECK(m.objAt<Uint8>() == 100); // check constructor called

        BOOST_CHECK_THROW(Mem m1 = m, char*); // cannot be copied
        BOOST_CHECK(m.size() == _fixedMem.size);
        _fixedMem.objAt<Int32>(5) = -1234567890;
        BOOST_CHECK(m.objAt<Int32>(5) == -1234567890);
    }
    BOOST_CHECK(_fixedMem.objAt<Uint8>() == 200); // check destructor called
}

BOOST_AUTO_TEST_CASE(Memory_Mem)
{
    Mem m0(0);
    BOOST_CHECK(m0 == Mem(0));
    BOOST_CHECK(!(m0 != Mem(0)));
    BOOST_CHECK(m0.size() == 0);
    BOOST_CHECK(m0.empty());
    BOOST_CHECK(m0.area().empty());
    
    Mem m15(15);
    BOOST_CHECK(m15.size() == 15);
    BOOST_CHECK(!m15.empty());
    BOOST_CHECK(m15.area().size() == 15);
    BOOST_CHECK(!m15.wrapper());

    Mem m15u(15, uninitialized);
    BOOST_CHECK(m15u != m15);

    Membuff<4> buff;
    Mem mb = Mem(buff);
    BOOST_CHECK(mb.size() == 4);
    BOOST_CHECK(!mb.empty());
    BOOST_CHECK(mb.area() == buff.area());
    BOOST_CHECK(mb.wrapper());
    mb.objAt<Int32>() = -12345678;
    BOOST_CHECK(buff.objAt<Int32>() == -12345678);

    Mem mbCpy = mb;
    BOOST_CHECK(mb.wrapper()); // TODO: more checks

    mb.unwrap();
    BOOST_CHECK(!mb.wrapper());
    BOOST_CHECK(mb.size() == 4);
    BOOST_CHECK(mb.area() != buff.area());
    BOOST_CHECK(buff.objAt<Int32>() == -12345678);
    mb.objAt<Int32>() = -87654321;
    BOOST_CHECK(buff.objAt<Int32>() == -12345678);

    memCustomImpl();
}

}