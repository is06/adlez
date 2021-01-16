#ifndef MAP_H
#define MAP_H

#include <map>
#include <string>
#include "entity.h"
#include "game.h"

class Entity;
class Game;

class Map
{
public:
    Map(Game* game);
    virtual ~Map();

    virtual void update();
    virtual void draw();

    void add_entity(const string& name, Entity* entity);
    Game* game();

protected:
    Entity* entity(const string& name);

private:
    std::map<std::string, Entity*> m_entities;
    Game* m_game;
};

#endif // MAP_H
