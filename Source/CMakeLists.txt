add_executable(Main Main.cpp)
target_link_libraries(Main PRIVATE Assert::Main)

if(MSVC)
  target_compile_options(Main PUBLIC "/ZI")
  target_link_options(Main PUBLIC "/INCREMENTAL")
endif()
