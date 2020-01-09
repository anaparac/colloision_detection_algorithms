#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "SFMLDebugDraw.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Character1.h"
#include "ContactListener.h"

#include <iostream>
#include <vector>

#define TIMESTEP 1.0f/60.0f     // Refresh time
#define VELITER 8              // iterations per tick to calculate speed -> standardno 8
#define POSITER 3              // iterations to calculate the position -> standardno 3

#define WIDTH 800
#define HEIGHT 600





void createShape(std::vector<Shape* > &vectorShapes, b2World &world, int numberShape)
{
    if (numberShape < 1 || numberShape > 4)
        return;

    Shape*          shape;
    b2Body*         body;
    sf::Vector2f    position;

    position.x = 50;
    position.y = 50;

    switch( numberShape )
    {


        case 2:
            shape = static_cast<Circle*>( new Circle(world, position) );
            break;



    }

    // Add shape -> mozda mogu ovo zamijeniti s iteriranjem po fixtureima i koristenjem userData
    vectorShapes.push_back(shape);

    // Initial move
    b2Vec2 force;
    force.x = 10;
    force.y = 10;

    body = vectorShapes.back()->getBody();
    body->ApplyForce(force, body->GetWorldCenter(), true);
}




void showInstructions()
{
    std::cout << std::endl << std::endl;

    std::cout << " INSTRUCTIONS             "            << std::endl << std::endl;
    std::cout << " Draw shape       : Keys A"<<std::endl;
    std::cout << " Draw aabb       : Keys B"<<std::endl;
}

int main()
{

    sf::Clock clock;
    sf::Time prevTime = clock.getElapsedTime();
    // Instructions
    showInstructions();

    std::vector<sf::Texture> BGtexture;
    sf::Texture tex;

    tex.loadFromFile("bg1.png");
    BGtexture.push_back(sf::Texture(tex));
    tex.loadFromFile("bg2.png");
    BGtexture.push_back(sf::Texture(tex));
    tex.loadFromFile("bg3.png");
    BGtexture.push_back(sf::Texture(tex));
    tex.loadFromFile("bg4.png");
    BGtexture.push_back(sf::Texture(tex));

    // Define world Box2D - Zero gravity
    b2World m_world(b2Vec2(0.f, 9.81f));

    //collection for polygons
    std::vector<Shape* > m_vectorShapes;

    // Create walls - static bodies
    m_vectorShapes.push_back(new Rectangle(600.f, 400.f, sf::Vector2f(120.f, 40.f), m_world));
    m_vectorShapes.push_back(new Rectangle(670.f, 450.f, sf::Vector2f(40.f, 120.f), m_world));

    m_vectorShapes.push_back(new Rectangle(500.f, 500.f, sf::Vector2f(120.f, 40.f), m_world));

    m_vectorShapes.push_back(new Rectangle(600.f, 600.f, sf::Vector2f(1200.f, 40.f), m_world));
    m_vectorShapes.push_back(new Rectangle(1.f, 300.f, sf::Vector2f(1.f, 1200.f), m_world));
    m_vectorShapes.push_back(new Rectangle(1200.f, 300.f, sf::Vector2f(1.f, 1200.f), m_world));
    Character1* ch1 = new Character1(100,100, m_world);
    m_vectorShapes.push_back(ch1);


    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow m_window(sf::VideoMode(1200, 600), "Collision detection", sf::Style::Default, settings);
    m_window.setFramerateLimit(60);

    // Initialize Debug draw -> poveze s sfml dijelom za iscrtavanje
    SFMLDebugDraw debugDraw(m_window);
    m_world.SetDebugDraw(&debugDraw);

    //instantiate ContactListener
    //at global scope
    ContactListener ContactListenerInstance;
    m_world.SetContactListener(&ContactListenerInstance);

    // Set initial flags for what to draw ->
    //zelimo da se iscrtaju geometrijski likovi kojima opisujemo nekonv. objekte
    debugDraw.SetFlags(b2Draw::e_shapeBit);

    sf::Time elapsedTime;
    const float timePerFrame = 1.0 / 0.07;   //textures per millisecond


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
                //jump
                if (event.key.code == sf::Keyboard::Space){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                        ch1->getBody()->ApplyForce(b2Vec2(100,-400),ch1->getBody()->GetWorldCenter(),true);

                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                        ch1->getBody()->ApplyForce(b2Vec2(-100,-400),ch1->getBody()->GetWorldCenter(),true);

                    else
                        ch1->getBody()->ApplyForce(b2Vec2(0,-400),ch1->getBody()->GetWorldCenter(),true);
                }



                //shapes
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

            //walk left/right + reverse texture
            if (event.key.code == sf::Keyboard::Right){
                ch1->getBody()->ApplyForce(b2Vec2(20,0),ch1->getBody()->GetWorldCenter(),true);
                ch1->setSpriteScale(b2Vec2(1,1));

            }
            if (event.key.code == sf::Keyboard::Left){
                 ch1->getBody()->ApplyForce(b2Vec2(-20,0),ch1->getBody()->GetWorldCenter(),true);
                 ch1->setSpriteScale(b2Vec2(-1,1));

            }


            if(elapsedTime.asMilliseconds()>=timePerFrame){
               ch1->setCurrTexture( (ch1->getCurrTexture() + 1) % 10);
               elapsedTime = clock.restart();
            }

        }

        // Update window
        m_window.clear(sf::Color::Transparent);

        // Update world Box2D
        m_world.Step(TIMESTEP, VELITER, POSITER);

        //draw background
        for(int i = 0; i<4; ++i){
            sf::Sprite s = sf::Sprite(BGtexture[i]);
            s.setScale(0.6,0.4);
            m_window.draw(s);
        }

        // Draw Sprites
        for (int i = 0; i < m_vectorShapes.size(); i++)
            m_vectorShapes.at(i)->draw(m_window);


        //draw fixtures (shapes)
        m_world.DrawDebugData();


        //draw contact points
        for(int i = 0; i < ContactListenerInstance.m_pointCount; ++i){
            ContactPoint* contactPoint = ContactListenerInstance.m_points + i;
            if(contactPoint->state == b2_addState) debugDraw.DrawPoint(contactPoint->position, sf::Color::Cyan);
            else if(contactPoint->state == b2_persistState) debugDraw.DrawPoint(contactPoint->position, sf::Color::Magenta);
        }
        ContactListenerInstance.m_pointCount = 0; //ukloni sve dosadasnje tocke kontakta


        m_window.display();
    }

    return 0;
}

