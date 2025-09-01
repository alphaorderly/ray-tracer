cmake_minimum_required(VERSION 3.10)
project(raytracer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)

add_executable(raytracer src/cli/raytrace_cli.cpp)
target_link_libraries(raytracer PRIVATE raycore)
target_link_libraries(raytracer PRIVATE image)
target_link_libraries(raytracer PRIVATE camera)
target_link_libraries(raytracer PRIVATE hit)