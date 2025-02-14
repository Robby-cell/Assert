#include "Assert/Assert.hpp"
TEST_CASE("Integer Addition Test") {
  int a = 5;
  int b = 10;
  ASSERT(a + b == 15); // Assertion that should pass
  ASSERT(a + b != 20); // Another assertion that should pass
  ASSERT(a * b == 50); // Assertion that should pass
  ASSERT(a - b > 0);   // Assertion that should FAIL
}
