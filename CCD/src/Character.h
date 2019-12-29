#ifndef CHARACTER_H
#define CHARACTER_H

#include "Shape.h"

class Character : public Shape
{
    public:
        Character(float x, float y, sf::Vector2f size, b2World &world);

        void draw(sf::RenderWindow &window);

    protected:

        sf::RectangleShape m_shape;
        sf::Sprite         sprite;  //lovac/kauboj
    private:
};

#endif
