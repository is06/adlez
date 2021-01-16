#include <SDL2/SDL.h>
#include "graphics.h"

Graphics::Graphics(SDL_Renderer* renderer)
{
    m_renderer = renderer;
}

void Graphics::set_render_target(Texture* render_target)
{
    if (render_target != nullptr) {
        SDL_SetRenderTarget(m_renderer, render_target->get_sdl_texture());
    } else {
        SDL_SetRenderTarget(m_renderer, nullptr);
    }
}

void Graphics::clear_frame_buffer(SDL_Color color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_renderer);
}

void Graphics::end_render()
{
    SDL_RenderPresent(m_renderer);
}

Graphics::~Graphics()
{
    SDL_DestroyRenderer(m_renderer);
}
