cmake_minimum_required(VERSION 3.31)

# CMake still gates standard-library modules as experimental, including in 4.0.
# This must be enabled before CMake discovers the C++ toolchain.
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
  "0e5b6991-d74f-4b3d-a41c-cf096e0b2508"
)
set(CMAKE_CXX_MODULE_STD ON)

project(LeetCodeSolutions LANGUAGES CXX)

include(CTest)

if(BUILD_TESTING)
  add_library(test-support INTERFACE)
  target_include_directories(test-support INTERFACE
    ${CMAKE_SOURCE_DIR}/test
  )
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# CMake 3.31's libc++ standard module is currently built in gnu++23 mode.
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Better warnings
if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Automatically find all cpp files inside problems/
file(GLOB PROBLEM_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_SOURCE_DIR}/problems/*.cpp"
)

# Create one executable per problem
foreach(PROBLEM ${PROBLEM_SOURCES})
  get_filename_component(PROBLEM_NAME ${PROBLEM} NAME_WE)

  add_executable(${PROBLEM_NAME} ${PROBLEM})

  target_include_directories(${PROBLEM_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/problems
    ${CMAKE_SOURCE_DIR}/test
  )
endforeach()

add_subdirectory(containers/vector)
