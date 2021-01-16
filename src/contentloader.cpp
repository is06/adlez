#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <png.h>
#include <stdio.h>
#include "contentloader.h"
#include "texture.h"

using namespace std;

ContentLoader::ContentLoader(SDL_Renderer* sdl_renderer)
{
    renderer = sdl_renderer;
}

Texture* ContentLoader::load_texture(const string& file_path) const
{
    SDL_Surface* sdl_surface = IMG_Load((file_path + ".png").c_str());
    if (sdl_surface == nullptr) {
        cerr << "Unable to find texture file '" << (file_path + ".png") << "'" << endl;
    }
    SDL_Texture* sdl_texture = SDL_CreateTextureFromSurface(renderer, sdl_surface);
    if (sdl_texture == nullptr) {
        cerr << "Unable to build texture from surface" << endl;
    }
    SDL_FreeSurface(sdl_surface);

    return new Texture(sdl_texture);
}
