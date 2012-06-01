
#pragma once



// Abstract memory buffer
class Mem: public
    boost::equality_comparable<Mem
    >
{
public:
    // This class
    typedef Mem This;

    // initialization
    inline Mem(const Memoffs& size); // zero-filled buffer of specified size
    inline Mem(const Memoffs& size, const Uninitialized&); // uninitialized buffer of specified size
    template<Memoffs::Raw buffSize>
    inline Mem(const Membuff<buffSize>& from);
    // TODO: initialize from POD-type with cloning

    // copy, assignment, swap
    inline Mem(const Mem& from);
    inline Mem& operator=(const Mem& from);
    inline void swap(Mem& y);

    // Destruction
    inline ~Mem();

    // comparison of memory contents
    inline Bool operator==(const Mem& y) const;

    // properties
    inline Memoffs size() const; // size of area in bytes
    inline Bool    empty() const; // empty area

    // treat this as memarea
    inline Memarea area() const;
    inline operator Memarea() const;

    // address in area by given offset
    inline Memaddr addrAt(const Memoffs& offset) const;
    inline Memaddr addrAt(const Memoffs& offset, const Dontcheck&) const;

    // TODO: array methods
    // Seq<const Object> asSeq() const
    // Seq<Object> asSeq()

    // object in area at given offset
    template<class Object> inline Object& objAt(const Memoffs& offset = 0) const;
    template<class Object> inline Object& objAt(const Memoffs& offset, const Dontcheck&) const;

    // is wrapper?
    inline Bool wrapper() const;
    inline This& unwrap(); // make contents owned

    // methods to construct and destruct object in memory
    PANDA_DECL_CTRDESTR_FEATURE(ensure, &objAt<Object>(), size())



    // implementation
    struct Methods;
    typedef Type::FacadeImpl<Methods, sizeof(Memarea)> Implementation;
    struct Methods: Type::FacadeBaseMethods
    {
        virtual void clone(Implementation& cloneTo) = 0;
        virtual Memoffs size() = 0;
        virtual Memarea area() = 0;
    };
    inline explicit Mem(Implementation*& implPointer);

private:
    Implementation _impl;
};