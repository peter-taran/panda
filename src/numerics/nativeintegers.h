
#pragma once



// tag types to declare signed and unsigned integers
struct Signed {};
struct Unsigned {};

// operations over integers are:
// - assignment      changing value for another one through operator=
//                   can be allowed or disabled
// - in[de]crement   ++value and --value
//                   can be disabled or allowed with, or without bound checks
// - plus and minus  can be disabled or allowed with, or without bound checks
// - multiplication  TODO
// - division        TODO
// TODO: implement selective declaration of integer types

#include "nativeintegers_impl.h"

template<class Value_>
class IntDivRes
{
public:
    // type of values
    typedef Value_ Value;

    // has no default constructor

    // initialization
    inline IntDivRes(Value& result, const Value& remainder);

    // default generated copy-n-assign

    // divide result and divide remainder
    Value& res() const {return _res;}
    Value  rem() const {return _rem;}

    // default transformable to result
    operator Value&() const {return _res;}

private:
    Value& _res;
    Value  _rem;
};

#define PANDA_INT_ARITHMETIC_CYCLIC   Impl::CyclicArithmetic<Null>
#define PANDA_INT_ARITHMETIC_BOUNDED  Impl::BoundedArithmetic<Null>

#ifndef PANDACFG_INT_ARITHMETIC
    #define PANDACFG_INT_ARITHMETIC PANDA_INT_ARITHMETIC_CYCLIC
#endif

template<class SignTag_, unsigned byteCount_,
    class Traits_ = PANDACFG_INT_ARITHMETIC
>
class IntOf: public
    boost::totally_ordered<IntOf<SignTag_, byteCount_, Traits_>, // TODO: replace totally_ordered with Bool-returning ones
    boost::additive       <IntOf<SignTag_, byteCount_, Traits_>,
    boost::multipliable   <IntOf<SignTag_, byteCount_, Traits_>,
    boost::dividable      <IntOf<SignTag_, byteCount_, Traits_>,
    boost::unit_steppable <IntOf<SignTag_, byteCount_, Traits_>,
    Traits_
    > > > > >
{
public:
    // Type parameters
    typedef SignTag_ SignTag;
    typedef Traits_  Traits;
    static const unsigned byteCount = byteCount_;
    static const unsigned bitCount  = byteCount * 8;

    // This type
    typedef IntOf<SignTag, byteCount, Traits> This;

    // ERROR: byte count must be degree of 2
    ensure_static(0 == ((byteCount-1) & byteCount));

    // raw type to represent integer
    typedef typename Impl::IntHelper<SignTag, byteCount>::Type Raw;

    // signed type flag
    static Bool signedType() {return Impl::IntHelper<SignTag, byteCount>::signedType;}

    // smallest and largest values of the type
    static IntOf smallest() {return Impl::IntHelper<SignTag, byteCount>::smallest;}
    static IntOf largest () {return Impl::IntHelper<SignTag, byteCount>::largest;}
    static const Raw smallest_static = Impl::IntHelper<SignTag, byteCount>::smallest;
    static const Raw largest_static  = Impl::IntHelper<SignTag, byteCount>::largest;

    // initialization
    inline IntOf();
    inline IntOf(const Uninitialized&);
    inline IntOf(Raw from);

    // initialization from other IntOf's
    template<class From_SignTag, unsigned From_byteCount, class From_Traits>
    explicit IntOf(const IntOf<From_SignTag, From_byteCount, From_Traits>& from);

    // copy-n-assignment
    inline IntOf(const IntOf& from);
    inline IntOf& operator=(const IntOf& from);

    // return raw value
    inline Raw raw() const;

    // comparison and ordering
    inline Bool operator==(const IntOf& y) const;
    inline Bool operator<(const IntOf& y) const;
    friend inline Bool operator==(const Raw& x, const IntOf& y) {return IntOf(x)==y;}
    friend inline Bool operator<(const Raw& x, const IntOf& y) {return IntOf(x)<y;}

    // increment/decrement
    inline IntOf& operator++();
    inline IntOf& operator--();

    // add/subtract
    inline IntOf& operator+=(const IntOf& y);
    inline IntOf& operator-=(const IntOf& y);
    inline IntOf& add(const IntOf& y);
    inline IntOf& add(const IntOf& y, const Dontcheck&);
    inline IntOf& subtract(const IntOf& y);
    inline IntOf& subtract(const IntOf& y, const Dontcheck&);

    // multiplication
    inline IntOf& operator*=(const IntOf& y);
    inline IntOf& multiply(const IntOf& y);
    inline IntOf& multiply(const IntOf& y, const Dontcheck&);

    // division
    inline IntDivRes<This> operator/=(const IntOf& y);
    inline IntDivRes<This> divide(const IntOf& y);
    inline IntDivRes<This> divide(const IntOf& y, const Dontcheck&);

private:
    Raw _value;
};

// TODO: make macroses to simplify creation of derived classes

// Fastest platform-dependent integer
typedef unsigned int Uint;
typedef   signed int Int;
ensure_static(sizeof(Int) >= 4);


// 8-bit integers, byte
typedef boost:: int_t<8>::exact Int8;
typedef boost::uint_t<8>::exact Uint8;

// 16-bit integers
typedef boost:: int_t<16>::exact Int16;
typedef boost::uint_t<16>::exact Uint16;

// 32-bit integers
typedef boost:: int_t<32>::exact Int32;
typedef boost::uint_t<32>::exact Uint32;

// 64-bit integers
typedef boost:: int_t<64>::exact Int64;
typedef boost::uint_t<64>::exact Uint64;


// TODO: replace boost's integers with special classes