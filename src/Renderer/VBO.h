#ifndef RPG_VBO_H
#define RPG_VBO_H

#include<glad/glad.h>
#include "Vertex.h"

class VBO {
public:
    GLuint ID;

    VBO();
    VBO(Vertex *vertices, GLsizeiptr size);

    void Bind();

    void Unbind();

    void Delete();
};


#endif //RPG_VBO_H
