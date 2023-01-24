#ifndef soldier_hpp
#define soldier_hpp
#include "game-object.hpp"
#include <stdio.h>

enum SoldierMode {
    run = 0,
    fly,
    digDown,
    digToDirection,
    block,
};

class Soldier: GameObject {
private:
    GameObjectDirection direction;
    GameObject soldier;
    SDL_Renderer *renderer;
    SoldierMode mode = run;
    const char *runSprite = "assets/soldier-run.png";
    const char *flySprite = "assets/soldier-run.png";
    const char *digDownSprite = "assets/soldier-run.png";
    const char *digToDirectionSprite = "assets/soldier-run.png";
    const char *blockSprite = "assets/soldier-run.png";
public:
    Soldier(): mode(run) {};
    Soldier(SDL_Renderer *renderer);
    void action();
    void draw();
    void setDirection(GameObjectDirection direction);
    void setMode(SoldierMode soldierMode);
    SDL_Rect getBox();
};


#endif /* soldier_hpp */
