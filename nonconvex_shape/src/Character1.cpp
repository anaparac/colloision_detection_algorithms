#include "../include/Character1.h"


Character1::Character1(float x, float y,  b2World &world)
{
    m_name = "Dino1";


    b2PolygonShape polygonShape;
    b2CircleShape  circleShape;
    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x*MPP,y*MPP);

    m_body = world.CreateBody(&bodyDef);


    //head
    circleShape.m_p = b2Vec2(-15*MPP,-25*MPP);
    circleShape.m_radius =  45/2*MPP;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 0;
    fixtureDef.restitution = 0;
    fixtureDef.friction = 1;
    m_body->CreateFixture(&fixtureDef);

    //fixture 2
    polygonShape.SetAsBox(40/2*MPP, 15/2*MPP, b2Vec2( -55*MPP,15*MPP), (-50*180)/M_PI );
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = 0;
    fixtureDef.restitution = 0;
    fixtureDef.friction = 1;
    m_body->CreateFixture(&fixtureDef);
    //fixture 3
    polygonShape.SetAsBox( 40/2*MPP, 10/2*MPP, b2Vec2( -25*MPP,35*MPP), 0 );
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = 0;
    fixtureDef.restitution = 0;
    fixtureDef.friction = 1;
    m_body->CreateFixture(&fixtureDef);
    //fixture 4
    circleShape.m_p = b2Vec2(-30*MPP,15*MPP);
    circleShape.m_radius =  40/2*MPP;
    fixtureDef.shape = &circleShape;
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


void Character1::draw(sf::RenderWindow &window)
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
