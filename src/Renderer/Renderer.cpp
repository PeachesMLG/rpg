#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Renderer.h"
#include "Vertex.h"
#include "Shader.h"
#include "VAO.h"
#include "EBO.h"
#include "Sprite.h"
#include "glm/gtc/type_ptr.hpp"

void Renderer::setIndicies(std::vector<SpriteLocation> sprites) {
    for (auto i = 0; i < sprites.size(); ++i) {
        Renderer::indicies[(i * 6) + 0] = (i * 4) + 0;
        Renderer::indicies[(i * 6) + 1] = (i * 4) + 1;
        Renderer::indicies[(i * 6) + 2] = (i * 4) + 3;
        Renderer::indicies[(i * 6) + 3] = (i * 4) + 1;
        Renderer::indicies[(i * 6) + 4] = (i * 4) + 2;
        Renderer::indicies[(i * 6) + 5] = (i * 4) + 3;
    }
}

void Renderer::SetSpriteData(std::vector<SpriteLocation> sprites) {
    spriteSize = sprites.size();
    for (auto i = 0; i < sprites.size(); ++i) {
        const SpriteLocation &spriteLocation = sprites[i];
        const Sprite &sprite = spriteLocation.sprite;

        // Bottom Left Vertex
        Renderer::verticies[(i * 4) + 0] = Vertex(
                {{spriteLocation.x, spriteLocation.y, spriteLocation.z},
                 {sprite.xMin, sprite.yMax},
                 static_cast<float>(sprite.textureId)}
        );

        // Top Left Vertex
        Renderer::verticies[(i * 4) + 1] = Vertex(
                {{spriteLocation.x, spriteLocation.y + 1, spriteLocation.z},
                 {sprite.xMin, sprite.yMin},
                 static_cast<float>(sprite.textureId)}
        );

        // Top Right Vertex
        Renderer::verticies[(i * 4) + 2] = Vertex(
                {{spriteLocation.x + 1, spriteLocation.y + 1, spriteLocation.z},
                 {sprite.xMax, sprite.yMin},
                 static_cast<float>(sprite.textureId)}
        );

        // Bottom Right Vertex
        Renderer::verticies[(i * 4) + 3] = Vertex(
                {{spriteLocation.x + 1, spriteLocation.y, spriteLocation.z},
                 {sprite.xMax, sprite.yMax},
                 static_cast<float>(sprite.textureId)}
        );
    }
}

void Renderer::UpdateSprites(std::vector<SpriteLocation> sprites) {
    SetSpriteData(sprites);

    vbo.Update(Renderer::verticies, sizeof(Vertex) * 4 * sprites.size());
}

Renderer::Renderer(const Shader &shaderProgram, std::vector<SpriteLocation> sprites) : shaderProgram(shaderProgram) {
    verticies = new Vertex[sprites.size() * 4];
    indicies = new GLuint[sprites.size() * 6];

    setIndicies(sprites);
    UpdateSprites(sprites);

    vao.Bind();
    vbo = VBO(Renderer::verticies, sizeof(Vertex) * 4 * sprites.size());
    ebo = EBO(Renderer::indicies, sizeof(GLuint) * 6 * sprites.size());

    vao.LinkVBO(vbo);
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Renderer::Render() {
    float positions[] = {0.0f,0.0f};
    Render(positions);
}

void Renderer::Render(float positions[2]) {
    shaderProgram.Activate();

    auto locTextures = glGetUniformLocation(shaderProgram.ID, "textures");
    int samplers[1] = {0};
    glUniform1iv(locTextures, 1, samplers);

    auto model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(positions[0], positions[1], 0.0f));
    int modelLog = glGetUniformLocation(shaderProgram.ID, "model");
    glUniformMatrix4fv(modelLog, 1, GL_FALSE, glm::value_ptr(model));

    ebo.Bind();
    vao.Bind();
    vbo.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(GLuint) * 6 * spriteSize / sizeof(int), GL_UNSIGNED_INT, 0);
//    ebo.Unbind();
//    vao.Unbind();
//    vbo.Bind();
}

void Renderer::Delete() {
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
}
