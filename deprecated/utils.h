// Number of items in static-sized array
namespace CPPDRG_NS
{
    template <Umem N>
    struct TypeWhichHasSizeExactly{ typedef char (&type)[N]; };

    template <typename ArrayElementT, Umem N>
    typename TypeWhichHasSizeExactly<N>::type arrayLengthHelper(ArrayElementT (&)[N]);

    template <typename ArrayElementT, Umem N>
    typename TypeWhichHasSizeExactly<N>::type arrayLengthHelper(const boost::array<ArrayElementT,N>&);
}
#define sizeofa(array) sizeof(CPPDRG_NS::arrayLengthHelper(array))


// Fill memory with zeroes
inline void zeroMem(const MemArea &area);

// Fill memory with filler byte
inline void fillMem(const MemArea &area, const Byte filler);

// Fill POD-variable with zeroes
template<class Class>
inline void zeroVar(Class &object) ;


// Round up and down to exp2bound (alignment)
// (exp2bound - minimum number of lower zero bits)
Umem roundUp(const Umem value, const Umem exp2bound);
Umem roundDown(const Umem value, const Umem exp2bound);


// Default string representation of different types
String asStr(Umem value);


// Механизм нужен для вечных глобальных объектов, к которым можно
// обращаться в процессе инициализации модуля. Деструкторы для них
// не вызываются.
// Макросом GLOBAL объявляем переменную (обычно в h-файле)
// Макросом GLOBAL_IMPLEMENT_DYNAMIC или GLOBAL_IMPLEMENT_STATIC переменные
// объявляются в cpp-файле.
// GLOBAL_IMPLEMENT_DYNAMIC - объект создаётся при первом обращении
// GLOBAL_IMPLEMENT_STATIC  - объект создаётся или в процессе инициализации
//                            модуля или при первом обращении - что будет раньше
// Предпочтительней первый вариант, второй имеет смысл использовать, если
// конструктор должен исполниться как можно раньше. По скорости без разницы.

#define CPPDRG_GLOBAL(Class, name) \
    namespace CPPDRG_NS { \
        Class& globCreate_##name(); \
        void globDestroy_##name(); \
        extern Class *globPtr_##name; \
    } \
    inline Class& name() { \
        return 0 != CPPDRG_NS::globPtr_##name \
            ? const_cast<Class&>(*CPPDRG_NS::globPtr_##name) \
            : CPPDRG_NS::globCreate_##name(); \
    }

#define CPPDRG_GLOBAL_IMPL_DYNAMIC(Class, name) \
    static Class* globCtr_##name(void *placement); \
    namespace CPPDRG_NS { \
        Class *globPtr_##name = 0; \
        static Byte globStor_##name[sizeof(Class)]; \
        Class& globCreate_##name() \
        { \
            if( 0 == globPtr_##name ) { \
                globPtr_##name = globCtr_##name(globStor_##name); \
            } \
            return const_cast<Class&>(*globPtr_##name); \
        } \
    } \
    static Class* globCtr_##name(void *placement)

#define CPPDRG_GLOBAL_IMPL_STATIC(Class, name) \
    namespace CPPDRG_NS { \
        Class *globStub_##name = &globCreate_##name(); \
    } \
    GLOBAL_IMPLEMENT_DYNAMIC(Class, name)

// Look for first equal value in sorted interval
template<class FwdIt, class Ty>
FwdIt binary_lookup(FwdIt first, FwdIt last, const Ty& val)
{
    FwdIt res = lower_bound(first, last, val);
    if( res != last && (!(*res < val) && !(val < *res)) )
        return res;
    return last;
}

// Look for first equal value in sorted interval with specified
// compare predicate
template<class FwdIt, class Ty, class Pr>
FwdIt binary_lookup(FwdIt first, FwdIt last, const Ty& val, Pr pred)
{
    FwdIt res = lower_bound(first, last, val, pred);
    if( res != last && (!pred(*res, val) && !pred(val, *res)) )
        return res;
    return last;
}
