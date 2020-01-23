#include "../include/Square.h"

Square::Square(b2World &world, sf::Vector2f center)
{
    m_name = "Square";

    m_color_spec = sf::Color::Blue;

    // Create body Box2D
    b2PolygonShape polygonShape;
    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(center.x * MPP, center.y * MPP);

    m_body = world.CreateBody(&bodyDef);

    polygonShape.SetAsBox( m_size.x/2 * MPP, m_size.y/2 * MPP);

    fixtureDef.shape = &polygonShape;
    fixtureDef.friction = 0.5;
    fixtureDef.restitution	= 0.4;
    fixtureDef.density	= 1.f;


    m_body->SetUserData(this);
    m_body->CreateFixture(&fixtureDef);


}

void Square::draw(sf::RenderWindow &window)
{
    if (m_body != NULL)
    {
        float angle = m_body->GetAngle();
        b2Vec2 position =  m_body->GetPosition();

        m_shape.setPosition(position.x * PPM, position.y * PPM);
        m_shape.setRotation((angle * 180) / M_PI);

        if(m_contacting){ m_color = sf::Color::Red; }
        else{ m_color = m_color_spec; }

        m_shape.setSize(m_size);
        m_shape.setOrigin(m_size.x/2, m_size.y/2);
        m_shape.setFillColor(m_color);
        window.draw(m_shape);
    }
}
