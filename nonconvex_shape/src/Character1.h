#ifndef CHARACTER1_H
#define CHARACTER1_H
//BBox je samo jedan pravokutnik

#include "Player.h"

class Character1 : public Player
{
    public:
        Character1(float x, float y, b2World &world);

        void draw(sf::RenderWindow &window);
        int getCurrTexture();
        void setCurrTexture(int idx);


    protected:

        std::vector<sf::Texture>         m_texture;
        sf::Sprite                       m_sprite;
        int                              m_current_texture;
        b2Vec2                           m_scale;
    private:
};

#endif
