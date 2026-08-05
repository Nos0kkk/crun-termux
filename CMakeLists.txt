# CMakeLists.txt for build is crun

cmake_minimum_required(VERSION 3.18)
project(crun VERSION 1.1.0 LANGUAGES CXX)

add_executable(crun ${CMAKE_SOURCE_DIR}/src/crun/main.cpp ${CMAKE_SOURCE_DIR}/src/crun/parse.cpp ${CMAKE_SOURCE_DIR}/src/crun/data.cpp)

# install(TARGET crun RUNTIME DESTINATION bin) # for Linux
