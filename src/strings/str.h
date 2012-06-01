
#pragma once



// Str class holds constant NON-EMPTY string of any size
class Str: public
    boost::equality_comparable<Str
    >
{
public:
    // This type
    typedef Str This;
    
    // initialization
    inline Str(const Null&); // TODO: надо убрать эту фичу и инициализировать всегда
    //inline Str(const wchar_t* wideCharsZeroTerm); // zero-terminated string of built-in wide characters
    inline Str(const char* asciiCharsZeroTerm); // zero-terminated string of built-in characters
    //inline Str(const Memarea& data, const Encoding& encoding);
    //inline Str(const InputStream& stream, const Encoding& encoding);
    //inline Str(const Seq<Char>& characters);
    //template<class Iterator> inline Str(Iterator begin, Iterator end);

    // copy-n-assignment
    inline Str(const Str& from);
    inline Str& operator=(const Str& from);

    // Destruction
    inline ~Str();

    // length
    inline Memoffs length() const;
    // TODO: lazy length

    // access to characters
    inline Char at(const Memoffs& index) const;
    inline Char operator[](const Memoffs& index) const;

    // comparison for equality (absolute equality)
    inline Bool operator==(const Str& y) const;

    // does Str wraps another object (and dependent on it's existent and immutability)?
    // false - Str manages containing data itself
    inline Bool wrapper() const;

    // swaps two Str's
    inline void swap(Str& y);



    // implementation
    struct Methods;
    typedef Type::FacadeImpl<Methods, 12> Implementation;
    struct Methods: Type::FacadeBaseMethods
    {
        // copy string to
        // copied string MUST NOT be wrapper (should manage character data)
        virtual void clone(Implementation& copyTo) = 0;

        // return length of the string
        virtual Memoffs length() = 0;

        // return character by index
        virtual Char charAt(const Memoffs& index) = 0;
    };
    inline explicit Str(Implementation*& implPointer);

private:
    Implementation _impl;
    //PANDA_DECL_FACADE_IMPLEMENTATION()
};
