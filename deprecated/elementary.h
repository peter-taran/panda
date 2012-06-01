
// All cppdragon objects initializes at default constructor with
// default values
// To leave them uninitialized put 'uninitialized' as parameter
struct Uninitialized {};
static const Uninitialized uninitialized = Uninitialized();


// Umem is 'memory integer': for memory offsets, object counters, indexes,
// raw pointers etc
#ifdef CPPDRAGON_STD_UMEM
    #include <stddef.h>
    typedef size_t Umem;
#else
    typedef boost::uint_t<8*sizeof(void*)>::exact Umem;
#endif


// Raw byte of memory. No arithmetic
typedef unsigned char Byte;
BOOST_STATIC_ASSERT(sizeof(Byte) == 1);




// Smart boolean value
typedef bool Bool;


// Integer with N lower bits set
#define LOWSETBITS(bitN) ((Umem(1) << bitN) - 1)


// Integer with specified bit set
#define BIT0           0x1u
#define BIT1           0x2u
#define BIT2           0x4u
#define BIT3           0x8u
#define BIT4          0x10u
#define BIT5          0x20u
#define BIT6          0x40u
#define BIT7          0x80u
#define BIT8         0x100u
#define BIT9         0x200u
#define BIT10        0x400u
#define BIT11        0x800u
#define BIT12       0x1000u
#define BIT13       0x2000u
#define BIT14       0x4000u
#define BIT15       0x8000u
#define BIT16      0x10000u
#define BIT17      0x20000u
#define BIT18      0x40000u
#define BIT19      0x80000u
#define BIT20     0x100000u
#define BIT21     0x200000u
#define BIT22     0x400000u
#define BIT23     0x800000u
#define BIT24    0x1000000u
#define BIT25    0x2000000u
#define BIT26    0x4000000u
#define BIT27    0x8000000u
#define BIT28   0x10000000u
#define BIT29   0x20000000u
#define BIT30   0x40000000u
#define BIT31   0x80000000u
#define BIT(n)  (Umem(1) << n)


// Size of the POD-structure field
// (you can get size with 'offsetof')
#define sizeoff(struct_name, field) (sizeof(((struct_name*)0)->field))


// Macros, marking function as never returning (like abort, unreachable,
// throwError, etc)
#define noreturn __declspec(noreturn)
