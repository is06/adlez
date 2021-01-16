#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL2/SDL.h>
#include "point.h"
#include "size.h"

struct Rectangle
{
    Point position;
    Size size;

    Rectangle();
    Rectangle(int x, int y, int width, int height)
    {
        position.x = x;
        position.y = y;
        size.width = width;
        size.height = height;
    }
    Rectangle(Point position, Size size)
    {
        this->position = position;
        this->size = size;
    }

    inline bool contains(Point point)
    {
        return (point.x >= left() && point.x <= right() && point.y >= top() && point.y <= bottom());
    }
    inline bool intersects(Rectangle rectangle)
    {
        return (left() < rectangle.right() && right() >= rectangle.left() && top() <= rectangle.bottom() && bottom() >= rectangle.top());
    }
    inline int left()
    {
        return position.x;
    }
    inline int right()
    {
        return position.x + size.width;
    }
    inline int top()
    {
        return position.y;
    }
    inline int bottom()
    {
        return position.y + size.height;
    }
    const SDL_Rect* to_sdl_rect() const
    {
        auto rect = new SDL_Rect();
        rect->x = position.x;
        rect->y = position.y;
        rect->w = size.width;
        rect->h = size.height;
        return rect;
    }
};

#endif // RECTANGLE_H
