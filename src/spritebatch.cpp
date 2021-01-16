#include <SDL2/SDL.h>
#include "game.h"
#include "rectangle.h"
#include "spritebatch.h"

SpriteBatch::SpriteBatch(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

void SpriteBatch::begin()
{

}

void SpriteBatch::draw(Texture* texture, Rectangle source, Rectangle destination)
{
    SDL_RenderCopy(renderer,
                   texture->get_sdl_texture(),
                   source.to_sdl_rect(),
                   destination.to_sdl_rect());
}

void SpriteBatch::end()
{

}

SpriteBatch::~SpriteBatch()
{

}
