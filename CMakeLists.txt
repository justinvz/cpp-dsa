cmake_minimum_required(VERSION 3.16)

project(LeetCodeSolutions)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Better warnings
if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Automatically find all cpp files inside problems/
file(GLOB PROBLEM_SOURCES
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
