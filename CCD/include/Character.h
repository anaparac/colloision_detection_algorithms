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
        
        void startAnimation();
        // do the animation if startAnimation() is called
        bool animate(sf::Time dt);
        bool is_in_animation() const {return m_animation;};

    protected:

        sf::Sprite                   m_sprite;
        std::vector<sf::Texture>     m_texture;     
        int                          m_current_texture;

    private:
        // start time (animation)
        sf::Time m_anim_time;
        // complete animation time (to render all frames)
        sf::Time m_total_time;
        
        bool m_animation;
        //number of images
        int m_no_frames;
};

#endif
