#include <SDL2/SDL.h>
#include "game.h"
#include "spritebatch.h"

SpriteBatch::SpriteBatch(SDL_Window* window)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void SpriteBatch::begin()
{

}

void SpriteBatch::draw(SDL_Texture *texture, SDL_Rect destination)
{
    SDL_RenderCopy(renderer, texture, nullptr, &destination);
}

void SpriteBatch::end()
{
    SDL_RenderPresent(renderer);
}

SpriteBatch::~SpriteBatch()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
}
