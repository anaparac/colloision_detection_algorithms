#include "../include/Triangle.h"

Triangle::Triangle(b2World &world, sf::Vector2f center)
{
    m_name = "Triangle";

    m_color_spec = sf::Color::Magenta;

    m_shape.setPosition(center);
    m_shape.setOrigin(m_size.x /2, m_size.y /2);
    m_shape.setPointCount(3);
    m_shape.setPoint( 0, sf::Vector2f(m_size.x/2, 0) );
    m_shape.setPoint( 1, sf::Vector2f(0, m_size.x) );
    m_shape.setPoint( 2, sf::Vector2f(m_size.x, m_size.x) );

    // Create body Box2D
    b2PolygonShape polygonShape;
    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;

    b2Vec2 vertex[3];

    float size = (m_size.x / 2) * MPP;
    vertex[0].Set(0, -size);
    vertex[1].Set(-size, size);
    vertex[2].Set(size, size);

    polygonShape.Set(vertex, 3);
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(center.x * MPP, center.y * MPP);
    m_body = world.CreateBody(&bodyDef);

    fixtureDef.shape = &polygonShape;
    fixtureDef.friction = 0.5;
    fixtureDef.restitution	= 0.4;
    fixtureDef.density	= 1.f;

    m_body->SetUserData(this);
    m_body->CreateFixture(&fixtureDef);

}

void Triangle::draw(sf::RenderWindow& window)
{
    if (m_body != NULL)
    {
        float angle = m_body->GetAngle();
        b2Vec2 position =  m_body->GetPosition();

        m_shape.setPosition(position.x * PPM, position.y * PPM);
        m_shape.setRotation((angle * 180) / M_PI);

        if(m_contacting){ m_color = sf::Color::Red; }
        else{ m_color = m_color_spec; }

        m_shape.setFillColor(m_color);
        window.draw(m_shape);
    }
}
