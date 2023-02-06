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
#include "constants.h"
// Состояние Игры
enum GameState {
    MainMenu,
    Run,
};
// Класс Игры
class Game {
private:
    void runGame(); // Метод отрисовки и итерации игры
    void runMainMenu(); // Метод отрисовки меню
    TTF_Font* bigFont; // Большой шрифт
    TTF_Font* regularFont; // Средний шрифт
    TTF_Font* smallFont; // Маленький шрифт
    Button playButton; // Объект кнопки "Play" в главном меню
    Button exitButton; // Объект кнопки "Exit" в главном меню
    ImageButton digDownButton; // Объект кнопки "Копать вниз" в меню игры
    ImageButton digToDirectionButton; // Объект кнопки "Копать в сторону" в меню игры
    ImageButton blockButton; // Объект кнопки "Блокировать" в меню игры
    SoldierMode chosenMode; // Выбранный приказ
    bool modeIsChosen = false; // Флаг для обозначения того, выбран ли приказ
public:
    Game(): state(MainMenu) {}
    int init(const int& width, const int& height);
    int iterate();
    int exit();
    bool quit = false; // Свойство, отвечающее за выход из игры
    bool groundMatrix[SCREEN_WIDTH][SCREEN_HEIGHT]; // Матрица, отвечающая за "землю"
    void handleClick(SDL_MouseButtonEvent &e);
    SDL_MouseMotionEvent motionEvent;
    
    SDL_Window *window; // Ссылка на объект окна
    Soldier soldiers[SOLDIERS_COUNT]; // Массив солдатов
    GameObject finishDoor; // Объект финишной двери
    GameObject background; // Объект фона
    SDL_Rect smallMenuRect;
    SDL_Renderer *renderer; // Ссылка на рендерер
    GameState state; // Состояние игры (игра или меню)
    GameObject fire;
    GameObject soldierHead;
};

#endif /* game_hpp */
