#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <SDL2/SDL.h>
#include "game.h"
#include "rectangle.h"
#include "texture.h"

struct Rectangle;
class Texture;

class SpriteBatch
{
public:
    SpriteBatch(SDL_Renderer* renderer);
    ~SpriteBatch();

    void begin();
    void draw(Texture* texture, Rectangle source, Rectangle destination);
    void end();

private:
    SDL_Renderer* renderer;
};

#endif // SPRITEBATCH_H
