#include "buttons.hpp"

Button::Button(SDL_Renderer* ren, const char *str, TTF_Font* font, SDL_Color color) {
    renderer = ren;
    surface = TTF_RenderText_Blended(font, str, color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}

void Button::setCoords(int xCoord, int yCoord) {
    x = xCoord;
    y = yCoord;
}

void Button::draw() {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

bool Button::isClicked(int xCoord, int yCoord) {
    return xCoord > x;
}

Button::~Button() {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
