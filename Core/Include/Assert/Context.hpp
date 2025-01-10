#ifndef ASSERT_ASSERT_CONTEXT_HPP
#define ASSERT_ASSERT_CONTEXT_HPP

#include "TestResult.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace Assert {

class Context {
public:
  auto DisplayInfo() const -> void;
  auto EnterSection(std::string section) -> void;
  auto PopSection() -> void;
  auto CurrentSection() const -> std::string;

  auto AddTest(const char* test_name) -> void ;
  auto LeaveTest() -> void;

  constexpr auto AddPass() noexcept {
    if (current_test_ != NotInTest) {
      tests_.at(current_test_).Pass();
    } else {
      global_assertions_.Pass();
    }
  }
  constexpr auto AddFail() noexcept {
    if (current_test_ != NotInTest) {
      tests_.at(current_test_).Fail();
    } else {
      global_assertions_.Fail();
    }
  }

  Context() = default;
private:

  static constexpr std::uint32_t NotInTest = -1;

  std::vector<std::string> section_;
  std::vector<TestResult> tests_;
  TestResult global_assertions_{"Anonymous"};
  std::uint32_t current_test_ = NotInTest;
};

} // namespace Assert

#endif // ASSERT_ASSERT_CONTEXT_HPP
