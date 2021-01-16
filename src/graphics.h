#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

class Graphics
{
public:
    Graphics(SDL_Renderer* renderer);
    ~Graphics();

    void clear_frame_buffer(SDL_Color color);
    void end_render();

private:
    SDL_Renderer* renderer;
};

#endif // GRAPHICS_H
