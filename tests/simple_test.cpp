#include <catch2/catch_test_macros.hpp>
#include <sstream>


// ============================================================================
// Runtime tests
// ============================================================================

TEST_CASE("Simple test", "[hello]")
{
  REQUIRE(1 == 1);
}