#include "game-object.hpp"

GameObject::GameObject(SDL_Renderer *ren, SDL_Rect &size, Uint8 count, const char *file) {
    SDL_Surface *imageSurface = IMG_Load(file);
    image = SDL_CreateTextureFromSurface(ren, imageSurface);
    SDL_FreeSurface(imageSurface);
    renderer = ren;
    spritesCount = count;
    if (image == NULL) {
        throw "Image could not be loaded!";
    }
    box = size;
}

void GameObject::draw() {
    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / animationTicksDelay;
    int sprite = seconds % spritesCount;
    SDL_Rect zone = { sprite * box.w, 0, box.w, box.h };
    if (!flipped) {
        SDL_RenderCopy(renderer, image, &zone, &box);
    } else {
        SDL_RenderCopyEx(renderer, image, &zone, &box, 180, NULL, flip);
    }
}

void GameObject::move(GameObjectDirection direction, const int pixels) {
    switch (direction) {
        case left:
            box.x -= pixels;
            break;
        case right:
            box.x += pixels;
            break;
        case top:
            box.y -= pixels;
            break;
        case bottom:
            box.y += pixels;
            break;
    }
}

void GameObject::setAnimationDelay(Uint8 ticksDelay) {
    animationTicksDelay = ticksDelay;
}
