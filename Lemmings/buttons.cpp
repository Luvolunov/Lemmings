#include "buttons.hpp"

Button::Button(SDL_Renderer* ren, const char *str, TTF_Font* f, SDL_Color color) {
    font = f;
    renderer = ren;
    surface = TTF_RenderText_Blended(font, str, color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}
// Метод инициализации кнопки, где сохраняется ссылка на рендерер, шрифт, текст
void Button::init(SDL_Renderer* ren, const char *str, TTF_Font* f, SDL_Color color) {
    font = f;
    renderer = ren;
    surface = TTF_RenderText_Blended(font, str, color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}
// Метод для установки координат кнопк
void Button::setCoords(int xCoord, int yCoord) {
    x = xCoord;
    y = yCoord;
}
// Метод отрисовки кнопки
void Button::draw() {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
// Метод проверки, попадают ли координаты внутрь кнопки
// Используется для проверки того, кликнул ли пользователь по этой кнопке или нет
bool Button::isCoordsInside(int xCoord, int yCoord) {
    return xCoord > x && xCoord < x + surface->w && yCoord > y && yCoord < y + surface->h;
}

Button::~Button() {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// ImageButton

ImageButton::ImageButton(SDL_Renderer *ren, const char *file) {
    SDL_Rect size;
    size = { 0, 0, 80, 80 };
    buttonImage = GameObject(ren, size, 1, file);
}
// Метод отрисовки кнопки-картинки
void ImageButton::draw() {
    buttonImage.draw();
}
// Метод для установки координат кнопки-картинки
void ImageButton::setCoords(int xCoord, int yCoord) {
    buttonImage.box.x = xCoord;
    buttonImage.box.y = yCoord;
}
// Метод проверки, попадают ли координаты внутрь кнопки
// Используется для проверки того, кликнул ли пользователь по этой кнопке или нет
bool ImageButton::isCoordsInside(int xCoord, int yCoord) {
    return xCoord > buttonImage.box.x &&
        xCoord < buttonImage.box.x + buttonImage.box.w &&
        yCoord > buttonImage.box.y &&
        yCoord < buttonImage.box.y + buttonImage.box.h;
}
// Метод инициализации кнопки-картинки, где создаётся игровой объект
void ImageButton::init(SDL_Renderer *ren, const char *file) {
    SDL_Rect size;
    size = { 0, 0, 80, 80 };
    buttonImage = GameObject(ren, size, 1, file);
}
