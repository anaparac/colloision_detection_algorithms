#include "../include/Wall.h"

Wall::Wall(float x, float y, sf::Vector2f size, b2World& world)
{
    m_name = "Wall";
    m_size = size;
    m_color = sf::Color::Transparent;

    // Create body static box2D
    b2PolygonShape polygonShape;
    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x * MPP, y * MPP);
    m_body = world.CreateBody(&bodyDef);

    polygonShape.SetAsBox( m_size.x/2 * MPP, m_size.y/2 * MPP);
    fixtureDef.shape = &polygonShape;

    m_body->CreateFixture(&fixtureDef);

    m_texture.loadFromFile("rock.png");

}

void Wall::draw(sf::RenderWindow &window)
{
    if (m_body != NULL)
    {
        float angle = m_body->GetAngle();
        b2Vec2 position =  m_body->GetPosition();

        m_sprite.setTexture(m_texture);
        m_sprite.setScale((m_size.x / m_texture.getSize().x ),
                          (m_size.y / m_texture.getSize().y ));

        m_sprite.setPosition((position.x- m_size.x*MPP/2) * PPM , (position.y- m_size.y*MPP/2)*PPM);
        m_sprite.setRotation((angle * 180) / M_PI);

        window.draw(m_sprite);
    }
}
