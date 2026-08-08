add_library(learning-vector)

target_sources(learning-vector
  PUBLIC
    FILE_SET CXX_MODULES
    FILES vector.cppm
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
    target_link_libraries(vector-tests PRIVATE learning-vector test-support)

    add_test(NAME vector-tests COMMAND vector-tests)
  else()
    message(STATUS
      "Skipping vector-tests until containers/vector/vectorTests.cpp is populated"
    )
  endif()
endif()
