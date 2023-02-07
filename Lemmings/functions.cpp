#include "functions.hpp"
// Метод, который заполняет землю по горизонтали от from до to с координаты "y" шириной size
void makeHorizontalGround(bool groundMatrix[SCREEN_WIDTH][SCREEN_HEIGHT], int from, int to, int y, int size) {
    for (int i = from; i < to; ++i) {
        for (int j = 0; j < size; ++j) {
            groundMatrix[i][y + j] = true;
        }
    }
}
// Метод, который заполняет землю по вертикали от from до to с координаты "ч" шириной size
void makeVerticalGround(bool groundMatrix[SCREEN_WIDTH][SCREEN_HEIGHT], int from, int to, int x, int size) {
    for (int i = from; i < to; ++i) {
        for (int j = 0; j < size; ++j) {
            groundMatrix[x + j][i] = true;
        }
    }
}
// Общий метод, где описывается логика заполнения карты землёй
void fillGround(bool groundMatrix[SCREEN_WIDTH][SCREEN_HEIGHT]) {
    for (unsigned int i = 0; i < SCREEN_WIDTH; ++i) {
        for (unsigned int j = 0; j < SCREEN_HEIGHT_WITHOUT_MENU; ++j) {
            groundMatrix[i][j] = false;
        }
    }
    makeHorizontalGround(groundMatrix, 0, SCREEN_WIDTH - 200, 50);
    makeVerticalGround(groundMatrix, 0, 50, 513);
    
    makeHorizontalGround(groundMatrix, SCREEN_WIDTH - 200, SCREEN_WIDTH, 100);
    makeHorizontalGround(groundMatrix, SCREEN_WIDTH - 300, SCREEN_WIDTH - 200, 150);
    makeVerticalGround(groundMatrix, 50, 222, 91);
    
    makeHorizontalGround(groundMatrix, 50, SCREEN_WIDTH - 300, 200);
    makeHorizontalGround(groundMatrix, SCREEN_WIDTH - 200, SCREEN_WIDTH, 200);
    
    makeHorizontalGround(groundMatrix, 0, 100, 250);
    makeVerticalGround(groundMatrix, 200, 250, 91);
    
    makeHorizontalGround(groundMatrix, SCREEN_WIDTH - 350, SCREEN_WIDTH, 300);
    makeHorizontalGround(groundMatrix, 0, SCREEN_WIDTH, 360);
    makeHorizontalGround(groundMatrix, SCREEN_WIDTH - 400, SCREEN_WIDTH, SCREEN_HEIGHT_WITHOUT_MENU - 100);
    makeVerticalGround(groundMatrix, SCREEN_HEIGHT_WITHOUT_MENU - 100, SCREEN_HEIGHT_WITHOUT_MENU, SCREEN_WIDTH - 403);
}
// Метод для рендера текста на холст
void renderText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, const std::string &text, SDL_Rect rect) {
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    rect.w = surfaceMessage->w;
    rect.h = surfaceMessage->h;
    SDL_RenderCopy(renderer, message, NULL, &rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}
