add_library(Assert_Assert STATIC Assert.cpp Context.cpp)
target_include_directories(Assert_Assert PUBLIC Include)

add_library(Assert::Assert ALIAS Assert_Assert)

add_library(Assert_Main STATIC AssertMain.cpp)
target_link_libraries(Assert_Main PUBLIC Assert_Assert)

add_library(Assert::Main ALIAS Assert_Main)
