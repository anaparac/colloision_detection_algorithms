#ifndef SHAPE_H
#define SHAPE_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <string>


class Shape
{
    public:
        float PPM = 64.f;
        float MPP = 0.015625f;

        Shape();

        virtual void draw(sf::RenderWindow &window);

        void    setBody(b2Body* body);

        b2Body* getBody();

        std::string  getName();
        void startContact();
        void endContact();


    protected:

        std::string     m_name;
        sf::Color       m_color;
        b2Body*         m_body;
        sf::Vector2f    m_size;
        int             m_contacting;


    private:
};

#endif // SHAPE_H
