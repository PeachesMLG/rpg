#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Renderer.h"
#include "Vertex.h"
#include "Shader.h"
#include "VAO.h"
#include "EBO.h"
#include "glm/gtc/type_ptr.hpp"
#include "../Camera.h"

void Renderer::Init() {
}

void Renderer::Render(float Position[2], float Color[3]) {
    Vertex verticies[] = {
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f
    };

    GLuint indicies[] = {
            0, 1, 3,
            1, 2, 3
    };

    Shader shaderProgram(
            "/home/chris/CLionProjects/rpg/shaders/default.vert",
            "/home/chris/CLionProjects/rpg/shaders/default.frag"
    );

    VAO vao;
    vao.Bind();

    VBO vbo(verticies, sizeof(verticies));
    EBO ebo(indicies, sizeof(indicies));
    vao.LinkVBO(vbo);
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    shaderProgram.Activate();

    Camera::applyView(shaderProgram.ID);

    auto model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(Position[0], Position[1], 0.0f));
    int modelLog = glGetUniformLocation(shaderProgram.ID, "model");
    glUniformMatrix4fv(modelLog, 1, GL_FALSE, glm::value_ptr(model));

    ebo.Bind();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(int), GL_UNSIGNED_INT, 0);
}