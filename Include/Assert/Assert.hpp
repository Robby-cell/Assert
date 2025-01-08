#ifndef ASSERT_ASSERT_ASSERT_HPP
#define ASSERT_ASSERT_ASSERT_HPP

#include "Context.hpp" // IWYU pragma: export
#include "Expr.hpp"    // IWYU pragma: export

#include <iostream> // IWYU pragma: export
#include <string>
#include <tuple>

namespace Assert {

#define ASSERT(...)                                                            \
  do {                                                                         \
    auto _Test = ::Assert::Expr<>{} * __VA_ARGS__;                             \
    std::stringstream ss;                                                      \
    ss << _Test;                                                               \
    try {                                                                      \
      ::Assert::ExprValidate(_Test);                                           \
      ::Assert::GetContext().AddPass();                                        \
    } catch (::Assert::AssertionFailure const& e) {                            \
      auto _Section = ::Assert::GetContext().CurrentSection();                 \
      std::cerr << __BASE_FILE__;                                              \
      if (_Section.length()) {                                                 \
        std::cerr << " in section " << _Section;                               \
      }                                                                        \
      std::cerr << " in function " << __PRETTY_FUNCTION__ << ":\n"             \
                << "\t---> Line " << __LINE__ << ": " #__VA_ARGS__ << '\n'     \
                << '\t' << e.what() << '\n';                                   \
      ::Assert::GetContext().AddFail();                                        \
    }                                                                          \
  } while (false)

#define PRECONDITION(...) ASSERT(__VA_ARGS__)
#define POST_CONDITION(...) ASSERT(__VA_ARGS__)
#define REQUIRE(...) ASSERT(__VA_ARGS__)

struct Section {
public:
  explicit Section(std::string section) noexcept {
    GetContext().EnterSection(std::move(section));
  }
  ~Section() { GetContext().PopSection(); }
  template <typename Func> friend auto operator|(const Section& scope, Func f) {
    (void)scope;
    f();
  }

private:
  std::string section_;
};

#define SECTION(SECTION_NAME) ::Assert::Section{SECTION_NAME} | [&]()

struct Nothing {
  constexpr Nothing() = default;
};

#define CAT0(FIRST, SECOND) FIRST%:%:SECOND
#define CAT(FIRST, SECOND) CAT0(FIRST, SECOND)
#define ASSERT_UNIQUE_TEST_NAME(TEST_NAME) CAT(TEST_NAME, __LINE__)
#define TEST_CASE(NAME)                                                        \
  static void ASSERT_UNIQUE_TEST_NAME(INTERNAL_TEST_CASE_)();                  \
  struct CAT(STRUCT, ASSERT_UNIQUE_TEST_NAME(INTERNAL_TEST_STRUCT_)) {         \
    CAT(STRUCT, ASSERT_UNIQUE_TEST_NAME(INTERNAL_TEST_STRUCT_))() {            \
      ::Assert::GetContext().AddTest(NAME);                                    \
      ASSERT_UNIQUE_TEST_NAME(INTERNAL_TEST_CASE_)();                          \
      ::Assert::GetContext().LeaveTest();                                      \
    }                                                                          \
  };                                                                           \
  static CAT(STRUCT, ASSERT_UNIQUE_TEST_NAME(INTERNAL_TEST_STRUCT_))           \
      CAT(VAR, ASSERT_UNIQUE_TEST_NAME(INTERNAL_STATIC_TEST_STRUCT_)) = {};    \
  void ASSERT_UNIQUE_TEST_NAME(INTERNAL_TEST_CASE_)()

} // namespace Assert

#ifndef ASSERT_NO_MAIN
auto main(int argc, char** argv) -> int { // NOLINT
  std::ignore = argc;
  std::ignore = argv;
  ::Assert::GetContext().DisplayInfo();
}
#endif

#endif // ASSERT_ASSERT_ASSERT_HPP
