#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#ifndef buttons_hpp
#define buttons_hpp

#include <stdio.h>

class Button {
protected:
    int x;
    int y;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
public:
    Button(SDL_Renderer* ren, const char *str, TTF_Font* font, SDL_Color color);
    const char *text;
    void setCoords(int xCoord, int yCoord);
    void draw();
    bool isClicked(int x, int y);
    ~Button();
};

#endif /* buttons_hpp */
