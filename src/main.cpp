#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer/Renderer.h"
#include "Camera.h"

const GLchar *vert = R"END(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;

void main()
{
    gl_Position = view * model * vec4(aPos, 1.0);
}
)END";

const GLchar *frag = R"END(
#version 330 core

out vec4 FragColor;

//uniform vec3 color;

void main()
{
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
)END";

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    Camera::zoom += yoffset * 0.1f;
    Camera::zoom = std::max(0.1f, Camera::zoom);
}


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        Camera::y -= 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        Camera::y += 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        Camera::x += 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        Camera::x -= 0.1f;
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1200, 1200, "RPG", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.192156862745f, 0.180392156863f, 0.16862745098f, 1.0f);

    Shader shaderProgram(vert, frag);

    Renderer renderer(shaderProgram);

    while (!glfwWindowShouldClose(window)) {
        double startTime = glfwGetTime();
        processInput(window);

        // Render Here
        glClear(GL_COLOR_BUFFER_BIT);

        float position[2] = {0.0f, 0.0f};
        float color[3] = {0.97f, 0.97f, 0.43f};


        Camera::applyView(shaderProgram.ID);
        renderer.Render(position, color);

        glfwSwapBuffers(window);
        glfwPollEvents();

        double time = (glfwGetTime() - startTime) * 1000;
        std::string title = "RPG - FPS: " + std::to_string((int) (1000 / time));
        glfwSetWindowTitle(window, title.c_str());
    }

    renderer.Delete();
    shaderProgram.Delete();

    glfwTerminate();
    return 0;
}
