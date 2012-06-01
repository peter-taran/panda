
#pragma once



// Base (almost) abstract class for any panda-error
class Error
{
public:
    // This type
    typedef Error This;

    // initialization
    // no public initialization, instantiate more specific error classes

    // destruction
    inline ~Error();

    // copy-n-assignment
    inline Error(const Error& from);
    inline Error& operator=(const Error& from);

    // throw this error as exception
    inline void throwThis() const;

    // description test
    inline Str description() const;

    // error, being cause of this (null, if absent)
    // TODO: Nullable<Error> cause() const;



    // implementation structures
    typedef Membuff<sizeof(Str)+sizeof(Memaddr)> InternalStorage;
    struct Methods
    {
        // destruct all data in storage
        typedef void (Destruct)(InternalStorage& storage);
        Destruct* _destruct;

        // copy Error object to
        typedef void (Copy)(InternalStorage& storage, InternalStorage& copyTo);
        Copy* _copy;

        // throw error as exception
        typedef void (ThrowThis)(const Error& error);
        ThrowThis* _throwThis;

        // return error description
        typedef Str (Description)(InternalStorage& storage);
        Description* _description;
    };

protected:
    inline Error();

    const   Methods*        _methods;
    mutable InternalStorage _storage;
};


// Class, containing error or normal object
template<class NormalObject_>
class Err
{
public:
    // Type parameters
    typedef NormalObject_ NormalObject;

    // This type
    typedef Err This;

    // initialization
    inline Err(); // with default-constructed NormalObject
    inline Err(const Uninitialized&); // in uninitialized state
    template<class SpecificError>
    inline Err(const SpecificError& error); // with error

    // destruction
    inline ~Err();

    // copy-n-assignment
    inline Err(const Err& from);
    inline Err& operator=(const Err& from);

private:
    enum State {
        State_uninitialized = -1,
        State_normalObject  =  0,
        State_error         =  1,
    };
    State _state;
    static const Memoffs::Raw _storageSize =
        sizeof(Error) > sizeof(NormalObject) ? sizeof(Error) : sizeof(NormalObject);
    Membuff<_storageSize> _storage;
};

// 
class AssertionError: public Error
{
public:
    AssertionError(const Str& text);
};
