#ifndef ASSERT_ASSERT_EXPR_HPP
#define ASSERT_ASSERT_EXPR_HPP

#include "Fwd.hpp"

#include <ostream>
#include <sstream>
#include <utility>

namespace Assert {
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

  auto Validate() const;

  auto Eval() const noexcept -> const Type& { return ExprEval(value_); }

  friend auto operator<<(std::ostream& os, const Expr& expr) -> std::ostream& {
    return os << expr.value_;
  }

private:
  Type value_;
};

template <typename Type> inline auto Expr<Type>::Validate() const {}
template <> inline auto Expr<bool>::Validate() const {
  if (!value_) {
    std::stringstream ss;
    ss << "Assertion Failure: Expected " << (*this);
    throw AssertionFailure(ss.str());
  }
}

namespace Detail {
template <typename> constexpr auto GetSymbol();
template <> constexpr auto GetSymbol<Eq>() { return "=="; }
template <> constexpr auto GetSymbol<NotEq>() { return "!="; }
template <> constexpr auto GetSymbol<Greater>() { return ">"; }
template <> constexpr auto GetSymbol<Less>() { return "<"; }
template <> constexpr auto GetSymbol<GreaterEq>() { return ">="; }
template <> constexpr auto GetSymbol<LessEq>() { return "<="; }
template <> constexpr auto GetSymbol<Add>() { return "+"; }
template <> constexpr auto GetSymbol<Sub>() { return "-"; }
template <> constexpr auto GetSymbol<Mul>() { return "*"; }
template <> constexpr auto GetSymbol<Div>() { return "/"; }

template <typename Op, typename Lhs, typename Rhs> struct ExprEvaluateHelper;

template <typename Lhs, typename Rhs> struct ExprEvaluateHelper<Eq, Lhs, Rhs> {
  static constexpr auto Evaluate(Lhs&& lhs, Rhs&& rhs) -> decltype(auto) {
    return ExprEval(lhs) == ExprEval(rhs);
  }
};
template <typename Lhs, typename Rhs>
struct ExprEvaluateHelper<NotEq, Lhs, Rhs> {
  static constexpr auto Evaluate(Lhs&& lhs, Rhs&& rhs) -> decltype(auto) {
    return ExprEval(lhs) != ExprEval(rhs);
  }
};
template <typename Lhs, typename Rhs>
struct ExprEvaluateHelper<Greater, Lhs, Rhs> {
  static constexpr auto Evaluate(Lhs&& lhs, Rhs&& rhs) -> decltype(auto) {
    return ExprEval(lhs) > ExprEval(rhs);
  }
};
template <typename Lhs, typename Rhs>
struct ExprEvaluateHelper<Less, Lhs, Rhs> {
  static constexpr auto Evaluate(Lhs&& lhs, Rhs&& rhs) -> decltype(auto) {
    return ExprEval(lhs) < ExprEval(rhs);
  }
};
template <typename Lhs, typename Rhs>
struct ExprEvaluateHelper<GreaterEq, Lhs, Rhs> {
  static constexpr auto Evaluate(Lhs&& lhs, Rhs&& rhs) -> decltype(auto) {
    return ExprEval(lhs) >= ExprEval(rhs);
  }
};
template <typename Lhs, typename Rhs>
struct ExprEvaluateHelper<LessEq, Lhs, Rhs> {
  static constexpr auto Evaluate(Lhs&& lhs, Rhs&& rhs) -> decltype(auto) {
    return ExprEval(lhs) <= ExprEval(rhs);
  }
};
template <typename Lhs, typename Rhs> struct ExprEvaluateHelper<Add, Lhs, Rhs> {
  static constexpr auto Evaluate(Lhs&& lhs, Rhs&& rhs) -> decltype(auto) {
    return ExprEval(lhs) + ExprEval(rhs);
  }
};
template <typename Lhs, typename Rhs> struct ExprEvaluateHelper<Sub, Lhs, Rhs> {
  static constexpr auto Evaluate(Lhs&& lhs, Rhs&& rhs) -> decltype(auto) {
    return ExprEval(lhs) - ExprEval(rhs);
  }
};
template <typename Lhs, typename Rhs> struct ExprEvaluateHelper<Mul, Lhs, Rhs> {
  static constexpr auto Evaluate(Lhs&& lhs, Rhs&& rhs) -> decltype(auto) {
    return ExprEval(lhs) * ExprEval(rhs);
  }
};
template <typename Lhs, typename Rhs> struct ExprEvaluateHelper<Div, Lhs, Rhs> {
  static constexpr auto Evaluate(Lhs&& lhs, Rhs&& rhs) -> decltype(auto) {
    return ExprEval(lhs) / ExprEval(rhs);
  }
};

template <typename Op, typename Lhs, typename Rhs>
constexpr auto ExprPerformOp(Lhs&& lhs, Rhs&& rhs) {
  return ExprEvaluateHelper<Op, Lhs, Rhs>::Evaluate(std::forward<Lhs>(lhs),
                                                    std::forward<Rhs>(rhs));
}
} // namespace Detail

template <typename Type, typename Other, typename Op>
struct Expr<Type, Other, Op> {
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

  auto Eval() const noexcept -> bool {
    return Detail::ExprPerformOp<Op>(value_, other_);
  }

  friend auto operator<<(std::ostream& os, const Expr& expr) -> std::ostream& {
    return os << ExprEval(expr.value_) << ' ' << Detail::GetSymbol<Op>() << ' '
              << ExprEval(expr.other_);
  }

private:
  Type value_;
  Other other_;
};
} // namespace Assert

#endif // ASSERT_ASSERT_EXPR_HPP
