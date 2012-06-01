
namespace CPPDRG_NS
{

template<class Type>
template<class To> To& TT<Type, TTKind_Object>::statCastTo(Type &from)
{
    return static_cast<To&>(from);
}

template<class Type>
template<class To> To* TT<Type, TTKind_Object>::statPtrCastTo(Type *from)
{
    return static_cast<To*>(from);
}

template<class Type>
template<class To> void* TT<Type, TTKind_Object>::statPtrCastTo_void(void *from)
{
    return dynamic_cast<To*>(static_cast<Type*>(from));
}

template<class Type>
template<class To> To& TT<Type, TTKind_Object>::dynCastTo(Type &from)
{
    return dynamic_cast<To&>(from);
}

template<class Type>
template<class To> To* TT<Type, TTKind_Object>::dynPtrCastTo(Type *from)
{
    return dynamic_cast<To*>(from);
}

template<class Type>
template<class To> void* TT<Type, TTKind_Object>::dynPtrCastTo_void(void *from)
{
    return static_cast<To*>(static_cast<Type*>(from));
}

} // namespace CPPDRG_NS
