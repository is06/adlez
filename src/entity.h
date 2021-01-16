#ifndef ENTITY_H
#define ENTITY_H

#include "map.h"
#include "point.h"

class Map;

class Entity
{
public:
    Entity(Map* map);
    virtual ~Entity();

    virtual void update();
    virtual void draw();

    void set_position(Point position);

protected:
    Map* m_map;
    Point m_position;
};

#endif // ENTITY_H
