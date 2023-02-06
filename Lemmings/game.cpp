#include "game.hpp"
#include "game-object.hpp"
#include "buttons.hpp"

const SDL_Color mainColor = { 0x48, 0x48, 0x48, 0xFF };
const SDL_Color secondColor = { 0xD0, 0xD0, 0xD0, 0xFF };
const SDL_Color blackColor = { 0x00, 0x00, 0x00, 0xFF };
const SDL_Color whiteColor = { 0xFF, 0xFF, 0xFF, 0xFF };

int iteration = 0;
int soldiersCreated = 0;

// Метод, который заполняет землю по горизонтали от from до to с координаты "y" шириной size
void makeHorizontalGround(bool groundMatrix[SCREEN_WIDTH][SCREEN_HEIGHT], int from, int to, int y, int size = 18) {
    for (int i = from; i < to; ++i) {
        for (int j = 0; j < size; ++j) {
            groundMatrix[i][y + j] = true;
        }
    }
}
// Метод, который заполняет землю по вертикали от from до to с координаты "ч" шириной size
void makeVerticalGround(bool groundMatrix[SCREEN_WIDTH][SCREEN_HEIGHT], int from, int to, int x, int size = 18) {
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
// Метод, где происходит инициализация игры - инициализируются нужные нам библиотеки (SDL_Image, SDL_ttf), создаётся окно с объектом рендерера, создаются кнопки, подгружаются шрифты и разного рода объекты
int Game::init(const int& width, const int& height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("IMG could not initialize! IMG_Error: %s\n", IMG_GetError());
        return 1;
    }
    if (TTF_Init()) {
        fprintf(stderr,"Ошибка в SDL_ttf");
        return 1;
    }
    window = SDL_CreateWindow("Lemmings", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    bigFont = TTF_OpenFont("assets/BlackOpsOne-Regular.ttf", 60);
    regularFont = TTF_OpenFont("assets/BlackOpsOne-Regular.ttf", 28);
    smallFont = TTF_OpenFont("assets/BlackOpsOne-Regular.ttf", 18);
    
    const int doorWidth = 56;
    const int doorHeight = 56;
    
    SDL_Rect doorSize;
    doorSize = { SCREEN_WIDTH - doorWidth * 2, SCREEN_HEIGHT_WITHOUT_MENU - doorHeight, doorWidth, doorHeight };
    
    finishDoor = GameObject(renderer, doorSize, 1, "assets/door-1.png");
    
    smallMenuRect = { 0, SCREEN_HEIGHT_WITHOUT_MENU, SCREEN_WIDTH, 80 };
    
    SDL_Rect backgroundSize;
    backgroundSize = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    background = GameObject(renderer, backgroundSize, 1, "assets/background.png");
    
    playButton.init(renderer, "Play", regularFont, blackColor);
    exitButton.init(renderer, "Exit", regularFont, blackColor);
    
    playButton.setCoords(100, 200);
    exitButton.setCoords(100, 250);
    
    digDownButton.init(renderer, "assets/dig-down-btn.png");
    digToDirectionButton.init(renderer, "assets/dig-to-direction-btn.png");
    blockButton.init(renderer, "assets/block-btn.png");
    
    digDownButton.setCoords(0, SCREEN_HEIGHT_WITHOUT_MENU);
    digToDirectionButton.setCoords(79, SCREEN_HEIGHT_WITHOUT_MENU);
    blockButton.setCoords(158, SCREEN_HEIGHT_WITHOUT_MENU);
    
    fillGround(groundMatrix);
    
    SDL_Rect fireSize = { 203, 4, 24, 32 };
    fire = GameObject(renderer, fireSize, 8, "assets/fire.png");
    
    SDL_Rect soldierHeadSize = { 350, 170, 256, 256 };
    soldierHead = GameObject(renderer, soldierHeadSize, 1, "assets/soldier-head.png");
    
    fire.setAnimationDelay(100);

    return 0;
};
// Метод для прослеживания кликов от юзера по холсту
// Тут описана логика разного взаимодействия при разных режимах игры (игра, меню)
void Game::handleClick(SDL_MouseButtonEvent &e) {
    switch (state) {
        case Run:
            if (modeIsChosen) {
                for (int i = 0; i < soldiersCreated; ++i) {
                    SDL_Rect box = soldiers[i].getBox();
                    bool soldierChosen = box.x < e.x && box.x + box.w > e.x && box.y < e.y && box.y + box.h > e.y;
                    SoldierMode mode = soldiers[i].getMode();
                    if (soldierChosen && mode == run) {
                        soldiers[i].setMode(chosenMode);
                        break;
                    }
                }
            }
            if (digDownButton.isCoordsInside(e.x, e.y)) {
                modeIsChosen = true;
                chosenMode = digDown;
                break;
            }
            if (digToDirectionButton.isCoordsInside(e.x, e.y)) {
                modeIsChosen = true;
                chosenMode = digToDirection;
                break;
            }
            if (blockButton.isCoordsInside(e.x, e.y)) {
                modeIsChosen = true;
                chosenMode = block;
                break;
            }
            break;
        case MainMenu:
            if (playButton.isCoordsInside(e.x, e.y)) {
                state = Run;
                return;
            }
            if (exitButton.isCoordsInside(e.x, e.y)) {
                quit = true;
                return;
            }
            break;
            
        default:
            break;
    }
}
// Метод для запуска 1 итерации основной игры
// Тут описана логика взаимодействия объектов и их отрисовка
void Game::runGame() {
    if (iteration % 100 == 0 && soldiersCreated < SOLDIERS_COUNT)
        soldiers[soldiersCreated++] = Soldier(renderer);
    
    background.draw();
    finishDoor.draw();
    
    SDL_SetRenderDrawColor(renderer, whiteColor.r, whiteColor.g, whiteColor.b, whiteColor.a);
    SDL_RenderFillRect(renderer, &smallMenuRect);
    
    SDL_SetRenderDrawColor(renderer, blackColor.r, blackColor.g, blackColor.b, blackColor.a);
    SDL_RenderDrawRect(renderer, &smallMenuRect);
    
    for (int i = 0; i < soldiersCreated; ++i) {
        SDL_Rect box = soldiers[i].getBox();
        SoldierMode mode = soldiers[i].getMode();
        if (box.x >= finishDoor.box.x &&
            box.x <= finishDoor.box.x + finishDoor.box.w &&
            box.y >= finishDoor.box.y &&
            box.y <= finishDoor.box.y + finishDoor.box.h) {
            soldiers[i].gone = true;
        }
        if (
            motionEvent.x >= box.x &&
            motionEvent.x <= box.x + box.w &&
            motionEvent.y >= box.y &&
            motionEvent.y <= box.y + box.h &&
            modeIsChosen && mode == run
        ) {
            SDL_SetRenderDrawColor(renderer, blackColor.r, blackColor.g, blackColor.b, blackColor.a);
            SDL_RenderDrawRect(renderer, &box);
        }
        soldiers[i].action(iteration, groundMatrix, soldiers);
        soldiers[i].draw();
    }
    
    SDL_SetRenderDrawColor(renderer, mainColor.r, mainColor.g, mainColor.b, mainColor.a);
    
    for (unsigned int i = 0; i < SCREEN_WIDTH; ++i) {
        SDL_RenderDrawPoint(renderer, i, SCREEN_HEIGHT_WITHOUT_MENU);
        for (unsigned int j = 0; j < SCREEN_HEIGHT_WITHOUT_MENU; ++j) {
            if (groundMatrix[i][j]) SDL_RenderDrawPoint(renderer, i, j);
        }
    }
    
    digDownButton.draw();
    digToDirectionButton.draw();
    blockButton.draw();
    
    SDL_SetRenderDrawColor(renderer, secondColor.r, secondColor.g, secondColor.b, secondColor.a);
}
// Метод для отрисовки главного меню
// Тут рисуются кнопки меню и разного рода тексты
void Game::runMainMenu() {
    SDL_SetRenderDrawColor(renderer, whiteColor.r, whiteColor.g, whiteColor.b, whiteColor.a);
    SDL_Rect message_rect;
    message_rect.x = SCREEN_WIDTH / 3.5;
    message_rect.y = 20;
    
    playButton.draw();
    exitButton.draw();
    
    fire.draw();
    soldierHead.draw();
    
    renderText(renderer, bigFont, mainColor, "Lemmings", message_rect);
    
    message_rect.x = 20;
    message_rect.y = SCREEN_HEIGHT - 40;
    renderText(renderer, smallFont, blackColor, "Made by Shukshin Stepan Vladimirovich", message_rect);
}
// Метод для запуска итерации игры, где в зависимости от режима вызывается нужный метод отрисовки:
// Либо метод отрисовки игры, либо метод отрисовки главного меню
int Game::iterate() {
    SDL_RenderClear(renderer);
    
    switch (state) {
        case Run:
            runGame();
            break;
        case MainMenu:
            runMainMenu();
            break;
        default:
            break;
    }
    
    iteration++;
    SDL_RenderPresent(renderer);
    return 0;
}
// Метод для выхода из игры и очистки ненужных нам объектов
int Game::exit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    return 0;
};
