cmake_minimum_required(VERSION 3.8)
project(cpp-simple-config-parser)
set(CMAKE_BUILD_TYPE Release)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_library(simple_config_parser_utils SHARED src/utils)
set_property(TARGET simple_config_parser_utils PROPERTY CXX_STANDARD 11)

add_library(simple_config_parser_parser SHARED src/parser)
set_property(TARGET simple_config_parser_parser PROPERTY CXX_STANDARD 11)
target_link_libraries(simple_config_parser_parser simple_config_parser_utils)

add_executable(demo_configparser src/main.cpp)
target_link_libraries(demo_configparser simple_config_parser_parser)
set_property(TARGET demo_configparser PROPERTY CXX_STANDARD 11)

# install(TARGETS configparser DESTINATION /usr/lib)
