# Assert

## A simple package for testing

Add it in CMAKE

```cmake
target_link_libraries(main PRIVATE Assert::Assert)
```

Then use it

```cpp
#include "Assert/AssertMain.hpp"

TEST_CASE("Some test name") {
    SECTION("A section in the test") {
        auto x = 5;
        PRECONDITION(x == 5);
        ++x;
        ASSERT(x == 6);
    };
}

// No main needed. just add your tests.
```
