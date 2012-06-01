
enum TTKind // todo: replace with strict enum
{
    TTKind_object,
    TTKind_func,
    TTKind_ref,
    TTKind_void,
};

namespace CPPDRG_NS
{

// types, identifying different kinds of types
struct TTKind_Object {};
struct TTKind_Func   {};
struct TTKind_Ref    {};
struct TTKind_Void   {};

template<class Type, class Void>
struct TTKindSelect_Func
{
    typedef TTKind_Object kindTag;
};

template<class Type>
struct TTKindSelect_Func<Type, boost::true_type>
{
    typedef TTKind_Func kindTag;
};

template<class Type, class Void>
struct TTKindSelect_Ref:
    TTKindSelect_Func< Type, typename boost::is_function<Type>::type >
{};

template<class Type>
struct TTKindSelect_Ref<Type, boost::true_type>
{
    typedef TTKind_Ref kindTag;
};

template<class Type, class Void>
struct TTKindSelect_Void:
    TTKindSelect_Ref< Type, typename boost::is_reference<Type>::type >
{};

template<class Type>
struct TTKindSelect_Void<Type, boost::true_type>
{
    typedef TTKind_Void kindTag;
};

template<class Type>
struct TTKindSelect:
    TTKindSelect_Void< Type, typename boost::is_void<Type>::type >
{};



template<class Type, class Kind>
struct TT
{}; // unused

template<class Type>
struct TT<Type, TTKind_Void>
{
    static const TTKind kind = TTKind_void;
    typedef TTKind_Void kindType;
};

template<class Type>
struct TT<Type, TTKind_Func>
{
    static const TTKind kind = TTKind_func;
    typedef TTKind_Func kindType;
};

template<class Type>
struct TT<Type, TTKind_Ref>
{
    static const TTKind kind = TTKind_ref;
    typedef TTKind_Ref kindType;
};

template<class Type>
struct TT<Type, TTKind_Object>
{
    static const TTKind kind = TTKind_object;
    typedef TTKind_Object kindType;

	static const Umem size = Umem(sizeof(Type));

    //typedef ??? clonable;
    //typedef ??? trivialDestructor;
    //typedef ??? equalComparable;

    // you can store pointers to this functions for static casting of current
    // Type to To-class
    template<class To> static To&   statCastTo        (Type &from);
    template<class To> static To*   statPtrCastTo     (Type *from);
    template<class To> static void* statPtrCastTo_void(void *from);

    // dynamic casting
    template<class To> static To&   dynCastTo        (Type &from);
    template<class To> static To*   dynPtrCastTo     (Type *from);
    template<class To> static void* dynPtrCastTo_void(void *from);
};

} // namespace CPPDRG_NS

template<class Type_>
struct TT: // TT = type traits
    public CPPDRG_NS::TT< Type_, typename CPPDRG_NS::TTKindSelect<Type_>::kindTag >
{
    typedef Type_ Type;
};
