cmake_minimum_required(VERSION 3.14)
project(POSTRACI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(POSTRACI main.cpp)
target_include_directories(POSTRACI PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(POSTRACI PRIVATE Boost::program_options pthread)
