#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

class Graphics
{
public:
    Graphics(SDL_Window* window);
    ~Graphics();

    void clearFrameBuffer(SDL_Color color);
    void endRender();

private:
    SDL_Renderer* renderer;
};

#endif // GRAPHICS_H
