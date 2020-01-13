#include "Character2.h"

Character2::Character2(float x, float y, b2World &world)
{
    m_name = "Dino2";


    b2PolygonShape polygonShape;
    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x*MPP,y*MPP);

    m_body = world.CreateBody(&bodyDef);

    //prvi fix
    polygonShape.SetAsBox(50/2*MPP,40/2*MPP, b2Vec2( -15*MPP,-20*MPP),0);
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = 0;
    fixtureDef.restitution = 0;
    fixtureDef.friction = 1;
    m_body->CreateFixture(&fixtureDef);
    //drugi fix
    polygonShape.SetAsBox(60/2*MPP, 45/2*MPP, b2Vec2( -40*MPP,20*MPP), 0 );
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

void Character2::draw(sf::RenderWindow &window)
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
