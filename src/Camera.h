#ifndef RPG_CAMERA_H
#define RPG_CAMERA_H


#include "glad/glad.h"

class Camera {
public:
    static void applyView(GLuint shaderId);

    static float x;
    static float y;

};


#endif //RPG_CAMERA_H
