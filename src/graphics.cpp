#include <SDL2/SDL.h>
#include "graphics.h"

Graphics::Graphics(SDL_Window* window)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Graphics::clearFrameBuffer(SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

void Graphics::endRender()
{
    SDL_RenderPresent(renderer);
}

Graphics::~Graphics()
{
    SDL_DestroyRenderer(renderer);
}
