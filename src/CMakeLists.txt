# Note that headers are optional, and do not affect add_library, but they will
# not show up in IDEs unless they are listed in add_library.

# Header files
set(HEADER_FOLDER "${PROJECT_SOURCE_DIR}/include/playground")
set(HEADER_LIST "${HEADER_FOLDER}/seesaw.h")

# Source files
set(SOURCE_FOLDER "playground")
set(SOURCE_LIST "${SOURCE_FOLDER}/seesaw.cpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library("${LIBRARY_NAME}" ${HEADER_LIST} ${SOURCE_LIST})

# We need this directory, and users of our library will need it too
target_include_directories("${LIBRARY_NAME}"
                           PUBLIC "${PROJECT_SOURCE_DIR}/include")

# We need this directory
target_include_directories("${LIBRARY_NAME}"
                           PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# We need this external library
target_link_libraries("${LIBRARY_NAME}" PRIVATE some_external_lib)

# All users of this library will need at least C++11
target_compile_features("${LIBRARY_NAME}" INTERFACE cxx_std_11)

# The target itself requires at least C++11
target_compile_features("${LIBRARY_NAME}" PRIVATE cxx_std_11)

# If CLANG_TIDY_EXE found and enabled, use it
if(CLANG_TIDY_EXE AND PLAYGROUND_CLANG_TIDY)
  set_target_properties("${LIBRARY_NAME}" PROPERTIES CXX_CLANG_TIDY
                                                     "${DO_CLANG_TIDY}")
endif()

# IDEs should put the headers in a nice place (This might not work as intended)
# ~~~
# source_group(
#  TREE "${PROJECT_SOURCE_DIR}/include"
#  PREFIX "Header Files"
#  FILES ${HEADER_LIST})
# ~~~
