#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "graphics.h"
#include "spritebatch.h"
#include "map.h"

class Map;

class Game
{
public:
    static void run();

    void quit();

private:
    Game();
    ~Game();

    void update();
    void draw();

    SDL_Window* window;
    Graphics* graphics;
    SpriteBatch* spriteBatch;
    Map* currentMap;

    bool running;
};

#endif // GAME_H
