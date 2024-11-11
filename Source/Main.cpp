#include "Assert/Assert.hpp"
#include "Assert/Context.hpp"

auto main() -> int {
  ASSERT(2 == 3);
  Assert::GetContext().DisplayInfo();
}
