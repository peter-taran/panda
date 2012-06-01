
#pragma once



// Address in memory
// TODO: need to decide: zero-address and null value are same or different? so, if(Memaddr), if(!Memaddr) are the same
class Memaddr: public
    boost::totally_ordered<Memaddr,
    boost::totally_ordered<Memaddr, const void*,
    boost::unit_steppable<Memaddr,
    boost::additive<Memaddr, Memoffs
    > > > >
{
public:
    // initialization
    inline Memaddr();
    inline Memaddr(const Uninitialized&);
    inline Memaddr(const void* const from);

    // copy-n-assignment
    inline Memaddr(const Memaddr& from);
    inline Memaddr& operator=(const Memaddr& from);

    // raw (unmanaged by Panda) value
    inline void* raw() const;

    // treat address as pointer or reference to object
    template<class Object> Object& objAt() const;

    // comparison
    inline Bool operator<(const Memaddr &y) const;
    inline Bool operator==(const Memaddr &y) const;

    // increment/decrement address by bytes
    inline Memaddr& operator++();
    inline Memaddr& operator--();

    // arithmetic with memory offsets
    inline Memaddr& operator+=(const Memoffs& y);
    inline Memaddr& operator-=(const Memoffs& y);
    inline Memoffs  operator- (const Memaddr& y) const;

    // TODO: align up and down to boundary (or include it to Memalign class?)

private:
    void* _addr;
};
