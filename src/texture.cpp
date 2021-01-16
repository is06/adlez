#include <SDL2/SDL.h>
#include "size.h"
#include "texture.h"

Texture::Texture(SDL_Texture* sdl_texture)
{
    texture = sdl_texture;
}

SDL_Texture* Texture::get_sdl_texture() const
{
    return texture;
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
}
