#ifndef CHARACTER_H
#define CHARACTER_H

#include "Shape.h"

class Character : public Shape
{
    public:
        Character(float x, float y, sf::Vector2f size, b2World &world);

        void draw(sf::RenderWindow &window);
        int getCurrTexture();
        void setCurrTexture(int idx);

    protected:

        sf::RectangleShape           m_shape;
        sf::Sprite                   m_sprite;
        std::vector<sf::Texture>     m_texture;     //vektor za slike
        int                          m_current_texture;

    private:
};

#endif
