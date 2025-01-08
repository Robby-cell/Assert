#ifndef ASSERT_ASSERT_FWD_HPP
#define ASSERT_ASSERT_FWD_HPP

#include <stdexcept>

namespace Assert {
class AssertionFailure : public std::runtime_error {
public:
  template <typename What>
  explicit AssertionFailure(const What& what) noexcept
      : std::runtime_error(what) {}
};
} // namespace Assert

#endif // ASSERT_ASSERT_FWD_HPP
