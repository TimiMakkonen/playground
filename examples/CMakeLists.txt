set(EXAMPLE_SOURCE_LIST playground_examples.cpp)

set(EXAMPLE_APP_NAME "PlaygroundExamples")
add_executable("${EXAMPLE_APP_NAME}" ${EXAMPLE_SOURCE_LIST})

target_link_libraries("${EXAMPLE_APP_NAME}" PRIVATE "${LIBRARY_NAME}")

# The target itself requires at least C++11
target_compile_features("${EXAMPLE_APP_NAME}" PRIVATE cxx_std_11)

# If CLANG_TIDY_EXE found and enabled, use it
if(CLANG_TIDY_EXE AND CLANG_TIDY_EXAMPLES)
  set_target_properties("${EXAMPLE_APP_NAME}" PROPERTIES CXX_CLANG_TIDY
                                                         "${DO_CLANG_TIDY}")
endif()
