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

void Sprite::draw()
{
    m_sprite_batch->begin();
    m_sprite_batch->draw(m_texture,
                         Rectangle(0, 0, 16, 16),
                         Rectangle(0, 0, 16, 16));
    m_sprite_batch->end();
}
