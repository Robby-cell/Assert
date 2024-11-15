#include "Assert/Assert.hpp"
#include "Assert/Context.hpp"

TEST_CASE("Foo bar") {
  ASSERT(2 > 3);
  ASSERT(false);
}
TEST_CASE("Some test") {
  SECTION("test2 (section)") { ASSERT(true); };
  ASSERT(false);
}

auto main() -> int {
  int x;
  x = 3;
  ASSERT(x == 2);

  SECTION("Foo") {
    x = 42;
    ASSERT(x > 10);
    SECTION("Bar") { ASSERT(x < 20); };
  };
  // VARINTERNAL_STATIC_TEST_STRUCT_4 = {};
  Assert::GetContext().DisplayInfo();
}
