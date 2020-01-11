#include "Character3.h"

Character3::Character3(float x, float y, b2World &world)
{
    m_name = "Dino3";
    m_size = sf::Vector2f(150.f, 100.0f);
    m_current_texture = 0;

    b2PolygonShape polygonShape;
    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x*MPP,y*MPP);

    m_body = world.CreateBody(&bodyDef);

    polygonShape.SetAsBox(45*MPP,40*MPP, b2Vec2( -30*MPP,0*MPP),0);
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = 0;
    fixtureDef.restitution = 0;
    fixtureDef.friction = 1;
    m_body->CreateFixture(&fixtureDef);

    sf::Texture t;
    for(int i = 1; i<=10; ++i){
        t.loadFromFile("Idle"+std::to_string(i)+".png");
        m_texture.push_back(t);

    }

}

void Character3::draw(sf::RenderWindow &window)
{
    if (m_body != NULL)
       {

           b2Vec2 position = m_body->GetPosition();
           float  angle = m_body->GetAngle();

           m_sprite.setTexture(m_texture[m_current_texture]);
           m_sprite.setScale((m_size.x / m_texture[m_current_texture].getSize().x ),
                             (m_size.y / m_texture[m_current_texture].getSize().y ));

           m_sprite.setPosition((position.x- m_size.x*MPP/2) * PPM , (position.y- m_size.y*MPP/2)*PPM);
           m_sprite.setRotation((angle * 180) / M_PI);

           window.draw(m_sprite);


       }

}
