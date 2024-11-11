#ifndef ASSERT_CORE_TESTRESULT_HPP
#define ASSERT_CORE_TESTRESULT_HPP

#include <string>

namespace Assert {
class TestResult {
public:
  explicit TestResult(std::string stringification)
      : stringification_(std::move(stringification)) {}

  constexpr auto GetStringification() const noexcept -> const std::string& {
    return stringification_;
  }

private:
  std::string stringification_;
};
} // namespace Assert

#endif // ASSERT_CORE_TESTRESULT_HPP
