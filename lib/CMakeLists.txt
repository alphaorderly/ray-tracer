add_library(raycore raycore/src/vec3.cpp raycore/src/ray.cpp raycore/src/color.cpp)

target_include_directories(raycore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/raycore/include)

add_library(image image/src/ppm.cpp)

target_include_directories(image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/image/include)