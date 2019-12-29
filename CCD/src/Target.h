#ifndef TARGET_H
#define TARGET_H

#include "Shape.h"

class Target : public Shape
{
    public:
        Target(float x, float y, sf::Vector2f size, b2World &world);

        void draw(sf::RenderWindow &window);

    protected:

        sf::RectangleShape m_shape;
        sf::Sprite         sprite;  //slika jabuke ili vaze
    private:
};

#endif
