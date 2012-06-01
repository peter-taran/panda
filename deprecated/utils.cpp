
#include "../include/cppdragon.h"


void noreturn unreachable()
{
    // todo:
    throw 100;
}

void noreturn unreachable_m(const String &message)
{
    // todo:
    throw 100;
}

/*String asStr(Umem value)
{
    // todo
}*/

static const Umem lowBitSet[] = {
    LOWSETBITS(0),
    LOWSETBITS(1),
    LOWSETBITS(2),
    LOWSETBITS(3),
    LOWSETBITS(4),
    LOWSETBITS(5),
    LOWSETBITS(6),
    LOWSETBITS(7),
    LOWSETBITS(8),
    LOWSETBITS(9),
    LOWSETBITS(10),
    LOWSETBITS(11),
    LOWSETBITS(12),
    LOWSETBITS(13),
    LOWSETBITS(14),
    LOWSETBITS(15),
    LOWSETBITS(16),
};

Umem roundUp(const Umem value, const Umem exp2bound)
{
    ensure(exp2bound <= 16);
    
    Umem result = value;
    Umem mask = lowBitSet[exp2bound];
    result +=  mask;
    result &= ~mask;
    
    return result;
}

Umem roundDown(const Umem value, const Umem exp2bound)
{
    ensure(exp2bound <= 16);
    
    Umem result = value;
    Umem mask = lowBitSet[exp2bound];
    result &= ~mask;
    
    return result;
}
