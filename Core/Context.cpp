#include "Assert/Context.hpp"

#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

namespace Assert {

auto Context::DisplayInfo() const -> void {
  std::size_t test_pass = 0;
  std::size_t passed = 0;
  std::size_t failed = 0;

  for (std::size_t i = 0; i < tests_.size(); ++i) {
    const auto& test = tests_.at(i);
    std::cerr << test.Name() << ": " << test.Passed() << ", " << test.Failed()
              << '\n';
    if (!test.Failed()) {
      ++test_pass;
    }
    passed += test.Passed();
    failed += test.Failed();

    if (test.Failed()) {
      std::cerr << "\tTest case " << i << ":\n\t\t" << test.Passed()
                << " passed\n\t\t" << test.Failed() << " failed\n";
    }
  }

  if (test_pass == tests_.size()) {
    std::cerr << "All " << tests_.size() << " tests passed\n\t" << passed
              << " Assertions\n";

  } else {
    auto test_fail = tests_.size() - test_pass;
    std::cerr << "Passed " << test_pass << " tests and failed " << test_fail
              << '\n';
  }
  std::cerr << '\t' << passed << " assertions passed\n\t" << failed
            << " assertions failed\n";

  std::cerr << '\n';

  if (global_assertions_.Failed()) {
    std::cerr << "Global assertions:\n\t" << global_assertions_.Passed()
              << " passed\n\t" << global_assertions_.Failed() << " failed\n";
  } else if (global_assertions_.Passed()) {
    std::cerr << "All " << global_assertions_.Passed()
              << " global assertions passed\n";
  }
}

auto Context::EnterSection(std::string section) -> void {
  section_.emplace_back(std::move(section));
}

auto Context::PopSection() -> void { section_.pop_back(); }

auto Context::CurrentSection() const -> std::string {
  std::stringstream ss;
  auto idx{section_.size()};
  for (const auto& subsection : section_) {
    ss << subsection;
    if (--idx) {
      ss << "::";
    }
  }
  return ss.str();
}

auto Context::AddTest(const char* test_name) -> void {
 tests_.emplace_back(test_name);
 current_test_ = tests_.size() - 1;
}

auto Context::LeaveTest() -> void {
 if (current_test_ == 0) {
   current_test_ = NotInTest;
 } else {
   --current_test_;
 }
}

} // namespace Assert
