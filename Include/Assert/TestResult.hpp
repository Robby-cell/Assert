#ifndef ASSERT_CORE_TESTRESULT_HPP
#define ASSERT_CORE_TESTRESULT_HPP

#include <cstdint>
#include <string>

namespace Assert {
class TestResult {
public:
  explicit TestResult(std::string test_name) noexcept
      : test_name_(std::move(test_name)) {}

  constexpr auto Pass() noexcept { ++passed_; }
  constexpr auto Fail() noexcept { ++failed_; }

  constexpr auto Passed() const noexcept { return passed_; }
  constexpr auto Failed() const noexcept { return failed_; }
  constexpr auto TestCount() const noexcept { return passed_ + failed_; }
  constexpr auto Name() const -> std::string const& { return test_name_; }

private:
  std::string test_name_;
  std::uint32_t passed_ = 0;
  std::uint32_t failed_ = 0;
};
} // namespace Assert

#endif // ASSERT_CORE_TESTRESULT_HPP
