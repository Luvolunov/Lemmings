#ifndef soldier_hpp
#define soldier_hpp
#include "game-object.hpp"
#include "constants.h"
#include <stdio.h>

// Состояния солдата: бег, полёт, копание вниз, копание в сторону, блокировщик
enum SoldierMode {
    run = 0,
    fly,
    digDown,
    digToDirection,
    block,
};
// Класс Солдата
class Soldier {
private:
    GameObjectDirection direction; // Направление движения солдата
    GameObject soldier; // Объект солдата
    SDL_Renderer *renderer; // Ссылка на рендерер
    SoldierMode mode = run; // Состояние солдата
    const char *runSprite = "assets/soldier-run.png"; // Путь до спрайта с бегущим солдатом
    const char *flySprite = "assets/soldier-fly-2.png"; // Путь до спрайта с летящим солдатом
    const char *digDownSprite = "assets/soldier-dig-2.png"; // Путь до спрайта с копающим вниз солдатом
    const char *digToDirectionSprite = "assets/soldier-dig-direction.png"; // Путь до спрайта с копающим в сторону солдатом
    const char *blockSprite = "assets/soldier-block.png"; // Путь до спрайта с блокирующим солдатом
    
    SDL_Texture *runTexture; // Текстура спрайта бегущего солдата
    SDL_Texture *flyTexture; // Текстура спрайта летящего солдата
    SDL_Texture *digDownTexture; // Текстура спрайта копающего вниз солдата
    SDL_Texture *digToDirectionTexture; // Текстура спрайта копающего в сторону солдата
    SDL_Texture *blockTexture; // Текстура спрайта блокирующего солдата
public:
    bool gone = false; // Переменная для определения, вышел ли солдат из карты через дверь
    Soldier(): mode(run) {};
    Soldier(SDL_Renderer *renderer);
    void action(int iteration, bool matrix[SCREEN_WIDTH][SCREEN_HEIGHT], Soldier soldiers[SOLDIERS_COUNT]);
    void draw();
    GameObjectDirection getDirection();
    SoldierMode getMode();
    void setDirection(GameObjectDirection direction);
    void setMode(SoldierMode soldierMode);
    SDL_Rect getBox();
};


#endif /* soldier_hpp */
