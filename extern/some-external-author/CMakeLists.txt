
# contents of this file partially copied from https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent

cmake_minimum_required(VERSION 3.1)

project(SomeExternalLibrary LANGUAGES CXX)


add_library(some_external_lib INTERFACE)

target_include_directories(some_external_lib
  INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/some-external-lib/include"
)

target_compile_features(some_external_lib INTERFACE cxx_std_11)