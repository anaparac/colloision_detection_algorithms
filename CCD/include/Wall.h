#ifndef WALL_H
#define WALL_H

#include "Shape.h"

class Wall : public Shape
{
    public:
        Wall(float x, float y, sf::Vector2f size, b2World &world);

        void draw(sf::RenderWindow &window);

    protected:

        sf::Sprite      m_sprite;
        sf::Texture     m_texture;
    private:
};

#endif
