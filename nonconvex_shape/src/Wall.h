#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <string>
#include <cstdlib>

class Wall
{
    public:
    float PPM = 64.f;
    float MPP = 0.015625f;
        Wall(float x, float y, sf::Vector2f size, b2World &world);

        void draw(sf::RenderWindow &window);


    protected:

        sf::Texture m_texture;
        b2Body*         m_body;
        sf::Vector2f    m_size;
        int             m_contacting;

    private:
};

#endif
