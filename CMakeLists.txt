cmake_minimum_required(VERSION 3.6)

project(NuakeRendererDemo)

add_subdirectory(./NuakeRenderer)
include_directories(./NuakeRenderer/)

add_executable(NuakeRendererDemo src/main.cpp)

target_link_libraries(NuakeRendererDemo PUBLIC NuakeRenderer)
