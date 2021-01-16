#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include <string>
#include "entity.h"
#include "game.h"

using namespace std;

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
    unordered_map<string, Entity*> m_entities;
    Game* m_game;
};

#endif // MAP_H
