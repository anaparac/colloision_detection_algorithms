#include "../include/Circle.h"

Circle::Circle(b2World &world, sf::Vector2f center)
{
    m_name = "Circle";
    m_radius = m_size.x / 2;

    m_color_spec = sf::Color::Yellow;

    // Create body Box2D
    b2CircleShape circleShape;
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;

    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = m_radius * MPP;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(center.x * MPP, center.y * MPP);
    m_body = world.CreateBody(&bodyDef);

    fixtureDef.shape = &circleShape;
    fixtureDef.friction = 0.5;
    fixtureDef.restitution	= 0.4;
    fixtureDef.density	= 1.f;

    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);

}

void Circle::draw(sf::RenderWindow& window)
{
    if (m_body != NULL)
    {

        b2Vec2 position = m_body->GetPosition();
        float  angle = m_body->GetAngle();

        if(m_contacting){ m_color = sf::Color::Red; }
        else{ m_color = m_color_spec; }


        m_shape.setOrigin(m_size.x / 2, m_size.y /2);
        m_shape.setRadius(m_radius);
        m_shape.setFillColor(m_color);
        m_shape.setPosition(position.x * PPM, position.y * PPM);
        m_shape.setRotation((angle * 180) / M_PI);

        window.draw(m_shape);
    }
}
