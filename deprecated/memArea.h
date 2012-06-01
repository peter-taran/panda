
// Memory area bounds
class MemArea: public
    boost::partially_ordered<MemArea
    >
{
    Addr _start;
    Addr _afterEnd;

public:
    inline MemArea();
    inline MemArea(Uninitialized);
    inline MemArea(Addr start, Adif size);
    inline MemArea(Addr start, Addr afterEnd);
    inline MemArea(const MemArea &from);
    inline MemArea& operator=(const MemArea &from);
    
    inline Addr start() const;
    inline Addr afterEnd() const;
    inline Adif size() const;
    
    Addr operator[](Adif offset) const;
    inline Addr byoffset(Adif offset) const;
    MemArea begArea(Adif size) const;
    MemArea begArea(Addr afterEnd) const;
    MemArea midArea(Adif offset, Adif size) const;
    MemArea endArea(Adif size) const;
    MemArea endArea(Addr start) const;
    
    inline bool addrInside(Addr address) const;
    
    inline bool operator<(const MemArea &y) const;
    
    template<Umem size>
    static MemArea array(const boost::array<char, size> &a)
    { return MemArea(Addr(a.elems), Adif(size)); }

    template<Umem size>
    static MemArea array(const char (&a)[size])
    { return MemArea(Addr(&a), Adif(size)); }

    static MemArea cptr(const char *str)
    { return MemArea(Addr(str), Adif(strlen(str))); }
};
