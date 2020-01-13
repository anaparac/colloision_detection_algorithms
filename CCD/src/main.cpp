#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "SFMLDebugDraw.h"
#include "Shape.h"
#include "Wall.h"
#include "Bullet.h"
#include "Target.h"
#include "Character.h"


#include <iostream>
#include <vector>

#define TIMESTEP 1.0f/60.0f     // Refresh time
#define VELITER 8              // iterations per tick to calculate speed -> standardno 8
#define POSITER 3              // iterations to calculate the position -> standardno 3

#define WIDTH 800
#define HEIGHT 600



void createShape(std::vector<Shape* > &vectorShapes, b2World &world, int numberShape)
{

    Shape*          shape;
    sf::Vector2f    position;

    if(numberShape == 1){
        position.x = 600;
        position.y = 300;
        shape = static_cast<Target*>( new Target(position.x,position.y, sf::Vector2f(20,50), world) );
    }
    //bullet
    else if(numberShape == 2){
        position.x = 150;
        position.y = 510;
        shape = static_cast<Bullet*>( new Bullet(world, position) );
    }

    vectorShapes.push_back(shape);
}


void showInstructions()
{
    std::cout << std::endl << std::endl;
    std::cout << " INSTRUCTIONS             "            << std::endl << std::endl;
    std::cout << " Draw target       : Key 1"            << std::endl;
    std::cout << " Fire bullet       : Key space"        << std::endl << std::endl;
    std::cout << " Shapes            : Keys A"<< std::endl;
    std::cout << " AABB              : Keys B"<< std::endl;
}

int main()
{
    sf::Clock clock;
    sf::Time prevTime = clock.getElapsedTime();
    std::vector<Shape* > m_vectorShapes;


    showInstructions();

    //background
    sf::Texture tex;
    tex.loadFromFile("background.png");
    sf::Sprite BGsprite;
    BGsprite.setTexture(tex);
    BGsprite.setScale(0.56,0.56);

    b2World m_world(b2Vec2(0.f, 9.81f));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow m_window(sf::VideoMode(800, 600), "Collision detection", sf::Style::Default, settings);
    m_window.setFramerateLimit(30);

    SFMLDebugDraw debugDraw(m_window);
    m_world.SetDebugDraw(&debugDraw);



    // Create walls - static bodies
    m_vectorShapes.push_back(new Wall(400.f, 600.f, sf::Vector2f(800.f, 1.f), m_world));
    m_vectorShapes.push_back(new Wall(600.f, 620.f, sf::Vector2f(110.f,165.f), m_world));

    //character
    Character* character = new Character(80.f, 500.f, sf::Vector2f(120.f, 200.f), m_world);
    m_vectorShapes.push_back(character);



    //flags for animation
    int prepare_shoot = 1;
    int animate = 0;
    int shoot = 0;
    const float timePerFrame = 1.0 / 0.07;   //textures per millisecond
    sf::Time elapsedTime;

    while (m_window.isOpen())
    {

        elapsedTime = clock.getElapsedTime() - prevTime;
        prevTime = prevTime + elapsedTime;

        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if ( event.type == sf::Event::KeyReleased )
            {
                // Kreiraj dinamicnu metu
                if (event.key.code == sf::Keyboard::Num1)
                    createShape(m_vectorShapes, m_world, 1);

                if (event.key.code == sf::Keyboard::Space){
                    animate = 1;
                }



                // Debug draw shapes
                if(event.key.code == sf::Keyboard::A)
                {
                    if(debugDraw.GetFlags() & b2Draw::e_shapeBit) debugDraw.ClearFlags(b2Draw::e_shapeBit);
                    else debugDraw.AppendFlags(b2Draw::e_shapeBit);
                }
                //aabb
                if(event.key.code == sf::Keyboard::B)
                {
                    if(debugDraw.GetFlags() & b2Draw::e_aabbBit) debugDraw.ClearFlags(b2Draw::e_aabbBit);
                    else debugDraw.AppendFlags(b2Draw::e_aabbBit);
                }

            }


            //update animation
            if(animate){

                if(prepare_shoot){

                    if(elapsedTime.asMilliseconds()>=timePerFrame){
                        character->setCurrTexture( character->getCurrTexture() + 1 );
                        elapsedTime = clock.restart();
                    }
                    if(character->getCurrTexture()  == 5)    {prepare_shoot = 0; shoot = 1;}
                }

                if(shoot){ createShape(m_vectorShapes, m_world, 2); shoot = 0; }

                if(!prepare_shoot){
                    if(elapsedTime.asMilliseconds()>=timePerFrame){
                        character->setCurrTexture( character->getCurrTexture() - 1 );
                        elapsedTime = clock.restart();
                    }
                    if(character->getCurrTexture()  == 0)    {prepare_shoot = 1; animate = 0;}
                }
            }


        }

        // Update window
        m_window.clear(sf::Color::Transparent);


        // Update world Box2D
        m_world.Step(TIMESTEP, VELITER, POSITER);

        m_window.draw(BGsprite);
        // Draw vector shapes
        for (int i = 0; i < m_vectorShapes.size(); i++)
            m_vectorShapes.at(i)->draw(m_window);

        // draw shapes
        m_world.DrawDebugData();


        m_window.display();
    }

    return 0;
}

