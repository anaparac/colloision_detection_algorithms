#ifndef CHARACTER_H
#define CHARACTER_H

#include "Shape.h"

class Character : public Shape
{
    public:
        Character(float x, float y, sf::Vector2f size, b2World &world);

        void draw(sf::RenderWindow &window);
        int getCurrTexture();
        void setCurrTexture(int idx);
        // Podrška za animaciju
        void startAnimation();
        // Izvrši animaciju ako je pozvana metoda startAnimation()
        bool animate(sf::Time dt);
        bool is_in_animation() const {return m_animation;};

    protected:

        sf::Sprite                   m_sprite;
        std::vector<sf::Texture>     m_texture;     //vektor za slike
        int                          m_current_texture;

    private:
        // Vrijeme od početka animacije
        sf::Time m_anim_time;
        // Ukupno vrijeme animacije
        sf::Time m_total_time;
        // Jesmo li u animaciji
        bool m_animation;
        // Broj sličica
        int m_no_frames;
};

#endif
