#include "map.h"
#include "testentity.h"
#include "sprite.h"

TestEntity::TestEntity(Map* map) : Entity(map)
{
    sprite = new Sprite(map->game()->sprite_batch(),
                        map->game()->content()->load_texture("block"));
}

void TestEntity::update()
{
    Entity::update();

    sprite->update();
}

void TestEntity::draw()
{
    Entity::draw();

    sprite->draw(m_position);
}

TestEntity::~TestEntity()
{
    delete sprite;
}
