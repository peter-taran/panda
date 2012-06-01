
#include "../include/cppdragon.h"

#define CPPDRG_DECLARE_ENCODING(name) \
    CPPDRG_GLOBAL(Cvt##name, cvt##name) \
    CPPDRG_GLOBAL_IMPL_DYNAMIC(Cvt##name, cvt##name) { \
        return new(placement) Cvt##name(); \
    } \
    Encoding##name::Encoding##name(): \
        Encoding(&cvt##name()) \
    {}

struct Cvt1251: public CPPDRG_NS::CharCvt
{
};
CPPDRG_DECLARE_ENCODING(1251)
