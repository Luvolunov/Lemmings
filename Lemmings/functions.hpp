#ifndef functions_hpp
#define functions_hpp

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "constants.h"

void makeHorizontalGround(bool groundMatrix[SCREEN_WIDTH][SCREEN_HEIGHT], int from, int to, int y, int size = 18);
void makeVerticalGround(bool groundMatrix[SCREEN_WIDTH][SCREEN_HEIGHT], int from, int to, int x, int size = 18);
void fillGround(bool groundMatrix[SCREEN_WIDTH][SCREEN_HEIGHT]);
void renderText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, const std::string &text, SDL_Rect rect);

#endif /* functions_hpp */
