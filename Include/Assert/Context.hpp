#ifndef ASSERT_ASSERT_CONTEXT_HPP
#define ASSERT_ASSERT_CONTEXT_HPP

#include "Assert/TestResult.hpp"
#include "TestResult.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace Assert {

class Context;

auto GetContext() noexcept -> Context&;

class Context {
public:
  auto DisplayInfo() const -> void;
  auto EnterSection(std::string section) -> void;
  auto PopSection() -> void;
  auto CurrentSection() const -> std::string;

  constexpr auto AddTest() -> decltype(auto) {
    tests_.emplace_back();
    current_test_ = tests_.size() - 1;
  }
  constexpr auto LeaveTest() { current_test_ = NotInTest; }

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

private:
  Context() = default;
  friend auto GetContext() noexcept -> Context&;

  static constexpr std::uint32_t NotInTest = -1;

  std::vector<std::string> section_;
  std::vector<TestResult> tests_;
  TestResult global_assertions_;
  std::uint32_t current_test_ = NotInTest;
};

} // namespace Assert

#endif // ASSERT_ASSERT_CONTEXT_HPP
