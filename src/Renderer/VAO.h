#ifndef RPG_VAO_H
#define RPG_VAO_H

#include<glad/glad.h>
#include"VBO.h"

class VAO {
public:
    GLuint ID;

    VAO();

    void LinkVBO(VBO &vbo);

    void Bind();

    void Unbind();

    void Delete();
};

#endif //RPG_VAO_H
