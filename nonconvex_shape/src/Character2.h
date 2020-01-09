#ifndef CHARACTER2_H
#define CHARACTER2_H
//BBox je sastavljen od 2 pravokutnika ili pravokutnika i kruga

#include "Shape.h"

class Character2 : public Shape
{
    public:
        Character2(float x, float y, sf::Vector2f size, b2World &world);

        void draw(sf::RenderWindow &window);

    protected:

        //sf::RectangleShape  m_shape;
        sf::Texture         m_texture;
    private:
};

#endif
