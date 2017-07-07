cmake_minimum_required(VERSION 3.8)
project(cpp-simple-config-parser)
set(CMAKE_BUILD_TYPE Release)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_library(configparser STATIC src/configparser src/utils)
set_property(TARGET configparser PROPERTY CXX_STANDARD 11)

add_executable(demo_configparser src/main.cpp)
target_link_libraries(demo_configparser configparser)
set_property(TARGET demo_configparser PROPERTY CXX_STANDARD 11)

install(TARGETS configparser DESTINATION /usr/lib)
