#include <vector>
#include "Player.h"
#include "Renderer/Sprite.h"

Player::Player() {
    x = 0;
    y = 0;
}

std::vector<SpriteLocation> Player::GetSpriteLocations() {
    Sprite sprite1(0, 5, 5, 16, 480, 769);
    Sprite sprite2(0, 5, 6, 16, 480, 769);

    std::vector<SpriteLocation> spriteLocations;
    spriteLocations.push_back({sprite1, x, y, 0});
    spriteLocations.push_back({sprite2, x, y + 1, 0});
    return spriteLocations;
}
