cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
project(game)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works

enable_testing()

add_subdirectory(Asta)
add_subdirectory(Sandbox)
add_subdirectory(Tests)
