cmake_minimum_required(VERSION 3.30.0)

project(OK)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(/user/include)

add_executable(OK src/main.cpp)

target_link_libraries(OK PRIVATE boost_system boost_filesystem)