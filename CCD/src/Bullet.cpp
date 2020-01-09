#include "Bullet.h"

Bullet::Bullet(b2World &world, sf::Vector2f center)
{
    m_name = "Bullet";
    m_size = sf::Vector2f(15,15);
    m_radius = m_size.x / 2;



    // Create body Box2D
    b2CircleShape circleShape;
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;

    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = m_radius * MPP;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(center.x * MPP, center.y * MPP);


    //////////////////////////////////
    ///enable bullet mode to apply CCD      -> na pritisak neke tipke s tipkovnice
    //bodyDef.bullet = false;
    bodyDef.bullet = true;
    //////////////////////////////////



    m_body = world.CreateBody(&bodyDef);
    m_body->SetLinearVelocity(b2Vec2(10,0));    //bullet x-vel=10

    fixtureDef.shape = &circleShape;
    fixtureDef.friction = 1;
    fixtureDef.restitution	= 0;
    fixtureDef.density	= 0.7f;
    m_body->CreateFixture(&fixtureDef);

    //ucitaj texture

    m_texture.loadFromFile("flash1.png");
    m_body->SetUserData(this);

}

void Bullet::draw(sf::RenderWindow& window)
{
    if (m_body != NULL)
    {

        b2Vec2 position = m_body->GetPosition();
        float  angle = m_body->GetAngle();

        m_sprite.setTexture(m_texture);
        m_sprite.setScale((m_size.x / m_texture.getSize().x ),
                          (m_size.y / m_texture.getSize().y ));

        m_sprite.setPosition((position.x- m_size.x*MPP/2) * PPM , (position.y- m_size.y*MPP/2)*PPM);
        m_sprite.setRotation((angle * 180) / M_PI);


        window.draw(m_sprite);
    }
}
