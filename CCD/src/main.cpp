#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "SFMLDebugDraw.h"
#include "Shape.h"
#include "Wall.h"
#include "Square.h"
#include "Bullet.h"
#include "Target.h"
#include "Character.h"

#include "ContactListener.h"

#include <iostream>
#include <ctime>
#include <typeinfo>
#include <vector>

#define TIMESTEP 1.0f/90.0f     // Refresh time
#define VELITER 8              // iterations per tick to calculate speed -> standardno 8
#define POSITER 3              // iterations to calculate the position -> standardno 3

#define WIDTH 800
#define HEIGHT 600



void createShape(std::vector<Shape* > &vectorShapes, b2World &world, int numberShape)
{
    if (numberShape < 1 || numberShape > 2)
        return;

    Shape*          shape;
    b2Body*         body;
    sf::Vector2f    position;
    b2Vec2          force;
    force = b2Vec2(0,0);

    //umjesto square kreirati target
    if(numberShape == 1){
        position.x = 800;
        position.y = 250;
        shape = static_cast<Square*>( new Square(world, position) );
    }
    //bullet
    else if(numberShape == 2){
        position.x = 50;
        position.y = 385;
        force.x =100, 0;
        shape = static_cast<Bullet*>( new Bullet(world, position) );
    }

    vectorShapes.push_back(shape);

    //add force to bullet
    body = vectorShapes.back()->getBody();
    body->ApplyForce(force, body->GetWorldCenter(), true);
}




void showInstructions()
{
    std::cout << std::endl << std::endl;

    std::cout << " INSTRUCTIONS             "            << std::endl << std::endl;

    std::cout << " Draw target       : Key 1"            << std::endl;

    std::cout << " Fire bullet       : Key space"        << std::endl << std::endl;

    //std::cout << " Debug draw        : Keys A, B, C";
}

int main()
{
    srand(time(0));

    // Instructions
    showInstructions();

    // Define world Box2D - Zero gravity
    b2World m_world(b2Vec2(0.f, 9.81f));

    std::vector<Shape* > m_vectorShapes;

    // Create walls - static bodies
    m_vectorShapes.push_back(new Wall(400.f, 600.f, sf::Vector2f(800.f, 15.f), m_world));
    m_vectorShapes.push_back(new Wall(600.f, 500.f, sf::Vector2f(15.f, 200.f), m_world));

    //character
    m_vectorShapes.push_back(new Character(50.f, 500.f, sf::Vector2f(60.f, 200.f), m_world));



    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow m_window(sf::VideoMode(800, 600), "Collision detection", sf::Style::Default, settings);
    m_window.setFramerateLimit(60);

    // Initialize Debug draw -> poveze s sfml dijelom za iscrtavanje
    SFMLDebugDraw debugDraw(m_window);
    m_world.SetDebugDraw(&debugDraw);

    //instantiate ContactListener
    //at global scope
    ContactListener ContactListenerInstance;
    m_world.SetContactListener(&ContactListenerInstance);

    // Set initial flags for what to draw
    debugDraw.SetFlags(b2Draw::e_shapeBit);

    while (m_window.isOpen())
    {

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
                if (event.key.code == sf::Keyboard::Space)
                    createShape(m_vectorShapes, m_world, 2);



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

        }

        // Update window
        m_window.clear(sf::Color::Transparent);

        // Update world Box2D
        m_world.Step(TIMESTEP, VELITER, POSITER);

        // Draw vector shapes
        for (int i = 0; i < m_vectorShapes.size(); i++)
            m_vectorShapes.at(i)->draw(m_window);

        // Debug draw display
        m_world.DrawDebugData();


        m_window.display();
    }

    return 0;
}

