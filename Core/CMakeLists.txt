add_library(Assert_Assert Assert.cpp Context.cpp AssertMain.cpp)
target_include_directories(Assert_Assert PUBLIC Include)

add_library(Assert::Assert ALIAS Assert_Assert)
