cmake_minimum_required(VERSION 3.8)

project(
  Playground
  VERSION 8.5.2
  # DESCRIPTION "Playground library"
  LANGUAGES CXX)

set(LIBRARY_NAME "libplayground")

# Options:
option(PLAYGROUND_BUILD_SHARED_LIBS
       "Build shared libraries instead of static ones" OFF)
option(PLAYGROUND_FORCE_COLORED_OUTPUT
       "Always produce ANSI-colored output (GNU/Clang only)." OFF)
option(PLAYGROUND_CLANG_TIDY "Use 'clang-tidy' on project source files." OFF)
option(PLAYGROUND_CLANG_TIDY_EXAMPLES "Use 'clang-tidy' on examples files." OFF)

if(PLAYGROUND_BUILD_SHARED_LIBS)
  set(BUILD_SHARED_LIBS ON)
endif()

# Setting up clang-tidy if it is installed and enabled
if(PLAYGROUND_CLANG_TIDY OR PLAYGROUND_CLANG_TIDY_EXAMPLES)
  find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable")

  if(NOT CLANG_TIDY_EXE)
    message(FATAL_ERROR "clang-tidy not found.")
  else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    # Allows to set clang-tidy for specific targets
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}")
  endif()
endif()

# Only do these if this is the main project, and not if it is included through
# add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Set global c++ standard
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  # Use -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDE's
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # https://medium.com/@alasher/colored-c-compiler-output-with-ninja-clang-gcc-10bfe7f2b949
  if(${FORCE_COLORED_OUTPUT})
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
      add_compile_options(-fdiagnostics-color=always)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
      add_compile_options(-fcolor-diagnostics)
    endif()
  endif()

  # Testing only available if this is the main app. Note this needs to be done
  # in the main CMakeLists since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)

  # ############################################################################
  # Needed to download Google test
  # ############################################################################

  # Download and unpack googletest at configure time
  configure_file(google_CMakeLists.txt.in googletest-download/CMakeLists.txt)
  execute_process(
    COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
  if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
  endif()
  execute_process(
    COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
  if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
  endif()

  # Prevent overriding the parent project's compiler/linker settings on Windows
  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE)

  # Add googletest directly to our build. This defines the gtest and gtest_main
  # targets.
  add_subdirectory(
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-src
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-build EXCLUDE_FROM_ALL)

  # The gtest/gtest_main targets carry header search path dependencies
  # automatically when using CMake 2.8.11 or later. Otherwise we have to add
  # them here ourselves.
  if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
  endif()

  # Now simply link against gtest or gtest_main as needed. Eg.
  # ~~~
  # add_executable(example example.cpp)
  # target_link_libraries(example gtest_main)
  # add_test(NAME example_test COMMAND example)
  # ~~~

  # ############################################################################
  # End of Google Test stuff
  # ############################################################################

endif()

# The compiled library code is here
add_subdirectory(src)

# Testing only available if this is the main app. Emergency override
# PLAYGROUND_LIB_BUILD_TESTING provided. Use set(PLAYGROUND_LIB_BUILD_TESTING
# ON) in parent folder to enable testing in this project.
if(((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) OR PLAYGROUND_LIB_BUILD_TESTING)
   AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

# The examples executable code is here. Only available if this is the main app.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  add_subdirectory(examples)
endif()
