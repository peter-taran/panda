
#include "../../panda.h"



struct MemEmpty: Mem::Methods
{
    virtual ~MemEmpty()
    {
        // MemEmpty doesn't need of destruction
    }

    virtual void clone(Mem::Implementation& cloneTo)
    {
        cloneTo._stor.construct<MemEmpty>();
    }

    virtual Memoffs size()
    {
        return 0;
    }

    virtual Memarea area()
    {
        Memarea zero;
        return zero;
    }

    virtual Bool wrapper()
    {
        return false;
    }
};

struct MemDynBuff: Mem::Methods
{
    Memarea _area;

    MemDynBuff(const Memoffs& size):
        _area(new char[size.raw()], size)
    {}

    virtual ~MemDynBuff()
    {
        delete[] _area.start().raw();
    }

    virtual void clone(Mem::Implementation& cloneTo)
    {
        MemDynBuff& dest = cloneTo._stor.construct<MemDynBuff>(_area.size());
        memcpy(dest._area.start().raw(), _area.start().raw(), _area.size().raw());
    }

    virtual Memoffs size()
    {
        return _area.size();
    }

    virtual Memarea area()
    {
        return _area;
    }

    virtual Bool wrapper()
    {
        return false;
    }
};

namespace Impl
{
    void MemEmpty_init(Mem::Implementation& impl)
    {
        impl._stor.construct<MemEmpty>();
    }

    void MemDynBuff_init(Mem::Implementation& impl, const Memoffs& size,
                         Bool fillByZeroes)
    {
        MemDynBuff& mdb = impl._stor.construct<MemDynBuff>(size);
        if( fillByZeroes )
            memset(mdb._area.start().raw(), 0, size.raw());
    }
}
