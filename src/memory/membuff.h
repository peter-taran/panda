

#pragma once



// Memory buffer of fixed size
// TODO: maybe it's a typedef to Array<Byte, size> ?
template<Memoffs::Raw size_>
class Membuff: public
    boost::equality_comparable<Membuff<size_>
    >
{
public:
    // Type parameters
    static const Memoffs::Raw size = size_; // equal to sizeof(This)

    // This type
    typedef Membuff<size> This;

    // initialization
    inline Membuff(); // zero-initialized buffer
    inline Membuff(const Uninitialized&); // uninitialized buffer
    static inline Membuff filled(const Byte& filler); // byte-filled buffer

    // initialization by copying memory, associated with object
    template<class Object>
    explicit inline Membuff(const Object& object);

    // copy-n-assignment
    inline Membuff(const Membuff& from); // copy of same-sized buffer
    inline Membuff& operator=(const Membuff& from);

    // filling
    inline This& fill(Byte byte); // fill by specified byte

    // comparison of memory contents
    inline Bool operator==(const Membuff& y) const;
    // TODO: comparison with buffer of other size?

    // is empty?
    bool empty() const { return size == 0; }

    // treat this as memarea
    inline Memarea area() const;
    inline operator Memarea() const;

    // address in buffer at given offset
    inline Memaddr addrAt(const Memoffs& offset) const;
    inline Memaddr addrAt(const Memoffs& offset, const Dontcheck&) const;

    // object in buffer at given offset
    template<class Object> inline const Object& cobjAt(const Memoffs& offset = 0) const;
    template<class Object> inline const Object& cobjAt(const Memoffs& offset, const Dontcheck&) const;
    template<class Object> inline Object& objAt(const Memoffs& offset = 0);
    template<class Object> inline Object& objAt(const Memoffs& offset, const Dontcheck&);

    // TODO: array methods
    // Array<const Object> asArray() const
    // Array<Object> asArray()
    // Seq<const Object> asSeq() const
    // Seq<Object> asSeq()

    // methods to construct and destruct object in memory
    PANDA_DECL_CTRDESTR_FEATURE(ensure_static, static_cast<Object*>(static_cast<void*>(&_data)), size)

private:
    mutable Byte _data[size]; // TODO: replace with Array?
};

// TODO: Membuff and Memarea interfaces must be mostly equal, Membuff seems to be a kind of Memarea