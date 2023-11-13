#ifndef RPG_VERTEX_H
#define RPG_VERTEX_H

struct Color {
    float r, g, b;
};

struct Vertex {
    float Position[3];
    float TextureCord[2];
    float TextureId;
};

#endif //RPG_VERTEX_H
