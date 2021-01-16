#include "game.h"
#include "map.h"
#include "testentity.h"

Map::Map(Game* game)
{
    m_game = game;
    add_entity("test", new TestEntity(this));
}

void Map::update()
{
    for (auto entity : m_entities) {
        entity.second->update();
    }
}

void Map::draw()
{
    for (auto entity : m_entities) {
        entity.second->draw();
    }
}

void Map::add_entity(const string& name, Entity* entity)
{
    m_entities[name] = entity;
}

Entity* Map::entity(const string& name)
{
    return m_entities[name];
}

Game* Map::game()
{
    return m_game;
}

Map::~Map()
{
    for (auto entity : m_entities) {
        delete entity.second;
    }
}
