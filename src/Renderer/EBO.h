#ifndef RPG_EBO_H
#define RPG_EBO_H

#include<glad/glad.h>

class EBO {
public:
    GLuint ID;

    EBO(GLuint *indices, GLsizeiptr size);

    void Bind();

    void Unbind();

    void Delete();
};

#endif //RPG_EBO_H
