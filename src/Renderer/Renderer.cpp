#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Renderer.h"
#include "Vertex.h"
#include "Shader.h"
#include "VAO.h"
#include "EBO.h"
#include "glm/gtc/type_ptr.hpp"

Vertex verticies[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f
};

GLuint indicies[] = {
        0, 1, 3,
        1, 2, 3
};

Renderer::Renderer(const Shader &shaderProgram) : shaderProgram(shaderProgram) {
    vao.Bind();
    vbo = VBO(verticies, sizeof(verticies));
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