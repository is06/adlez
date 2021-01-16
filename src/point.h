#ifndef POINT_H
#define POINT_H

struct Point
{
    int x = 0;
    int y = 0;

    Point()
    {

    }
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

#endif // POINT_H
