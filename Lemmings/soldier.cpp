#include "soldier.hpp"
// Метод загружающий изображение по переданному ему рендереру и пути
// И возвращающий готовую текстуру
SDL_Texture* loadImage(SDL_Renderer *ren, const char *file) {
    SDL_Surface *imageSurface = IMG_Load(file);
    SDL_Texture *image = SDL_CreateTextureFromSurface(ren, imageSurface);
    SDL_FreeSurface(imageSurface);
    return image;
}

Soldier::Soldier(SDL_Renderer *ren) {
    renderer = ren;
    SDL_Rect soldierBox;
    soldierBox = { 0, 0, 16, 32 };
    
    runTexture = loadImage(ren, runSprite);
    flyTexture = loadImage(ren, flySprite);
    digDownTexture = loadImage(ren, digDownSprite);
    digToDirectionTexture = loadImage(ren, digToDirectionSprite);
    blockTexture = loadImage(ren, blockSprite);
    
    soldier = GameObject();
    soldier.renderer = ren;
    soldier.box = soldierBox;
    soldier.spritesCount = 4;
    soldier.image = runTexture;
    soldier.setAnimationDelay(125);
    
    
    direction = right;
}
// Метод для установки направления движения солдата
void Soldier::setDirection(GameObjectDirection dir) {
    direction = dir;
    soldier.flipped = dir == left;
}
// Метод для получения текущего направления
GameObjectDirection Soldier::getDirection() {
    return direction;
}
// Метод, принимающий в себя объект SDL_Rect и матрицу с "землёй"
// Возвращает true в случае, если внизу объекта есть хотя бы 1 заполненный пиксель
bool checkIsGroundDown(SDL_Rect box, bool matrix[SCREEN_WIDTH][SCREEN_HEIGHT]) {
    for (int i = 0; i < box.w; ++i) {
        if (matrix[box.x + i][box.y + box.h]) {
            return true;
        }
    }
    return false;
}
// Метод, принимающий в себя объект SDL_Rect и матрицу с "землёй"
// Возвращает true в случае, если слева объекта есть хотя бы 1 заполненный пиксель
bool checkIsGroundLeft(SDL_Rect box, bool matrix[SCREEN_WIDTH][SCREEN_HEIGHT]) {
    for (int i = 0; i < box.h; ++i) {
        if (matrix[box.x][box.y + i]) {
            return true;
        }
    }
    return false;
}
// Метод, принимающий в себя объект SDL_Rect и матрицу с "землёй"
// Возвращает true в случае, если справа объекта есть хотя бы 1 заполненный пиксель
bool checkIsGroundRight(SDL_Rect box, bool matrix[SCREEN_WIDTH][SCREEN_HEIGHT]) {
    for (int i = 0; i < box.h; ++i) {
        if (matrix[box.x + box.w][box.y + i]) {
            return true;
        }
    }
    return false;
}

// Метод, с помощью которого солдат совершает действие
// Внутри описана логика разного рода действий в зависимости от текущего режима солдата (mode)
void Soldier::action(int iteration, bool matrix[SCREEN_WIDTH][SCREEN_HEIGHT], Soldier soldiers[SOLDIERS_COUNT]) {
    if (gone) { return; }
    SDL_Rect box = soldier.box;
    bool isNotRightGround = !matrix[box.x + box.w][box.y] || box.x + box.w >= SCREEN_WIDTH;
    bool isNotLeftGround = !matrix[box.x - 1][box.y] || box.x <= 0;
    switch (mode) {
        case run:
            if (!checkIsGroundDown(box, matrix) && box.y + box.h < SCREEN_HEIGHT_WITHOUT_MENU) {
                setMode(fly);
                break;
            }
            if (box.x + box.w > SCREEN_WIDTH || checkIsGroundRight(box, matrix)) {
                setDirection(left);
            } else if (box.x < 0 || checkIsGroundLeft(box, matrix)) {
                setDirection(right);
            }
            for (int i = 0; i < SOLDIERS_COUNT; ++i) {
                if (soldiers[i].getMode() == block) {
                    SDL_Rect anotherBox = soldiers[i].getBox();
                    if (direction == right && box.x + box.w >= anotherBox.x && box.x < anotherBox.x && box.y == anotherBox.y) {
                        setDirection(left);
                    } else if (direction == left && box.x <= anotherBox.x + anotherBox.w && box.x > anotherBox.x && box.y == anotherBox.y) {
                        setDirection(right);
                    }
                }
            }
            soldier.move(direction, 1);
            break;
        case fly:
            if ((checkIsGroundDown(box, matrix) || box.y + box.h >= SCREEN_HEIGHT_WITHOUT_MENU)) {
                setMode(run);
                break;
            }
            soldier.move(bottom, 1);
            break;
        case digDown:
            if (!checkIsGroundDown(box, matrix) || box.y + box.h >= SCREEN_HEIGHT_WITHOUT_MENU) {
                setMode(run);
                break;
            }
            if (iteration % 10 == 0) {
                for (int i = 0; i < box.w; ++i) {
                    matrix[box.x + i][box.y + box.h] = false;
                }
                soldier.move(bottom, 1);
            }
            break;
        case digToDirection:
            if (iteration % 200 == 0 && ((direction == right && isNotRightGround) || (direction == left && isNotLeftGround))) {
                setMode(run);
                break;
            }
            if (iteration % 10 == 0) {
                for (int i = 0; i < box.h; ++i) {
                    if (direction == right) {
                        matrix[box.x + box.w][box.y + i] = false;
                    } else if (direction == left) {
                        matrix[box.x - 1][box.y + i] = false;
                    }
                }
                soldier.move(direction, 1);
            }
            break;
        default:
            break;
    }
}
// Метод отрисовки солдата
// Если солдат покинул карту, то его не отрисовываем
void Soldier::draw() {
    if (gone) { return; }
    soldier.draw();
}
// Метод для установки режима солдата, а также смены отрисовываемой текстуры
void Soldier::setMode(SoldierMode soldierMode = run) {
    mode = soldierMode;
    switch (mode) {
        case run:
            soldier.image = runTexture;
            break;
        case fly:
            soldier.image = flyTexture;
            break;
        case digDown:
            soldier.image = digDownTexture;
            break;
        case digToDirection:
            soldier.image = digToDirectionTexture;
            break;
        case block:
            soldier.image = blockTexture;
            break;
        default:
            break;
    }
}
// Метод для получения текущего режима
SoldierMode Soldier::getMode() {
    return mode;
}
// Метод для получения геометрии солдата (x, y, ширина, высота)
SDL_Rect Soldier::getBox() {
    return soldier.box;
}
