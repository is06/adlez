#ifndef CONTENTLOADER_H
#define CONTENTLOADER_H

#include <SDL2/SDL.h>
#include <string>
#include "texture.h"

using namespace std;

class Texture;

class ContentLoader
{
public:
    ContentLoader(SDL_Renderer* sdl_renderer);

    Texture* load_texture(const string& file_path) const;

private:
    SDL_Renderer* renderer;
};

#endif // CONTENTLOADER_H
