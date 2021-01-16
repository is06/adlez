#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "contentloader.h"
#include "graphics.h"
#include "map.h"
#include "spritebatch.h"

class ContentLoader;
class Graphics;
class Map;
class SpriteBatch;

class Game
{
public:
    static void run();

    void quit();
    ContentLoader* content();
    SpriteBatch* sprite_batch();

private:
    Game();
    ~Game();

    void update();
    void draw();

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    ContentLoader* m_content;
    Graphics* m_graphics;
    Map* m_current_map;
    SpriteBatch* m_sprite_batch;

    bool running;
};

#endif // GAME_H
