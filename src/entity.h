#ifndef ENTITY_H
#define ENTITY_H

#include "map.h"

class Map;

class Entity
{
public:
    Entity(Map* map);
    virtual ~Entity();

    virtual void update();
    virtual void draw();

protected:
    Map* map;
};

#endif // ENTITY_H
