#ifdef RUN_TEST

#ifdef SELF_TEST
#include "catch.hpp"

TEST_CASE( "Check if catch library is working", "[catch_library]" ) {
    REQUIRE( 1 == 1 );
    REQUIRE( true == 1 );
    REQUIRE( Approx(12.456) == 12.456 );
}
#endif

#endif
