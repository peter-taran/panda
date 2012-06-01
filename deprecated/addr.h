
// Address in memory
class Addr: public
    boost::additive<Addr, Adif,
    boost::additive<Addr, Umem,
    boost::unit_steppable<Addr,
    boost::totally_ordered<Addr
    > > > >
{
    friend class Adif;
    const char *_addr;
    
public:
    inline Addr();
    inline Addr(Uninitialized);
    inline explicit Addr(const void* address);
    inline Addr(const Addr &from);
    inline Addr& operator=(const Addr &from);
    
    inline static Addr sys(Umem address);
    
    inline void* asVoid() const;
    inline char* asPtr() const;
    inline Umem asFlat() const;
    
    template<class Result> Result& at() const
    { return *static_cast<Result*>(static_cast<void*>(const_cast<char*>(_addr))); }
    
    inline Addr& operator+=(Adif offset);
    inline Addr& operator+=(Umem offset);
    inline Addr& operator-=(Adif offset);
    inline Addr& operator-=(Umem offset);
    inline Addr& operator++();
    inline Addr& operator--();
    
    inline Addr& alignUp(Umem exp2bound);
    inline Addr alignedUp(Umem exp2bound) const;
    inline Addr& alignDown(Umem exp2bound);
    inline Addr alignedDown(Umem exp2bound) const;

    inline Adif operator-(const Addr &y) const;
    
    inline bool operator<(const Addr &y) const;
    inline bool operator==(const Addr &y) const;
    
    typedef bool (Addr::*BoolCheckable)() const;
    inline operator BoolCheckable() const;
    inline bool operator!() const;
};
