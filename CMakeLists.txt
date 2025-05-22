cmake_minimum_required(VERSION 3.10)
project(Simple256)
enable_testing()


# Main
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")
add_library(simple256 ${SRC_FILES})

#add_executable(simple256 ${SRC_FILES})


# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)


# Tests
add_subdirectory(tests)




