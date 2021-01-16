#ifndef TESTENTITY_H
#define TESTENTITY_H

#include "entity.h"
#include "sprite.h"

class Entity;
class Sprite;

class TestEntity : public Entity
{
public:
    TestEntity(Map* map);
    ~TestEntity();

    void update() override;
    void draw() override;

private:
    Sprite* sprite;
};

#endif // TESTENTITY_H
