#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#ifndef buttons_hpp
#define buttons_hpp

#include <stdio.h>
#include "game-object.hpp"
// Класс Кнопки (обычная текстовая)
class Button {
protected:
    int x; // x координата кнопки
    int y; // y координата кнопки
    SDL_Surface* surface; // Ссылка на поверхность
    SDL_Texture* texture; // Cсылка на текстуру текста кнопки
    SDL_Renderer* renderer; // Ссылка на рендерер
    TTF_Font* font; // Ссылка на шрифт
    char *text; // Ссылка на отрисовываемый текст
public:
    Button() {}
    Button(SDL_Renderer* ren, const char *str, TTF_Font* font, SDL_Color color);
    void init(SDL_Renderer* ren, const char *str, TTF_Font* font, SDL_Color color);
    void setCoords(int xCoord, int yCoord);
    void changeColor(SDL_Color color);
    void draw();
    bool isCoordsInside(int x, int y);
    ~Button();
};
// Класс Кнопки-Картинки
class ImageButton {
public:
    GameObject buttonImage; // Объект кнопки с изображением
    bool isCoordsInside(int x, int y);
    void draw();
    void init(SDL_Renderer *ren, const char *file);
    void setCoords(int xCoord, int yCoord);
    ImageButton() {}
    ImageButton(SDL_Renderer *ren, const char *file);
};

#endif /* buttons_hpp */
