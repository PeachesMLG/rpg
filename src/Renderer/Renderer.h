#ifndef RPG_RENDERER_H
#define RPG_RENDERER_H


#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Renderer {
public:
    Renderer(const Shader &shaderProgram);

    void Render(float Position[2], float Color[3]);
    void Delete();

private:
    Shader shaderProgram;
    VAO vao;
    VBO vbo;
    EBO ebo;
};


#endif //RPG_RENDERER_H
