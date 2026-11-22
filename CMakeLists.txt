cmake_minimum_required(VERSION 3.20)
project(raytracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Strict warnings applied to our own targets only
add_library(raytracer_warnings INTERFACE)
if(MSVC)
  target_compile_options(raytracer_warnings INTERFACE /W4)
else()
  target_compile_options(raytracer_warnings INTERFACE -Wall -Wextra -Wpedantic)
endif()

# External dependencies via FetchContent
include(FetchContent)

FetchContent_Declare(
  lodepng
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG        master
)
FetchContent_GetProperties(lodepng)
if(NOT lodepng_POPULATED)
  FetchContent_Populate(lodepng)
  add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
  target_include_directories(lodepng PUBLIC ${lodepng_SOURCE_DIR})
endif()

# Core library shared by the app and unit tests
add_library(raytracer_core
    src/colour/colour.cpp
    src/geometry/ray.cpp
    src/geometry/plane.cpp
    src/geometry/sphere.cpp
    src/io/png_saver.cpp
    src/light/light.cpp
    src/material/flat_shader.cpp
    src/material/lambert_shader.cpp
    src/math/vector.cpp
    src/render/camera.cpp
    src/render/image.cpp
    src/render/scene.cpp
)
target_include_directories(raytracer_core PUBLIC src)
target_link_libraries(raytracer_core PRIVATE raytracer_warnings lodepng)

# Main executable
add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core raytracer_warnings)

# Unit tests (Catch2 + CTest)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_executable(tests
    tests/test_main.cpp
    tests/test_helpers.cpp
    tests/colour/test_colour.cpp
    tests/geometry/test_ray.cpp
    tests/geometry/test_plane.cpp
    tests/geometry/test_sphere.cpp
    tests/io/test_png_saver.cpp
    tests/light/test_light.cpp
    tests/material/test_material.cpp
    tests/math/test_vector.cpp
    tests/render/test_camera.cpp
    tests/render/test_image.cpp
    tests/render/test_scene.cpp
)
target_include_directories(tests PRIVATE tests)
target_link_libraries(tests PRIVATE raytracer_core raytracer_warnings Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)
