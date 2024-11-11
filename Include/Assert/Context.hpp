#ifndef ASSERT_ASSERT_CONTEXT_HPP
#define ASSERT_ASSERT_CONTEXT_HPP

#include "TestResult.hpp"

#include <string>
#include <utility>
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

  template <typename... Args> auto AddPass(Args&&... args) {
    passed_.emplace_back(std::forward<Args>(args)...);
  }

  template <typename... Args> auto AddFail(Args&&... args) {
    failed_.emplace_back(std::forward<Args>(args)...);
  }

private:
  Context() = default;
  friend auto GetContext() noexcept -> Context&;

  std::vector<std::string> section_;
  std::vector<TestResult> passed_;
  std::vector<TestResult> failed_;
};

} // namespace Assert

#endif // ASSERT_ASSERT_CONTEXT_HPP
