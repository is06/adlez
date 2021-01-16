#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <SDL2/SDL.h>
#include "game.h"

class SpriteBatch
{
public:
    SpriteBatch(SDL_Window* window);
    ~SpriteBatch();

    void begin();
    void draw(SDL_Texture *texture, SDL_Rect destination);
    void end();

private:
    SDL_Renderer* renderer;
};

#endif // SPRITEBATCH_H
