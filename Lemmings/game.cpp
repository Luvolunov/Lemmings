#include "game.hpp"
#include "game-object.hpp"
#include "buttons.hpp"

const SDL_Color mainColor = { 0x48, 0x48, 0x48, 0xFF };
const SDL_Color secondColor = { 0xD0, 0xD0, 0xD0, 0xFF };
const SDL_Color blackColor = { 0x00, 0x00, 0x00, 0xFF };

void renderText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, const std::string &text, SDL_Rect rect) {
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    rect.w = surfaceMessage->w;
    rect.h = surfaceMessage->h;
    SDL_RenderCopy(renderer, message, NULL, &rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

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
    
    bigFont = TTF_OpenFont("assets/Roboto-Black.ttf", 60);
    smallFont = TTF_OpenFont("assets/Roboto-Black.ttf", 28);
    
    Button playB(renderer, "Play", smallFont, blackColor);
    Button exitB(renderer, "Exit", smallFont, blackColor);
    
    playButton = &playB;
    exitButton = &exitB;
    
    playButton->setCoords(50, 200);
    exitButton->setCoords(50, 260);

    return 0;
};

bool groundMatrix[SCREEN_WIDTH][SCREEN_HEIGHT];
int iteration = 0;
int soldiersCreated = 0;

void Game::handleClick(SDL_MouseButtonEvent &e) {
    printf("%d", true);
}

void Game::runGame() {
    SDL_SetRenderDrawColor(renderer, mainColor.r, mainColor.g, mainColor.b, mainColor.a);
    if (iteration % 40 == 0 && soldiersCreated < SOLDIERS_COUNT)
        soldiers[soldiersCreated++] = Soldier(renderer);
    
    for (int i = 0; i < soldiersCreated; ++i) {
        SDL_Rect box = soldiers[i].getBox();
        if (box.x + box.w > SCREEN_WIDTH) {
            soldiers[i].setDirection(left);
        } else if (box.x < 0) {
            soldiers[i].setDirection(right);
        }
        soldiers[i].action();
        soldiers[i].draw();
    }
}

void Game::runMainMenu() {
    SDL_SetRenderDrawColor(renderer, secondColor.r, secondColor.g, secondColor.b, secondColor.a);
    SDL_Rect message_rect;
    message_rect.x = SCREEN_WIDTH / 3.5;
    message_rect.y = 20;
    

    exitButton->draw();

    renderText(renderer, bigFont, mainColor, "Lemmings", message_rect);
}

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

int Game::exit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    return 0;
};
