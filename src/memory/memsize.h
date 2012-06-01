
#pragma once



// Memory size or byte counter
class Memsize: public
    boost::totally_ordered<Memsize,
    boost::totally_ordered<Memsize, IntOf<Unsigned, sizeof(void*)>::Raw, // see Raw type
    boost::additive<Memsize,
    boost::unit_steppable<Memsize
    > > > >
{
public:
    // This type
    typedef Memsize This;

    // integer type to represent memory size
    typedef IntOf<Unsigned, sizeof(void*)>::Raw Raw;

    // initialization
    inline Memsize();
    inline Memsize(const Uninitialized&);
    inline Memsize(Raw from);

    // copy-n-assignment
    inline Memsize(const Memsize& from);
    inline Memsize& operator=(const Memsize& from);

    // raw value of memory size
    inline Raw raw() const;

    // comparison
    inline Bool operator<(const Memsize &y) const;
    inline Bool operator<(const Raw &y) const;
    inline Bool operator==(const Memsize &y) const;
    inline Bool operator==(const Raw &y) const;

    // increment/decrement offset by bytes
    inline Memsize& operator++();
    inline Memsize& operator--();

    // arithmetic with Memoffs'es
    inline Memsize& operator+=(const Memsize& y);
    inline Memsize& operator-=(const Memsize& y);

private:
    Raw _offs;
};
