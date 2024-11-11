cmake_minimum_required(VERSION 3.25)
project(Assert)

add_library(Assert_Assert Core/Assert.cpp Core/Context.cpp)
target_include_directories(Assert_Assert PUBLIC Include)

add_library(Assert::Assert ALIAS Assert_Assert)

if(MSVC)
  target_compile_options(<target> PUBLIC "/ZI")
  target_link_options(<target> PUBLIC "/INCREMENTAL")
endif()

add_executable(Main Source/Main.cpp)
target_link_libraries(Main Assert::Assert)
