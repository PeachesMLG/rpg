#ifndef RPG_RENDERER_H
#define RPG_RENDERER_H


#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Sprite.h"
#include <vector>

class Renderer {
public:
    Renderer(const Shader &shaderProgram, std::vector<SpriteLocation> sprites);

    void UpdateVerticies(std::vector<SpriteLocation> sprites);

    void Render();

    void Delete();

private:
    Shader shaderProgram;
    VAO vao;
    VBO vbo;
    EBO ebo;
    Vertex verticies[];
};


#endif //RPG_RENDERER_H
