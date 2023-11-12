#ifndef RPG_RENDERER_H
#define RPG_RENDERER_H


#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Renderer {
public:
    static void Init();

    static void Render(float Position[2], float Color[3]);
};


#endif //RPG_RENDERER_H
