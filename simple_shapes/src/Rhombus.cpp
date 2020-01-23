#include "../include/Rhombus.h"

Rhombus::Rhombus(b2World &world, sf::Vector2f center)
{
    m_name = "Rhombus";
    m_size = sf::Vector2f(50.f, 100.f);
    float size = m_size.x ;

    m_color_spec = sf::Color::Green;
    m_shape.setPosition(center);
    // Create body Box2D
    b2PolygonShape polygonShape;
    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;

    b2Vec2 vertex[3];

    float size_b2 = size/2 * MPP;
    vertex[0].Set(0, -size_b2);
    vertex[1].Set(-size_b2, size_b2);
    vertex[2].Set(0, size_b2 * 3);
    vertex[3].Set(size_b2, size_b2);

    polygonShape.Set(vertex, 4);
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

void Rhombus::draw(sf::RenderWindow& window)
{
    if (m_body != NULL)
    {
        float angle = m_body->GetAngle();
        b2Vec2 position =  m_body->GetPosition();
        float size = m_size.x ;

        m_shape.setPosition(position.x * PPM, position.y * PPM);
        m_shape.setRotation((angle * 180) / M_PI);

        if(m_contacting){ m_color = sf::Color::Red; }
        else{ m_color = m_color_spec; }


        m_shape.setOrigin(size/2, size /2);
        m_shape.setPointCount(4);
        m_shape.setPoint( 0, sf::Vector2f(size/2, 0) );
        m_shape.setPoint( 1, sf::Vector2f(0, size) );
        m_shape.setPoint( 2, sf::Vector2f(size/2, size*2) );
        m_shape.setPoint( 3, sf::Vector2f(size, size) );
        m_shape.setFillColor(m_color);
        window.draw(m_shape);
    }
}
