#ifndef ASSERT_HPP_
#define ASSERT_HPP_

#include "Context.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace Assert {

// using AssertionFailure = std::runtime_error;
class AssertionFailure : public std::runtime_error {
public:
  template <typename What>
  explicit AssertionFailure(const What& what) noexcept
      : std::runtime_error(what) {}
};

struct Add;
struct Sub;
struct Mul;
struct Div;
struct Eq;
struct NotEq;
struct Greater;
struct Less;
struct GreaterEq;
struct LessEq;

template <class...> struct Expr;

template <typename... Ts, typename Type>
auto operator==(Expr<Ts...>&& expr, const Type& value) {
  return Expr<Expr<Ts...>, Type, Eq>{expr, value};
}
template <typename... Ts, typename Type>
auto operator!=(Expr<Ts...>&& expr, const Type& value) {
  return Expr<Expr<Ts...>, Type, NotEq>{expr, value};
}
template <typename... Ts, typename Type>
auto operator+(Expr<Ts...>&& expr, const Type& value) {
  return Expr<Expr<Ts...>, Type, Add>{expr, value};
}
template <typename... Ts, typename Type>
auto operator-(Expr<Ts...>&& expr, const Type& value) {
  return Expr<Expr<Ts...>, Type, Sub>{expr, value};
}
template <typename... Ts, typename Type>
auto operator*(Expr<Ts...>&& expr, const Type& value) {
  return Expr<Expr<Ts...>, Type, Mul>{expr, value};
}
template <typename... Ts, typename Type>
auto operator/(Expr<Ts...>&& expr, const Type& value) {
  return Expr<Expr<Ts...>, Type, Div>{expr, value};
}
template <typename... Ts, typename Type>
auto operator>(Expr<Ts...>&& expr, const Type& value) {
  return Expr<Expr<Ts...>, Type, Greater>{expr, value};
}
template <typename... Ts, typename Type>
auto operator<(Expr<Ts...>&& expr, const Type& value) {
  return Expr<Expr<Ts...>, Type, Less>{expr, value};
}
template <typename... Ts, typename Type>
auto operator>=(Expr<Ts...>&& expr, const Type& value) {
  return Expr<Expr<Ts...>, Type, GreaterEq>{expr, value};
}
template <typename... Ts, typename Type>
auto operator<=(Expr<Ts...>&& expr, const Type& value) {
  return Expr<Expr<Ts...>, Type, LessEq>{expr, value};
}

template <typename Type> auto ExprEval(const Type& value) -> const Type& {
  return value;
}
template <typename... Ts>
auto ExprEval(const Expr<Ts...>& expr) -> decltype(expr.Eval()) {
  return expr.Eval();
}
template <typename Type> auto ExprValidate(const Type& value) noexcept {}
template <typename... Ts> auto ExprValidate(const Expr<Ts...>& expr) {
  return expr.Validate();
}

template <> struct Expr<> {
  template <typename Type>
  friend auto operator*(const Expr& self, const Type& value) -> Expr<Type> {
    (void)self;
    return Expr<Type>{value};
  }
  auto Validate() const noexcept {}
  auto Eval() const noexcept { return true; }
};
template <typename Type> auto operator*(Expr<>&& expr, const Type& value) {
  (void)expr;
  return Expr<Type>{value};
}

template <typename Type> struct Expr<Type> {
public:
  explicit Expr(const Type& value) : value_(value) {}

  auto Validate() const noexcept {}

  auto Eval() const noexcept -> const Type& { return ExprEval(value_); }

  friend auto operator<<(std::ostream& os, const Expr& expr) -> std::ostream& {
    return os << expr.value_;
  }

private:
  Type value_;
};

template <typename Type, typename Other> struct Expr<Type, Other, Eq> {
public:
  Expr(const Type& value, const Other& other) noexcept
      : value_(value), other_(other) {}

  auto Validate() const {
    if (!Eval()) {
      std::stringstream ss;
      ss << "Assertion Failure: Expected " << *this;
      throw AssertionFailure(ss.str());
    }
  }

  auto Eval() const noexcept -> bool { return ExprEval(value_) == other_; }

  friend auto operator<<(std::ostream& os, const Expr& expr) -> std::ostream& {
    return os << ExprEval(expr.value_) << " == " << ExprEval(expr.other_);
  }

private:
  Type value_;
  Other other_;
};

