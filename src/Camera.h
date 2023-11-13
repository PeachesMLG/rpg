#ifndef RPG_CAMERA_H
#define RPG_CAMERA_H


#include "glad/glad.h"
#include "Player.h"

class Camera {
public:
    static void applyView(GLuint shaderId, Player player);
    static float zoom;

};


#endif //RPG_CAMERA_H
