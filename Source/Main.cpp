#include "Assert/Assert.hpp"

TEST_CASE("Foo bar") {
  ASSERT(2 > 3);
  ASSERT(false);
}

TEST_CASE("Some test") {
  SECTION("test2 (section)") { ASSERT(true); };
  ASSERT(true);
}

TEST_CASE("Another test case") {
  SECTION("Another section") {
    ASSERT(3 < 1);
    ASSERT(10 == 3);
  };
}

TEST_CASE("No asserts") {}
