#ifndef SIZE_H
#define SIZE_H

struct Size
{
    int width = 0;
    int height = 0;

    Size()
    {

    }
    Size(int w, int h)
    {
        width = w;
        height = h;
    }
};

#endif // SIZE_H
