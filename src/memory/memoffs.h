
#pragma once



// Integer, representing offset in memory
// It has same size as Memaddr.
class Memoffs: public
    boost::totally_ordered<Memoffs,
    boost::totally_ordered<Memoffs, IntOf<Signed, sizeof(void*)>::Raw, // see Raw type
    boost::additive<Memoffs,
    boost::unit_steppable<Memoffs
    > > > >
{
public:
    // integer types to represent memory offset & memory size
    // TODO: вопрос с интеграцией с IntOf-ом не решён, арифметику бы на нём строить
    /*typedef IntOf<Signed,   sizeof(void*)> Int;         // panda signed integer
    typedef IntOf<Unsigned, sizeof(void*)> UnsignedInt; // panda unsigned integer*/
    typedef IntOf<Signed, sizeof(void*)>::Raw Raw;        // built-in integer type

    // initialization
    inline Memoffs();
    inline Memoffs(const Uninitialized&);
    /*explicit inline Memoffs(const Int& from);
    explicit inline Memoffs(const UnsignedInt& from);*/
    inline Memoffs(Raw from);

    // copy-n-assignment
    inline Memoffs(const Memoffs& from);
    inline Memoffs& operator=(const Memoffs& from);

    // raw value of offset
    /*inline Int asInt() const;
    inline UnsignedInt asUnsigned() const;*/
    inline Raw raw() const;

    // comparison
    inline Bool operator<(const Memoffs &y) const;
    inline Bool operator<(const Raw &y) const;
    inline Bool operator==(const Memoffs &y) const;
    inline Bool operator==(const Raw &y) const;

    // increment/decrement offset by bytes
    inline Memoffs& operator++();
    inline Memoffs& operator--();

    // unary minus
    inline Memoffs operator-() const;

    // arithmetic with Memoffs'es
    inline Memoffs& operator+=(const Memoffs& y);
    inline Memoffs& operator-=(const Memoffs& y);

private:
    Raw _offs;
};
