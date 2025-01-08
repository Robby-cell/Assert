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
    auto v = Assert::Expr<>{} * 3 < 1;
    std::cout << v;
    std::cout << '\n' << v.Eval();
    try {
      v.Validate();
    } catch (...) {
      std::cout << "\nInvalid\n";
    }
    ASSERT(3 < 1);
    ASSERT(10 == 3);
  };
}

TEST_CASE("No asserts") {}
