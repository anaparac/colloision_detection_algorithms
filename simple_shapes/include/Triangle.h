#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape
{
    public:

        Triangle(b2World &world, sf::Vector2f center);

        void draw(sf::RenderWindow &window);

    protected:

        sf::ConvexShape m_shape;
        sf::Color       m_color_spec;
    private:
};

#endif // TRIANGLE_H
