add_library(learning-vector vector.cpp)

target_include_directories(learning-vector
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(BUILD_TESTING)
  set(VECTOR_TEST_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/vectorTests.cpp")

  # Reconfigure after the initially empty exercise test file is populated.
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    "${VECTOR_TEST_SOURCE}"
  )
  file(SIZE "${VECTOR_TEST_SOURCE}" VECTOR_TEST_SOURCE_SIZE)

  if(VECTOR_TEST_SOURCE_SIZE GREATER 0)
    add_executable(vector-tests vectorTests.cpp)
    target_link_libraries(vector-tests PRIVATE
      learning-vector
      GTest::gtest_main
    )

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
      target_compile_options(vector-tests PRIVATE
        -fsanitize=address
        -fno-omit-frame-pointer
      )
      target_link_options(vector-tests PRIVATE -fsanitize=address)
    endif()

    gtest_discover_tests(vector-tests
      TEST_PREFIX "vector-tests::"
      DISCOVERY_TIMEOUT 30
      PROPERTIES TIMEOUT 30
    )
  else()
    message(STATUS
      "Skipping vector-tests until containers/vector/vectorTests.cpp is populated"
    )
  endif()
endif()
