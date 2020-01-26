#include "../include/Character.h"
#include <iostream>

Character::Character(float x, float y, sf::Vector2f size, b2World& world)
{
    // animacija
    m_animation = false;
    m_anim_time =sf::Time::Zero;
    m_total_time = sf::seconds(1); // ukupno vrijeme animacije

    m_name = "Character";
    m_size = size;
    m_current_texture = 0;
    m_color = sf::Color::Transparent;

    // Create static box2D  body
    b2PolygonShape polygonShape;
    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x * MPP, y * MPP);
    m_body = world.CreateBody(&bodyDef);

    polygonShape.SetAsBox( m_size.x/2 * MPP, m_size.y/2 * MPP);
    fixtureDef.shape = &polygonShape;

    m_body->SetUserData(this);
    m_body->CreateFixture(&fixtureDef);


    //ucitaj slike u vektor
    sf::Texture texture;
    texture.loadFromFile("green_fire_1.png");
    m_texture.push_back(texture);
    texture.loadFromFile("green_fire_2.png");
    m_texture.push_back(texture);
    texture.loadFromFile("green_fire_3.png");
    m_texture.push_back(texture);
    texture.loadFromFile("green_fire_4.png");
    m_texture.push_back(texture);
    texture.loadFromFile("green_fire_5.png");
    m_texture.push_back(texture);
    texture.loadFromFile("green_fire_6.png");
    m_texture.push_back(texture);

    // Za anmimaciju
    m_no_frames = m_texture.size();
    std::cout << "Broj sličica = " << m_no_frames << std::endl;
}
int Character::getCurrTexture(){
    return m_current_texture;
}
void Character::setCurrTexture(int idx){
    m_current_texture = idx;
}

// Započnimo animaciju.
void Character::startAnimation()
{
    m_current_texture = 0;
    m_anim_time =sf::Time::Zero;
    m_animation = true;
}

// Unutar animacije izvrti sličice dok animacija na završi.
bool Character::animate(sf::Time dt)
{
    if(!m_animation) return false;

    float DT = m_total_time.asSeconds()/(m_no_frames+1);
    //std::cout  << "DT = " << DT << "\n";
    m_anim_time += dt;
    int N = std::floor(m_anim_time.asSeconds()/DT);
//    std::cout  << "N = " << N << "\n";
    if(N == m_no_frames){
        m_current_texture = 0;
        m_animation = false;
        return true;
    }
    else{
        m_current_texture = N;
        return false;
    }

}

void Character::draw(sf::RenderWindow &window)
{
    if (m_body != NULL)
    {
        float angle = m_body->GetAngle();
        b2Vec2 position =  m_body->GetPosition();
        float diff;
        if(m_current_texture)
            diff = ((m_texture[m_current_texture].getSize().x - m_texture[ m_current_texture - 1 ].getSize().x ) / 2)*MPP;
        else diff = 0;


        position.x = ( position.x - diff*MPP);
        m_sprite.setTexture(m_texture[m_current_texture]);
        //scale texture to shape size
        m_sprite.setScale(m_size.y / m_texture[m_current_texture].getSize().y ,
                          (m_size.y / m_texture[m_current_texture].getSize().y ));

        //position connects sprite to body
        m_sprite.setPosition((m_body->GetPosition().x- m_size.x*MPP/2) * PPM , (m_body->GetPosition().y- m_size.y*MPP/2)*PPM);
        m_sprite.setRotation((angle * 180) / M_PI);


        window.draw(m_sprite);
    }
}
