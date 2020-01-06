#ifndef BULLET_H
#define BULLET_H

#include "Shape.h"

class Bullet : public Shape
{
    public:
        Bullet(b2World &world, sf::Vector2f center);

        void draw(sf::RenderWindow &window);

    protected:
        float           m_radius;
        sf::CircleShape m_shape;
        sf::Sprite      m_sprite;
        sf::Texture     m_texture;

    private:
};

#endif
