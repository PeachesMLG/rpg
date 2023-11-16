#ifndef RPG_SPRITE_H
#define RPG_SPRITE_H


struct Sprite {
    int textureId;
    float xMin;
    float xMax;
    float yMin;
    float yMax;

    Sprite(int textureId, int x, int y, float size, float width, float height) {
        this->textureId = textureId;
        this->xMin = static_cast<float>(x) * size / width;
        this->xMax = static_cast<float>(x + 1) * size / width;
        this->yMin = static_cast<float>(y) * size / height;
        this->yMax = static_cast<float>(y + 1) * size / height;
    }
};

struct SpriteLocation {
    Sprite sprite;
    float x;
    float y;
    float z;
};

#endif //RPG_SPRITE_H
