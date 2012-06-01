
#pragma once



// Represents area in memory
class Memarea: public
    boost::equality_comparable<Memarea
    >
{
public:
    // This type
    typedef Memarea This;

    // initialization
    inline Memarea(); // empty area: zero start and zero end
    inline Memarea(const Uninitialized&);
    inline Memarea(const Memaddr& start, const Memaddr& end);
    inline Memarea(const Memaddr& start, const Memoffs& size);

    // copy-n-assignment
    inline Memarea(const Memarea& from);
    inline Memarea& operator=(const Memarea& from);

    // comparison
    // note: empty Memarea is equal to any other empty Memarea
    inline Bool operator==(const Memarea& y) const;

    // comparison of memory contents
    inline Bool memEqual(const Memarea& y) const;

    // copy memory content
    inline void memCopyTo(const Memaddr& to) const;
    inline void memCopyTo(const Memarea& to) const;

    // properties
    inline Memaddr start() const; // addres of first byte
    inline Memaddr end() const; // addres after last byte
    inline Memoffs size() const; // size of area in bytes
    inline Bool    empty() const; // empty area

    // address in area by given offset
    inline Memaddr addrAt(const Memoffs& offset) const;
    inline Memaddr addrAt(const Memoffs& offset, const Dontcheck&) const;

    // object in area at given offset
    template<class Object> inline Object& objAt(const Memoffs& offset = 0) const;
    template<class Object> inline Object& objAt(const Memoffs& offset, const Dontcheck&) const;

    // TODO: method Seq<Type> asSeq() const

    // head of area
    // offset  > 0: head of offset size
    // offset == 0: empty area
    // offset  < 0: head until end-offset position
    inline Memarea head(const Memoffs& offset) const;
    // TODO: dontcheck pair

    // tail of area
    // offset  > 0: tail area, starting from offset
    // offset == 0: the same area
    // offset  < 0: tail area, having size == -offset
    inline Memarea tail(const Memoffs& offset) const;
    // TODO: dontcheck pair

    // split area into two ones
    // returns (head(offset), tail(offset))
    inline std::pair<Memarea, Memarea> split(const Memoffs& offset) const;
    // TODO: dontcheck pair

    // returns head, leaving in *this tail
    // &
    // returns tail, leaving in *this head
    inline Memarea extractHead(const Memoffs& offset);
    inline Memarea extractTail(const Memoffs& offset);
    // TODO: dontcheck pairs

    // methods to construct and destruct object in memory
    PANDA_DECL_CTRDESTR_FEATURE(ensure, &_start.objAt<Object>(), _size)

private:
    Memaddr _start;
    Memoffs _size;
};
