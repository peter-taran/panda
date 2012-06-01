
#include "../tests.h"

namespace Tests
{

BOOST_AUTO_TEST_CASE(Errors_Error)
{
    // shouldn't compile
    // Error e0;

    AssertionError e1 = Str(null);
    BOOST_CHECK_THROW(e1.throwThis(), AssertionError);
    BOOST_CHECK_THROW(throw e1, AssertionError);

    Error e2 = e1;
    BOOST_CHECK_THROW(e2.throwThis(), AssertionError);
    BOOST_CHECK_THROW(throw e2, Error);

    // TODO: test Error class
}

}