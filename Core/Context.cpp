#include "Assert/Context.hpp"

#include <iostream>
#include <sstream>
#include <string>

namespace Assert {

auto Context::DisplayInfo() const -> void {
  if (failed_.empty()) {
    std::cout << "All " << passed_.size() << " tests passed\n";
  } else {
    std::cout << passed_.size() << " tests passed\n"
              << failed_.size() << " tests failed\n";
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

auto GetContext() noexcept -> Context& {
  static Context context;
  return context;
}

} // namespace Assert
