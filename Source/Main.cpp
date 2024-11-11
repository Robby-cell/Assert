#include "Assert/Assert.hpp"
#include "Assert/Context.hpp"

auto main() -> int {
  int x;
  x = 3;
  ASSERT(x == 2);

  SECTION("Foo") {
    x = 42;
    ASSERT(x > 10);
    SECTION("Bar") { ASSERT(x < 20); };
  };
  Assert::GetContext().DisplayInfo();
}
