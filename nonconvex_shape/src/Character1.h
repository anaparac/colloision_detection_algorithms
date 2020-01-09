#ifndef CHARACTER1_H
#define CHARACTER1_H
//BBox je samo jedan pravokutnik

#include "Shape.h"

class Character1 : public Shape
{
    public:
        Character1(float x, float y, b2World &world);

        void draw(sf::RenderWindow &window);
        int getCurrTexture();
        void setCurrTexture(int idx);
        sf::Sprite setSpriteScale(b2Vec2 b);

    protected:

        std::vector<sf::Texture>         m_texture;
        sf::Sprite                       m_sprite;
        int                              m_current_texture;
        b2Vec2                           m_scale;
    private:
};

#endif
