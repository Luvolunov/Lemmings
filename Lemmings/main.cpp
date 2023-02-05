#include <iostream>
#include "game.hpp"

int main(int argc, char* args[]) {
    Game game;
    if (game.init(SCREEN_WIDTH, SCREEN_HEIGHT) != 0) {
        return 1;
    };

    SDL_Event e;
    while(!game.quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    game.quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    game.handleClick(e.button);
                    break;
                default:
                    break;
            }
                
        }
        if (game.iterate() != 0) {
            return -1;
        }
    }

    game.exit();

    return 0;
}
