
#include "../../panda.h"



namespace Impl
{
    void memoryCopy(const Memaddr& destination, const Memaddr& source, const Memoffs& length)
    {
        // TODO: replace with non-CRT implementation
        memcpy(destination.raw(), source.raw(), length.raw());
    }

    void memoryZero(const Memaddr& destination, const Memoffs& length)
    {
        // TODO: replace with non-CRT implementation
        memset(destination.raw(), 0, length.raw());
    }

    Bool memoryEqual(
        const Memaddr& x, const Memoffs& xLength,
        const Memaddr& y, const Memoffs& yLength)
    {
        if( xLength == yLength )
            // TODO: replace with non-CRT implementation
            return 0 == memcmp(x.raw(), y.raw(), xLength.raw());
        else
            return false;
    }
}
