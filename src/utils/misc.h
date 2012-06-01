
#pragma once



// Standard facade's implementation
#define PANDA_DECL_FACADE_IMPLEMENTATION()                                     \
public:                                                                        \
    struct Implementation {                                                    \
        Storage        _storage;                                               \
        const Methods* _methods;                                               \
        Implementation():                                                      \
            _storage(uninitialized)                                            \
        {}                                                                     \
        Implementation(const Implementation& from):                            \
            _storage(uninitialized),                                           \
            _methods(from._methods)                                            \
        {                                                                      \
            (*from._methods->_clone)(                                          \
                const_cast<Implementation&>(from), *this);                     \
        }                                                                      \
        Implementation& operator=(const Implementation& from)                  \
        {                                                                      \
            if( &from != this ) {                                              \
                (*_methods->_destruct)(*this);                                 \
                _methods = from._methods;                                      \
                (*from._methods->_clone)(                                      \
                    const_cast<Implementation&>(from), *this);                 \
            }                                                                  \
            return *this;                                                      \
        }                                                                      \
    };                                                                         \
private:                                                                       \
    mutable Implementation _impl;                                              \


// Declaration of constructor/destructor feature
//     checker  ensure or ensure_static
//     addr     expression evaluating address of object
//     size     expression evaluating memory size
#define PANDA_DECL_CTRDESTR_FEATURE(checker, addr, size)                       \
    template<class Object>                                                     \
    Object& construct() const {                                                \
        checker(sizeof(Object) <= (size));                                     \
        return *new(addr) Object();                                            \
    }                                                                          \
    template<class Object, class P1>                                           \
    Object& construct(const P1& p1) const {                                    \
        checker(sizeof(Object) <= (size));                                     \
        return *new(addr) Object(p1);                                          \
    }                                                                          \
    template<class Object, class P1, class P2>                                 \
    Object& construct(const P1& p1, const P2& p2) const {                      \
        checker(sizeof(Object) <= (size));                                     \
        return *new(addr) Object(p1, p2);                                      \
    }                                                                          \
    template<class Object, class P1, class P2, class P3>                       \
    Object& construct(const P1& p1, const P2& p2, const P3& p3) const {        \
        checker(sizeof(Object) <= (size));                                     \
        return *new(addr) Object(p1, p2, p3);                                  \
    }                                                                          \
    template<class Object, class P1, class P2, class P3, class P4>             \
    Object& construct(const P1& p1, const P2& p2, const P3& p3,                \
                      const P4& p4) const {                                    \
        checker(sizeof(Object) <= (size));                                     \
        return *new(addr) Object(p1, p2, p3, p4);                              \
    }                                                                          \
    template<class Object, class P1, class P2, class P3, class P4, class P5>   \
    Object& construct(const P1& p1, const P2& p2, const P3& p3, const P4& p4,  \
                      const P5& p5) const {                                    \
        checker(sizeof(Object) <= (size));                                     \
        return *new(addr) Object(p1, p2, p3, p4, p5);                          \
    }                                                                          \
    template<class Object, class P1, class P2, class P3, class P4, class P5,   \
             class P6>                                                         \
    Object& construct(const P1& p1, const P2& p2, const P3& p3, const P4& p4,  \
                      const P5& p5, const P6& p6) const {                      \
        checker(sizeof(Object) <= (size));                                     \
        return *new(addr) Object(p1, p2, p3, p4, p5, p6);                      \
    }                                                                          \
    template<class Object, class P1, class P2, class P3, class P4, class P5,   \
             class P6, class P7>                                               \
    Object& construct(const P1& p1, const P2& p2, const P3& p3, const P4& p4,  \
                      const P5& p5, const P6& p6, const P7& p7) const {        \
        checker(sizeof(Object) <= (size));                                     \
        return *new(addr) Object(p1, p2, p3, p4, p5, p6, p7);                  \
    }                                                                          \
    template<class Object> void destruct() const {                             \
        checker(sizeof(Object) <= (size));                                     \
        (addr)->~Object();                                                     \
    }                                                                          \


namespace Impl
{
    // to use in Mem* classes implementation
    void memoryCopy(const Memaddr& destination, const Memaddr& source, const Memoffs& length);
    void memoryZero(const Memaddr& destination, const Memoffs& length);
    Bool memoryEqual(
        const Memaddr& x, const Memoffs& xLength,
        const Memaddr& y, const Memoffs& yLength);

    // for memory block with statically known length
    template<Memoffs::Raw length>
    struct StaticMemArea
    {
        static void copy(const Memaddr& destination, const Memaddr& source)
        {
            memoryCopy(destination, source, length);
        }
        static void zero(const Memaddr& destination)
        {
            memoryZero(destination, length);
        }
    };

    // partial specializations
    template<>
    struct StaticMemArea<0>
    {
        static void copy(const Memaddr& destination, const Memaddr& source)
        {}
        static void zero(const Memaddr& destination)
        {}
    };

    template<>
    struct StaticMemArea<1>
    {
        static void copy(const Memaddr& destination, const Memaddr& source)
        {
            destination.objAt<Uint8>() = source.objAt<Uint8>();
        }
        static void zero(const Memaddr& destination)
        {
            destination.objAt<Uint8>() = 0;
        }
    };

    template<>
    struct StaticMemArea<2>
    {
        static void copy(const Memaddr& destination, const Memaddr& source)
        {
            destination.objAt<Uint16>() = source.objAt<Uint16>();
        }
        static void zero(const Memaddr& destination)
        {
            destination.objAt<Uint16>() = 0;
        }
    };

    template<>
    struct StaticMemArea<4>
    {
        static void copy(const Memaddr& destination, const Memaddr& source)
        {
            destination.objAt<Uint32>() = source.objAt<Uint32>();
        }
        static void zero(const Memaddr& destination)
        {
            destination.objAt<Uint32>() = 0;
        }
    };

    template<>
    struct StaticMemArea<8>
    {
        static void copy(const Memaddr& destination, const Memaddr& source)
        {
            destination.objAt<Uint64>() = source.objAt<Uint64>();
        }
        static void zero(const Memaddr& destination)
        {
            destination.objAt<Uint64>() = 0;
        }
    };

    template<Memoffs::Raw xLength, Memoffs::Raw yLength>
    struct StaticMemArea2
    {
        static Bool equal(const Memaddr& x, const Memaddr& y)
        {
            return false; // 'cause this calls only for different lengths
        }
    };

    template<Memoffs::Raw length>
    struct StaticMemArea2<length, length>
    {
        static Bool equal(const Memaddr& x, const Memaddr& y)
        {
            return memoryEqual(x, length, y, length);
        }
    };

    template<>
    struct StaticMemArea2<1, 1>
    {
        static Bool equal(const Memaddr& x, const Memaddr& y)
        {
            return x.objAt<Uint8>() == y.objAt<Uint8>();
        }
    };

    template<>
    struct StaticMemArea2<2, 2>
    {
        static Bool equal(const Memaddr& x, const Memaddr& y)
        {
            return x.objAt<Uint16>() == y.objAt<Uint16>();
        }
    };

    template<>
    struct StaticMemArea2<4, 4>
    {
        static Bool equal(const Memaddr& x, const Memaddr& y)
        {
            return x.objAt<Uint32>() == y.objAt<Uint32>();
        }
    };

    template<>
    struct StaticMemArea2<8, 8>
    {
        static Bool equal(const Memaddr& x, const Memaddr& y)
        {
            return x.objAt<Uint64>() == y.objAt<Uint64>();
        }
    };
}
