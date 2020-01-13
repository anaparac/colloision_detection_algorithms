#include "Player.h"

Player::Player(){
    // Size shape
    m_size = sf::Vector2f(150.f, 100.0f);
    m_current_texture = 0;
    m_contacting = 0;
    m_size = sf::Vector2f(150.f, 100.0f);
    m_current_texture = 0;

}
void Player::draw(sf::RenderWindow &window){

}

b2Body* Player::getBody(){
    return m_body;
}

void Player::setBody(b2Body* body){
    m_body = body;
}

std::string Player::getName(){
    return m_name;
}

int Player::getCurrTexture(){
    return m_current_texture;
}
void Player::setCurrTexture(int idx){
    m_current_texture = idx;
}
