#include "entity.h"
#include "point.h"

Entity::Entity(Map* map) : m_position(Point(0, 0))
{
    m_map = map;
}

void Entity::update()
{

}

void Entity::draw()
{

}

void Entity::set_position(Point position)
{
    m_position = position;
}

Entity::~Entity()
{

}
