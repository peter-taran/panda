
namespace Impl
{

template<class SignTag, unsigned byteCount>
struct IntHelper
{
    // ERROR: you can use only Signed and Unsigned types
    //ensure_static(false);
};

template<unsigned byteCount>
struct IntHelper<Signed, byteCount>
{
    typedef typename boost::int_t <byteCount*8>::exact Type;
    typedef typename boost::uint_t<byteCount*8>::exact Utype;

    static const Type smallest = Type(Type(1) << (byteCount*8 - 1));
    static const Type largest  = Type(Utype(smallest) - 1);
    static const bool signedType = true;

    static void boundedPlus(Type& x, const Type& y)
    {
        // TODO: optimize check
        Type xOld = x;
        x += y;
        if( y >= 0 )
        {
            if( x < xOld )
                throw "signed integer op+ overfloat";
                // TODO: good exception class
                // TODO: name of throwing class and detailed message
        }
        else
        {
            if( x > xOld )
                throw "signed integer op+ underfloat";
                // TODO: good exception class
                // TODO: name of throwing class and detailed message
        }
    }

    static void boundedMinus(Type& x, const Type& y)
    {
        // TODO: optimize check
        Type xOld = x;
        x -= y;
        if( y < 0 )
        {
            if( x < xOld )
                throw "signed integer op- overfloat";
                // TODO: good exception class
                // TODO: name of throwing class and detailed message
        }
        else
        {
            if( x > xOld )
                throw "signed integer op- underfloat";
                // TODO: good exception class
                // TODO: name of throwing class and detailed message
        }
    }

    static void boundedMultiply(Type& x, const Type& y)
    {
        /*static const unsigned upperBitN = byteCount * 8 - 1;
        static const Utype upperMask = Utype(1) << upperBitN;

        if(
            (x & upperMask) != ((x << 1) & upperMask) &&
            (y & upperMask) != ((y << 1) & upperMask)
          )
            throw "signed integer op* overfloat";*/

        // TODO: doesn't work!

        x *= y;
        // TODO: good exception class
        // TODO: name of throwing class and detailed message
    }
};

template<unsigned byteCount>
struct IntHelper<Unsigned, byteCount>
{
    typedef typename boost::uint_t<byteCount*8>::exact Type;

    static const Type smallest = 0;
    static const Type largest  = Type(smallest - 1);
    static const bool signedType = false;

    static void boundedPlus(Type& x, const Type& y)
    {
        Type xOld = x;
        x += y;
        if( x < xOld )
            throw "unsigned integer op+ overfloat";
            // TODO: good exception class
            // TODO: name of throwing class and detailed message
            // TODO: optimize check
    }

    static void boundedMinus(Type& x, const Type& y)
    {
        Type xOld = x;
        x -= y;
        if( x > xOld )
            throw "unsigned integer op- underfloat";
            // TODO: good exception class
            // TODO: name of throwing class and detailed message
            // TODO: optimize check
    }

    static void boundedMultiply(Type& x, const Type& y)
    {
        /*static const unsigned upperBitN = byteCount * 8 - 1;
        static const Type upperValue = Type(1) << upperBitN;

        const Type& bigger  = x > y ? x : y;
        const Type& smaller = x > y ? y : x;
        const Type checkValue = ((bigger >> 1) * smaller);
        if( checkValue >= upperValue )
            throw "unsigned integer op* overfloat";*/

        // TODO: doesn't work!

        x *= y;
        // TODO: good exception class
        // TODO: name of throwing class and detailed message
    }
};

template<class Super = Null>
struct CyclicArithmetic: public Super
{
protected:
    template<class SignTag, unsigned byteCount>
    static void _plus(
        typename IntHelper<SignTag, byteCount>::Type& x,
        const typename IntHelper<SignTag, byteCount>::Type& y)
    {
        x += y;
    }

    template<class SignTag, unsigned byteCount>
    static void _minus(
        typename IntHelper<SignTag, byteCount>::Type& x,
        const typename IntHelper<SignTag, byteCount>::Type& y)
    {
        x -= y;
    }

    template<class SignTag, unsigned byteCount>
    static void _multiply(
        typename IntHelper<SignTag, byteCount>::Type& x,
        const typename IntHelper<SignTag, byteCount>::Type& y)
    {
        x *= y;
    }
};

template<class Super = Null>
struct BoundedArithmetic: public Super
{
    template<class SignTag, unsigned byteCount>
    static void _plus(
        typename IntHelper<SignTag, byteCount>::Type& x,
        const typename IntHelper<SignTag, byteCount>::Type& y)
    {
        IntHelper<SignTag, byteCount>::boundedPlus(x, y);
    }

    template<class SignTag, unsigned byteCount>
    static void _minus(
        typename IntHelper<SignTag, byteCount>::Type& x,
        const typename IntHelper<SignTag, byteCount>::Type& y)
    {
        IntHelper<SignTag, byteCount>::boundedMinus(x, y);
    }

    template<class SignTag, unsigned byteCount>
    static void _multiply(
        typename IntHelper<SignTag, byteCount>::Type& x,
        const typename IntHelper<SignTag, byteCount>::Type& y)
    {
        IntHelper<SignTag, byteCount>::boundedMultiply(x, y);
    }
};

}
