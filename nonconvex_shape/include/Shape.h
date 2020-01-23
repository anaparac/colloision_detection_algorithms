#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <string>
#include <cstdlib>

class Player
{
    public:
        float PPM = 64.f;
        float MPP = 0.015625f;

        Player();

        virtual void draw(sf::RenderWindow &window);

        void        setBody(b2Body* body);
        b2Body*     getBody();
        std::string getName();
        int         getCurrTexture();
        void        setCurrTexture(int idx);


    protected:

        std::string     m_name;
        sf::Color       m_color;
        b2Body*         m_body;
        sf::Vector2f    m_size;
        int                              m_contacting;
        std::vector<sf::Texture>         m_texture;
        sf::Sprite                       m_sprite;
        int                              m_current_texture;

    private:
};

#endif
