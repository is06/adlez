#ifndef MAP_H
#define MAP_H

#include "game.h"

class Game;

class Map
{
public:
    Map(Game* game);
    virtual ~Map();

    virtual void update();
    virtual void draw();

private:
    Game* game;
};

#endif // MAP_H
