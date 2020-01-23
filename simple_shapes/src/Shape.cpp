#include "../include/Shape.h"

Shape::Shape()
{
    m_name = "Shape";

    // Size shape
    m_size = sf::Vector2f(50.f, 50.0f);
    m_contacting = 0;

}
void Shape::draw(sf::RenderWindow &window)
{

}

b2Body* Shape::getBody()
{
    return m_body;
}

void Shape::setBody(b2Body* body)
{
    m_body = body;
}

std::string Shape::getName()
{
    return m_name;
}

void Shape::startContact(){ m_contacting ++; }

void Shape::endContact(){ m_contacting --; }
