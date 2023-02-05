#ifndef game_object_hpp
#define game_object_hpp
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

enum GameObjectDirection {
    top = 0,
    bottom,
    left,
    right
};

class GameObject {
public:
    SDL_Renderer *renderer;
    SDL_Texture *image;
    SDL_Rect box;
    Uint8 spritesCount;
    bool flipped = false;
    SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
    
    GameObject(SDL_Renderer *renderer, SDL_Rect& size, Uint8 spritesCount, const char *file);
    void draw();
    void move(GameObjectDirection direction, int pixels);
    GameObject() {}
    void setAnimationDelay(const Uint8 ticksDelay);
protected:
    Uint8 animationTicksDelay = 200;
};

#endif /* game_object_hpp */
