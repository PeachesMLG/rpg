#include"VBO.h"

VBO::VBO(Vertex *vertices, GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::VBO() {

}

void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Update(Vertex *vertices, GLsizeiptr size) {
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
    Unbind();
}

void VBO::Delete() {
    glDeleteBuffers(1, &ID);
}