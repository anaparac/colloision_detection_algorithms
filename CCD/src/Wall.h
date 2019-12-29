#ifndef WALL_H
#define WALL_H

#include "Shape.h"

class Wall : public Shape
{
    public:
        Wall(float x, float y, sf::Vector2f size, b2World &world);

        void draw(sf::RenderWindow &window);

    protected:

        sf::RectangleShape m_shape;
        sf::Color       m_color_spec;
    private:
};

#endif