template <typename Type, typename Other> struct Expr<Type, Other, NotEq> {
public:
  Expr(const Type& value, const Other& other) noexcept
      : value_(value), other_(other) {}

  auto Validate() const {
    if (!Eval()) {
      std::stringstream ss;
      ss << "Assertion Failure: Expected " << *this;
      throw AssertionFailure(ss.str());
    }
  }

  auto Eval() const noexcept -> bool { return ExprEval(value_) != other_; }

  friend auto operator<<(std::ostream& os, const Expr& expr) -> std::ostream& {
    return os << ExprEval(expr.value_) << " != " << ExprEval(expr.other_);
  }

private:
  Type value_;
  Other other_;
};
template <typename Type, typename Other> struct Expr<Type, Other, Greater> {
public:
  Expr(const Type& value, const Other& other) noexcept
      : value_(value), other_(other) {}

  auto Validate() const {
    if (!Eval()) {
      std::stringstream ss;
      ss << "Assertion Failure: Expected " << *this;
      throw AssertionFailure(ss.str());
    }
  }

  auto Eval() const noexcept -> bool { return ExprEval(value_) > other_; }

  friend auto operator<<(std::ostream& os, const Expr& expr) -> std::ostream& {
    return os << expr.value_ << " > " << expr.other_;
  }

private:
  Type value_;
  Other other_;
};
template <typename Type, typename Other> struct Expr<Type, Other, Less> {
public:
  Expr(const Type& value, const Other& other) noexcept
      : value_(value), other_(other) {}

  auto Validate() const {
    if (!Eval()) {
      std::stringstream ss;
      ss << "Assertion Failure: Expected " << *this;
      throw AssertionFailure(ss.str());
    }
  }

  auto Eval() const noexcept -> bool { return ExprEval(value_) < other_; }

  friend auto operator<<(std::ostream& os, const Expr& expr) -> std::ostream& {
    return os << expr.value_ << " < " << expr.other_;
  }

private:
  Type value_;
  Other other_;
};
template <typename Type, typename Other> struct Expr<Type, Other, GreaterEq> {
public:
  Expr(const Type& value, const Other& other) noexcept
      : value_(value), other_(other) {}

  auto Validate() const {
    if (!Eval()) {
      std::stringstream ss;
      ss << "Assertion Failure: Expected " << *this;
      throw AssertionFailure(ss.str());
    }
  }

  auto Eval() const noexcept -> bool { return ExprEval(value_) >= other_; }

  friend auto operator<<(std::ostream& os, const Expr& expr) -> std::ostream& {
    return os << expr.value_ << " >= " << expr.other_;
  }

private:
  Type value_;
  Other other_;
};
template <typename Type, typename Other> struct Expr<Type, Other, LessEq> {
public:
  Expr(const Type& value, const Other& other) noexcept
      : value_(value), other_(other) {}

  auto Validate() const {
    if (!Eval()) {
      std::stringstream ss;
      ss << "Assertion Failure: Expected " << *this;
      throw AssertionFailure(ss.str());
    }
  }

  auto Eval() const noexcept -> bool { return ExprEval(value_) <= other_; }

  friend auto operator<<(std::ostream& os, const Expr& expr) -> std::ostream& {
    return os << expr.value_ << " <= " << expr.other_;
  }

private:
  Type value_;
  Other other_;
};

template <typename Type, typename Other> struct Expr<Type, Other, Add> {
public:
  Expr(const Type& value, const Other& other) noexcept
      : value_(value), other_(other) {}

  auto Validate() const noexcept {}

  auto Eval() const noexcept { return ExprEval(value_) + other_; }

  friend auto operator<<(std::ostream& os, const Expr& expr) -> std::ostream& {
    return os << expr.value_ << " + " << expr.other_;
  }

private:
  Type value_;
  Other other_;
};
template <typename Type, typename Other> struct Expr<Type, Other, Sub> {
public:
  Expr(const Type& value, const Other& other) noexcept
      : value_(value), other_(other) {}

  auto Validate() const noexcept {}

  auto Eval() const noexcept { return ExprEval(value_) - other_; }

  friend auto operator<<(std::ostream& os, const Expr& expr) -> std::ostream& {
    return os << expr.value_ << " - " << expr.other_;
  }

private:
  Type value_;
  Other other_;
};
template <typename Type, typename Other> struct Expr<Type, Other, Mul> {
public:
  Expr(const Type& value, const Other& other) noexcept
      : value_(value), other_(other) {}

  auto Validate() const noexcept {}

  auto Eval() const noexcept { return ExprEval(value_) * other_; }

  friend auto operator<<(std::ostream& os, const Expr& expr) -> std::ostream& {
    return os << expr.value_ << " * " << expr.other_;
  }

private:
  Type value_;
  Other other_;
};
template <typename Type, typename Other> struct Expr<Type, Other, Div> {
public:
  Expr(const Type& value, const Other& other) noexcept
      : value_(value), other_(other) {}

  auto Validate() const noexcept {}

  auto Eval() const noexcept { return ExprEval(value_) / other_; }

  friend auto operator<<(std::ostream& os, const Expr& expr) -> std::ostream& {
    return os << expr.value_ << " / " << expr.other_;
  }

private:
  Type value_;
  Other other_;
};

#define ASSERT(...)                                                            \
  do {                                                                         \
    auto _Test = ::Assert::Expr<>{} * __VA_ARGS__;                             \
    std::stringstream ss;                                                      \
    ss << _Test;                                                               \
    try {                                                                      \
      ::Assert::ExprValidate(_Test);                                           \
      ::Assert::GetContext().AddPass(ss.str());                                \
    } catch (::Assert::AssertionFailure const& e) {                            \
      std::cerr << __FILE__ << " at line " << __LINE__ << " in function "      \
                << __PRETTY_FUNCTION__ << ":\n"                                \
                << e.what() << '\n';                                           \
      ::Assert::GetContext().AddFail(ss.str());                                \
    }                                                                          \
  } while (false)

#define PRECONDITION(...) ASSERT(__VA_ARGS__)
#define POST_CONDITION(...) ASSERT(__VA_ARGS__)
#define REQUIRE(...) ASSERT(__VA_ARGS__)
} // namespace Assert

#endif // ASSERT_HPP_
