cmake_minimum_required(VERSION 3.27)
project(rpg)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glm)

add_executable(rpg src/main.cpp)

target_link_libraries(rpg PUBLIC glfw glad glm)
