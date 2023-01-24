#include "soldier.hpp"

Soldier::Soldier(SDL_Renderer *ren) {
    renderer = ren;
    SDL_Rect soldierBox;
    soldierBox = { 0, 0, 16, 32 };
    soldier = GameObject(renderer, soldierBox, 4, runSprite);
    soldier.setAnimationDelay(125);
    direction = right;
}

void Soldier::setDirection(GameObjectDirection dir) {
    direction = dir;
    soldier.flipped = dir == left;
}

void Soldier::action() {
    switch (mode) {
        case run:
            soldier.move(direction, 1);
            break;
            
        default:
            break;
    }
}

void Soldier::draw() {
    soldier.draw();
}

void Soldier::setMode(SoldierMode soldierMode = run) {
    mode = soldierMode;
}

SDL_Rect Soldier::getBox() {
    return soldier.box;
}
