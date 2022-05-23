cmake_minimum_required(VERSION 3.6)

project(NuakeRendererDemo)
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)
add_subdirectory(./NuakeRenderer)
include_directories(./NuakeRenderer/)

add_executable(NuakeRendererDemo src/main.cpp)

target_link_libraries(NuakeRendererDemo PUBLIC NuakeRenderer)
