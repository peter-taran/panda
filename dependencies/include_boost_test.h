
#pragma once

// disable boost warnings, we trust boost
// TODO: it doesn't work for some reason
#pragma warning(push, 1)



#ifdef PANDACFG_BOOST_UTF_INCLUDE_IMPLEMENTATION
    #include "boost/test/included/unit_test.hpp"
#else
    #define BOOST_TEST_NO_LIB
    #include "boost/test/unit_test.hpp"
#endif



#pragma warning(pop)
