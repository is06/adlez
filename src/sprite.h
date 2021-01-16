#ifndef SPRITE_H
#define SPRITE_H

#include "spritebatch.h"
#include "texture.h"

class SpriteBatch;
class Texture;

class Sprite
{
public:
    Sprite(SpriteBatch* sprite_batch, Texture* texture);

    void update();
    void draw(Point position);

private:
    SpriteBatch* m_sprite_batch;
    Texture* m_texture;
};

#endif // SPRITE_H
