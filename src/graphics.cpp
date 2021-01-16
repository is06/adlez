#include <SDL2/SDL.h>
#include "graphics.h"

Graphics::Graphics(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

void Graphics::clear_frame_buffer(SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

void Graphics::end_render()
{
    SDL_RenderPresent(renderer);
}

Graphics::~Graphics()
{
    SDL_DestroyRenderer(renderer);
}
