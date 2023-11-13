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
    Renderer();
    Renderer(const Shader &shaderProgram, std::vector<SpriteLocation> sprites);

    void UpdateSprites(std::vector<SpriteLocation> sprites);

    void Render();
    void Render(float positions[2]);

    void Delete();

private:
    void setIndicies(std::vector<SpriteLocation> sprites);
    void SetSpriteData(std::vector<SpriteLocation> sprites);
    Shader shaderProgram;
    VAO vao;
    VBO vbo;
    EBO ebo;
    Vertex *verticies;
    GLuint *indicies;
    int spriteSize;
};


#endif //RPG_RENDERER_H
