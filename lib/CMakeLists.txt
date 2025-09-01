add_library(raycore raycore/src/vec3.cpp raycore/src/ray.cpp raycore/src/color.cpp)

add_library(camera camera/src/camera.cpp)

add_library(image image/src/ppm.cpp)

add_library(hit hit/src/hittable.cpp hit/src/hit_record.cpp hit/src/hittable_list.cpp hit/src/sphere.cpp hit/src/hittable_list.cpp)

target_include_directories(raycore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/raycore/include)

target_include_directories(image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/image/include)

target_include_directories(camera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/camera/include)

target_include_directories(hit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hit/include)

target_link_libraries(camera PUBLIC raycore)

target_link_libraries(hit PUBLIC raycore)