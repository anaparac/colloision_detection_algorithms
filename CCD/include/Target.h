#ifndef TARGET_H
#define TARGET_H

#include "Shape.h"

class Target : public Shape
{
    public:
        Target(float x, float y, sf::Vector2f size, b2World &world);

        void draw(sf::RenderWindow &window);

    protected:

        sf::Sprite              m_sprite;
        sf::Texture             m_texture;
    private:
};

#endif
