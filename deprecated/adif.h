
// Memory offset, memory address difference or memory size
// Cannot hold negative offsets, positive or zero only
class Adif: public
    boost::additive<Adif, Adif,
    boost::additive<Adif, Umem,
    boost::unit_steppable<Adif,
    boost::multiplicative<Adif, Umem,
    boost::subtractable2_left<Addr, Adif,
    boost::totally_ordered<Adif, Adif,
    boost::totally_ordered<Adif, Umem
    > > > > > > >
{
    friend class Addr;
    Umem _diff;

public:
    inline Adif();
    inline Adif(Uninitialized);
    inline explicit Adif(Umem difference);
    inline Adif(const Adif &from);
    inline Adif& operator=(const Adif &from);
    
    inline Umem asRaw() const;
    
    inline bool zero() const;

    inline Adif& operator++();
    inline Adif& operator--();
    inline Adif& operator+=(Adif y);
    inline Adif& operator+=(Umem y);
    inline Adif& operator-=(Adif y);
    inline Adif& operator-=(Umem y);
    inline Adif& operator*=(Umem y);
    inline Adif& operator/=(Umem y);
    
    inline Adif& roundUp(Umem exp2bound);
    inline Adif roundedUp(Umem exp2bound) const;
    
    inline Adif& roundUp4();
    inline Adif roundedUp4() const;
    inline Adif& roundUp8();
    inline Adif roundedUp8() const;
    inline Adif& roundUp16();
    inline Adif roundedUp16() const;
    
    inline bool operator<(Adif y) const;
    inline bool operator==(Adif y) const;
    inline bool operator<(Umem y) const;
    inline bool operator>(Umem y) const;
    inline bool operator==(Umem y) const;
};
const Adif adif0;
