cmake_minimum_required(VERSION 3.28)

project(LeetCodeSolutions LANGUAGES CXX)

include(CTest)

if(BUILD_TESTING)
  include(FetchContent)

  set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
  set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Better warnings
if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(BUILD_TESTING)
  file(GLOB PROBLEM_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/problems/*.cpp"
  )

  foreach(PROBLEM ${PROBLEM_SOURCES})
    get_filename_component(PROBLEM_NAME ${PROBLEM} NAME_WE)

    add_executable(${PROBLEM_NAME} ${PROBLEM})
    target_include_directories(${PROBLEM_NAME} PRIVATE
      ${CMAKE_SOURCE_DIR}/problems
    )
    target_link_libraries(${PROBLEM_NAME} PRIVATE
      GTest::gtest_main
    )

    gtest_discover_tests(${PROBLEM_NAME}
      TEST_PREFIX "${PROBLEM_NAME}::"
      DISCOVERY_TIMEOUT 30
      PROPERTIES TIMEOUT 30
    )
  endforeach()
endif()

add_subdirectory(containers/vector)
