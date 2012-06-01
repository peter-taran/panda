
#pragma once



Error::Error():
    _methods(0), _storage(uninitialized)
{}

Error::~Error()
{
    if( _methods != 0 )
        (*_methods->_destruct)(this->_storage);
}

Error::Error(const Error& from):
    _methods(from._methods), _storage(uninitialized)
{
    (*from._methods->_copy)(from._storage, this->_storage);
}

Error& Error::operator=(const Error& from)
{
    if( &from == this )
        return *this;
    this->~Error();
    return *new(this) Error(from);
}

void Error::throwThis() const
{
    (*_methods->_throwThis)(*this);
}

Str Error::description() const
{
    Str result = (*_methods->_description)(this->_storage);
    return result;
}



template<class NormalObject>
Err<NormalObject>::Err():
    _state(State_normalObject)
{
    _storage.memarea().construct<NormalObject>();
}

template<class NormalObject>
Err<NormalObject>::Err(const Uninitialized&):
    _state(State_uninitialized)
{}

template<class NormalObject>
template<class SpecificError>
Err<NormalObject>::Err(const SpecificError& error):
    _state(State_error)
{
    _storage.memarea().construct<SpecificError>(error);
}

template<class NormalObject>
Err<NormalObject>::~Err()
{
    switch(_state)
    {
    case State_normalObject:
        _storage.memarea().destruct<NormalObject>();
        break;
    case State_error:
        _storage.memarea().destruct<Error>();
        break;
    }
}

template<class NormalObject>
Err<NormalObject>::Err(const Err& from):
    _state(from._state)
{
    switch(_state)
    {
    case State_normalObject:
        _storage.memarea().addrAt(0).as<NormalObject&>() =
            from._storage.memarea().addrAt(0).as<NormalObject&>();
        break;
    case State_error:
        _storage.memarea().addrAt(0).as<Error&>() =
            from._storage.memarea().addrAt(0).as<Error&>();
        break;
    }
}

template<class NormalObject>
Err<NormalObject>& Err<NormalObject>::operator=(const Err& from)
{
    if( &from == this )
        return *this;
    this->~Err();
    return *new(this) Err(from);
}
