#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "texture.h"

class Graphics
{
public:
    Graphics(SDL_Renderer* renderer);
    ~Graphics();

    void set_render_target(Texture* render_target);
    void clear_frame_buffer(SDL_Color color);
    void end_render();

private:
    SDL_Renderer* m_renderer;
};

#endif // GRAPHICS_H
