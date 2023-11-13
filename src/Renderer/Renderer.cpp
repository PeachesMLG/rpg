#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include "Renderer.h"
#include "Vertex.h"
#include "Shader.h"
#include "VAO.h"
#include "EBO.h"
#include "glm/gtc/type_ptr.hpp"
#include "Sprite.h"

GLuint indicies[] = {
        0, 1, 3,
        1, 2, 3
};

void Renderer::UpdateVerticies(std::vector<SpriteLocation> sprites) {
    for (auto i = 0; i < sprites.size(); ++i) {
        const SpriteLocation &spriteLocation = sprites[i];
        const Sprite &sprite = spriteLocation.sprite;

        // Bottom Left Vertex
        Renderer::verticies[(i * 4) + 0] = Vertex(
                {{spriteLocation.x, spriteLocation.y, spriteLocation.z}, {sprite.xMin, sprite.yMin},
                 static_cast<float>(sprite.textureId)});

        // Top Left Vertex
        Renderer::verticies[(i * 4) + 1] = Vertex(
                {{spriteLocation.x, spriteLocation.y + 1, spriteLocation.z}, {sprite.xMin, sprite.yMax},
                 static_cast<float>(sprite.textureId)});

        // Top Right Vertex
        Renderer::verticies[(i * 4) + 2] = Vertex(
                {{spriteLocation.x + 1, spriteLocation.y + 1, spriteLocation.z}, {sprite.xMax, sprite.yMax},
                 static_cast<float>(sprite.textureId)});

        // Bottom Right Vertex
        Renderer::verticies[(i * 4) + 3] = Vertex(
                {{spriteLocation.x + 1, spriteLocation.y, spriteLocation.z}, {sprite.xMax, sprite.yMin},
                 static_cast<float>(sprite.textureId)});
    }
}

Renderer::Renderer(const Shader &shaderProgram, std::vector<SpriteLocation> sprites) : shaderProgram(shaderProgram) {
    UpdateVerticies(sprites);
    vao.Bind();
    vbo = VBO(Renderer::verticies, sizeof(Vertex) * 4 * sprites.size());
    ebo = EBO(indicies, sizeof(indicies));

    vao.LinkVBO(vbo);
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Renderer::Render() {
    shaderProgram.Activate();

    auto loc = glGetUniformLocation(shaderProgram.ID, "textures");
    int samplers[1] = {0};
    glUniform1iv(loc, 1, samplers);

    ebo.Bind();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void Renderer::Delete() {
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
}