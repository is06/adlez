#include "point.h"
#include "size.h"
#include "sprite.h"
#include "spritebatch.h"
#include "texture.h"

Sprite::Sprite(SpriteBatch* sprite_batch, Texture* texture)
{
    m_sprite_batch = sprite_batch;
    m_texture = texture;
}

void Sprite::update()
{

}

void Sprite::draw(Point position)
{
    m_sprite_batch->begin();
    m_sprite_batch->draw(m_texture,
                         Rectangle(Point(0, 0), Size(16, 16)),
                         Rectangle(position, Size(16, 16)));
    m_sprite_batch->end();
}
