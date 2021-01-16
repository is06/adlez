#include "map.h"
#include "testentity.h"
#include "sprite.h"

TestEntity::TestEntity(Map* map) : Entity(map)
{
    auto texture = map->game()->content()->load_texture("block");

    sprite = new Sprite(map->game()->sprite_batch(), texture);
}

void TestEntity::update()
{
    Entity::update();

    sprite->update();
}

void TestEntity::draw()
{
    Entity::draw();

    sprite->draw();
}

TestEntity::~TestEntity()
{
    delete sprite;
}
