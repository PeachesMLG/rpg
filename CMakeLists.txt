cmake_minimum_required(VERSION 3.27)
project(rpg)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glm)

add_executable(rpg
        src/main.cpp
        src/Renderer/Shader.cpp
        src/Renderer/Shader.h
        src/Renderer/VBO.cpp
        src/Renderer/VBO.h
        src/Renderer/EBO.cpp
        src/Renderer/EBO.h
        src/Renderer/VAO.cpp
        src/Renderer/VAO.h
        src/Renderer/Vertex.h
        src/Renderer/Renderer.cpp
        src/Renderer/Renderer.h
        src/Camera.cpp
        src/Camera.h
        src/Renderer/Textures.cpp
        src/Renderer/Textures.h
        src/Renderer/Sprite.h
        src/Player.cpp
        src/Player.h
)

target_link_libraries(rpg PUBLIC glfw glad glm)