cmake_minimum_required(VERSION 3.8)

project(hw-008  VERSION 1.0
                DESCRIPTION "homework-008"
                LANGUAGES CXX)

find_package(Threads)

add_executable(hw-008  src/main.cpp)

target_compile_features(hw-008 PUBLIC cxx_std_20)
                
set_target_properties(hw-008  PROPERTIES
                              CXX_STANDARD_REQUIRED ON
                              RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

target_compile_options(hw-008 PRIVATE -Wall -Wextra -Werror -pedantic -g -pthread)

target_link_libraries(hw-008 PRIVATE Threads::Threads)