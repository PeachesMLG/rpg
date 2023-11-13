#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H


#include "Renderer/Renderer.h"

class Player {
public:
    Player();

    std::vector<SpriteLocation> GetSpriteLocations();

    float x;
    float y;
};


#endif //RPG_PLAYER_H
