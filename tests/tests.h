
#pragma once


// This header is common header for any unit test
// It's precompiled, if compiler supports this feature


// configuration
#define PANDACFG_DEFAULT_ENCODING Encoding_ASCII

#include "../panda.h"
#include "../dependencies/include_boost_test.h"



// common test utils


// check uninitialized feature
template<class Object>
void checkUninitialized()
{
    // possible syntaxes
    Object x1 = uninitialized;
    Object x2(uninitialized);

    // check, that memory really untouched
    Membuff<sizeof(Object)> dirty = uninitialized;
    dirty.fill(0xA2);
    new(&dirty) Object(uninitialized);
    for(Memoffs i = 0; i < dirty.size; ++i)
        BOOST_CHECK(dirty.objAt<Byte>(i) == 0xA2);
}
