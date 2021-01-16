#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include "size.h"

struct Size;

class Texture
{
public:
    Texture(SDL_Texture* sdl_texture);
    ~Texture();

    SDL_Texture* get_sdl_texture() const;

private:
    SDL_Texture* texture;
};

#endif // TEXTURE_H
