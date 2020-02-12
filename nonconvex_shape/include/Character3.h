#ifndef CHARACTER3_H
#define CHARACTER3_H
//Bbox is one rectangle
#include "Player.h"

class Character3 : public Player
{
    public:
        Character3(float x, float y, b2World &world);
        void draw(sf::RenderWindow &window);

    protected:

    private:
};

#endif
