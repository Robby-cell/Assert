#include "Assert/Assert.hpp"
#include "Assert/Context.hpp"
#include "Assert/Fwd.hpp"

#include <tuple>

auto main(int argc, char** argv) -> int { // NOLINT
  std::ignore = argc;
  std::ignore = argv;
  ::Assert::GetContext().DisplayInfo();
}
