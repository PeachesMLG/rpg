#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer/Renderer.h"
#include "Camera.h"
#include "Renderer/Textures.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../../dependencies/stb/stb_image.h"
#include "Player.h"


const GLchar *vert = R"END(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aTexId;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 texCoord;
out float texId;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    texCoord = aTexCoord;
    texId = aTexId;
}
)END";

const GLchar *frag = R"END(
#version 330 core

out vec4 FragColor;

in vec2 texCoord;
in float texId;

uniform sampler2D[1] textures;

void main()
{
    FragColor = FragColor = texture(textures[int(texId)], texCoord);
}
)END";

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, float deltaTime, Player *player) {
    const float cameraSpeed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 8.0f : 4.0f;
    float moveX = 0.0f, moveY = 0.0f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        moveY += cameraSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        moveY -= cameraSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        moveX -= cameraSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        moveX += cameraSpeed * deltaTime;
    }

    // Normalize diagonal movement
    if (moveX != 0.0f && moveY != 0.0f) {
        float normalizationFactor = cameraSpeed * deltaTime / sqrt(moveX * moveX + moveY * moveY);
        moveX *= normalizationFactor;
        moveY *= normalizationFactor;
    }

    player->x += moveX;
    player->y += moveY;
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

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.192156862745f, 0.180392156863f, 0.16862745098f, 1.0f);

    Player player;

    Shader shaderProgram(vert, frag);

    auto texture = Textures::GenerateTexture("/home/chris/CLionProjects/rpg/assets/terrain.png", 0);

    Sprite sprite(0, 3, 0, 16, 304, 720);
    std::vector<SpriteLocation> spriteLocations;
    for (int x = -10; x < 10; ++x) {
        for (int y = -10; y < 10; ++y) {
            spriteLocations.push_back({sprite, static_cast<float>(x), static_cast<float>(y), 0});
        }
    }
    std::vector<SpriteLocation> playerLocations = player.GetSpriteLocations();
    spriteLocations.insert(spriteLocations.end(), playerLocations.begin(), playerLocations.end());

    Renderer renderer(shaderProgram, spriteLocations);

    double lastTime = glfwGetTime();

    int i = 0;

    while (!glfwWindowShouldClose(window)) {
        i++;
        double startTime = glfwGetTime();
        double deltaTime = startTime - lastTime;
        processInput(window, (float) deltaTime, &player);

        glClear(GL_COLOR_BUFFER_BIT);

        Camera::applyView(shaderProgram.ID, player);

        spriteLocations.clear();
        for (int x = -10; x < 10; ++x) {
            for (int y = -10; y < 10; ++y) {
                spriteLocations.push_back({sprite, static_cast<float>(x), static_cast<float>(y), 0});
            }
        }
        playerLocations = player.GetSpriteLocations();
        spriteLocations.insert(spriteLocations.end(), playerLocations.begin(), playerLocations.end());

        renderer.UpdateSprites(spriteLocations);
        renderer.Render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        lastTime = startTime;
        double time = (glfwGetTime() - startTime) * 1000;
        std::string title = "RPG - FPS: " + std::to_string((int) (1000 / time));
        glfwSetWindowTitle(window, title.c_str());
    }

    renderer.Delete();
    shaderProgram.Delete();

    glfwTerminate();
    return 0;
}
