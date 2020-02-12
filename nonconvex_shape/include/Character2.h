#ifndef CHARACTER2_H
#define CHARACTER2_H
//BBox consists of 1 rectangle and 1 circle

#include "Player.h"

class Character2 : public Player
{
    public:
        Character2(float x, float y, b2World &world);

        void draw(sf::RenderWindow &window);

    protected:

    private:
};

#endif
