#include "Assert/Assert.hpp"
#include "Assert/Context.hpp"

#include <tuple>

static Assert::Context context{};

auto Assert::GetContext() -> Assert::Context& {
    return context;
}

auto main(int argc, char** argv) -> int { // NOLINT
  std::ignore = argc;
  std::ignore = argv;
  context.DisplayInfo();
}
