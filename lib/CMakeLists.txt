# Ray Tracer Library Components
cmake_minimum_required(VERSION 3.10)

# Core raytracing math and utilities
add_library(raycore 
    raycore/src/vec3.cpp 
    raycore/src/ray.cpp 
    raycore/src/color.cpp 
    raycore/src/util.cpp
)

# Image processing library (no dependencies)
add_library(image 
    image/src/ppm.cpp
)

# Materials library (depends on raycore and shapes via forward declaration)
add_library(materials
    materials/src/Lambertian.cpp
    materials/src/Metal.cpp
    materials/src/Dielectric.cpp
)

# Shapes library (depends on raycore and materials via forward declaration)
add_library(shapes
    shapes/src/Sphere.cpp
    shapes/src/HittableList.cpp
)

# Camera library
add_library(camera 
    camera/src/camera.cpp
)

# Texture library (no dependencies)
add_library(texture
    texture/src/Checker.cpp
)

# Include directories
target_include_directories(raycore PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/raycore/include
    ${CMAKE_CURRENT_SOURCE_DIR}/shapes/include
    ${CMAKE_CURRENT_SOURCE_DIR}/materials/include
)
target_include_directories(materials PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/materials/include)
target_include_directories(shapes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/shapes/include)
target_include_directories(camera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/camera/include)
target_include_directories(image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/image/include)
target_include_directories(texture PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/texture/include)

# Dependency relationships
target_link_libraries(materials PUBLIC raycore texture)
target_link_libraries(shapes PUBLIC raycore)
target_link_libraries(camera PUBLIC raycore)

# raycore is header-only dependent on shapes/materials types (for color.hpp),
# but we avoid a link cycle; only include dirs are required.


# Compiler features
target_compile_features(raycore PUBLIC cxx_std_17)
target_compile_features(materials PUBLIC cxx_std_17)
target_compile_features(shapes PUBLIC cxx_std_17)
target_compile_features(camera PUBLIC cxx_std_17)
target_compile_features(image PUBLIC cxx_std_17)