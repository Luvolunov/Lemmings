#ifndef game_hpp
#define game_hpp
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <filesystem>

#include "game-object.hpp"
#include "soldier.hpp"
#include "buttons.hpp"

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 600;
const unsigned int SOLDIERS_COUNT = 10;

enum GameState {
    MainMenu,
    Run,
    Menu,
};

class Game {
private:
    void runGame();
    void runMenu();
    void runMainMenu();
    TTF_Font* bigFont;
    TTF_Font* smallFont;
    Button* playButton;
    Button* exitButton;
public:
    Game(): state(MainMenu) {}
    int init(const int& width, const int& height);
    int iterate();
    int exit();
    bool quit = false;
    void handleClick(SDL_MouseButtonEvent &e);
    
    SDL_Window *window;
    Soldier soldiers[SOLDIERS_COUNT];
    SDL_Renderer *renderer;
    GameState state;
};

#endif /* game_hpp */
