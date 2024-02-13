cmake_minimum_required(VERSION 3.8)

project(hw-008  VERSION 1.0
                DESCRIPTION "homework-006"
                LANGUAGES CXX)


add_executable(hw-008  src/main.cpp)

target_compile_features(hw-008 PUBLIC cxx_std_17)
                
set_target_properties(hw-008  PROPERTIES
                              CXX_STANDARD_REQUIRED ON
                              RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

target_include_directories(hw-008 PUBLIC library)
                
 if (MSVC)
   target_compile_options(hw-008 PUBLIC /W4 /WX)
 else ()
   target_compile_options(hw-008 PUBLIC 
#                                        -Wall
#                                        -Wextra
#                                        -Werror
#                                        -pedantic
#                                        -g
#                                        -fsanitize=thread
#                                        -fsanitize=address
#                                        -fsanitize=undefined
                                        )

   target_link_options(hw-008 PUBLIC    
#                                        -fsanitize=thread
#                                        -fsanitize=address
#                                        -fsanitize=undefined
                                        )
  endif()