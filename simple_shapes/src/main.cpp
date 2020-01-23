#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "../include/SFMLDebugDraw.h"
#include "../include/Shape.h"
#include "../include/Rectangle.h"
#include "../include/Square.h"
#include "../include/Circle.h"
#include "../include/Triangle.h"
#include "../include/Rhombus.h"
#include "../include/ContactListener.h"

#include <vector>

#define TIMESTEP 1.0f/80.0f     // Refresh time
#define VELITER 8              // iterations per tick to calculate speed -> standardno 8
#define POSITER 3              // iterations to calculate the position -> standardno 3

#define WIDTH 800
#define HEIGHT 600




int randomNumber(int min, int max)
{
    return min + rand()% (max - min + 1);
}

void createShape(std::vector<Shape* > &vectorShapes, b2World &world, int numberShape)
{

    Shape*          shape;
    b2Body*         body;
    sf::Vector2f    position;

    position.x = randomNumber(50, WIDTH - 50);
    position.y = randomNumber(50, 100);

    switch( numberShape )
    {
        case 1:
            shape = static_cast<Square*>( new Square(world, position) );
            break;

        case 2:
            shape = static_cast<Circle*>( new Circle(world, position) );
            break;

        case 3:
            shape = static_cast<Triangle*>( new Triangle(world, position) );
            break;

        case 4:
            shape = static_cast<Rhombus*>( new Rhombus(world, position) );
            break;

    }

    // Add shape -> mozda mogu ovo zamijeniti s iteriranjem po fixtureima i koristenjem userData
    vectorShapes.push_back(shape);

    // Initial move
    b2Vec2 force;
    force.x = randomNumber(-100, 100);
    force.y = randomNumber(-100, 100);

    body = vectorShapes.back()->getBody();
    body->ApplyForce(force, body->GetWorldCenter(), true);
}


void createWalls(std::vector<Shape* > &vectorShapes, b2World &world){
    // Create walls - static bodies
    vectorShapes.push_back(new Rectangle(400.f, 1.f, sf::Vector2f(800.f, 15.f), world));
    vectorShapes.push_back(new Rectangle(400.f, 600.f, sf::Vector2f(800.f, 15.f), world));
    vectorShapes.push_back(new Rectangle(1.f, 300.f, sf::Vector2f(15.f, 800.f), world));
    vectorShapes.push_back(new Rectangle(800.f, 300.f, sf::Vector2f(15.f, 800.f), world));

    //Create platforms
    vectorShapes.push_back(new Rectangle(80.f, 200.f, sf::Vector2f(150.f, 15.f), world));
    vectorShapes.push_back(new Rectangle(200.f, 300.f, sf::Vector2f(100.f, 15.f), world));
    vectorShapes.push_back(new Rectangle(300.f, 400.f, sf::Vector2f(100.f, 15.f), world));
    vectorShapes.push_back(new Rectangle(720.f, 200.f, sf::Vector2f(150.f, 15.f), world));
    vectorShapes.push_back(new Rectangle(600.f, 300.f, sf::Vector2f(100.f, 15.f), world));
    vectorShapes.push_back(new Rectangle(500.f, 400.f, sf::Vector2f(100.f, 15.f), world));

}

void drawScene(sf::RenderWindow &window, b2World &world, SFMLDebugDraw &debugDraw,
               std::vector<Shape*> &vectorShapes, ContactListener &ContactListenerInstance){

    window.clear(sf::Color::Transparent);
    // Update world Box2D
    world.Step(TIMESTEP, VELITER, POSITER);
    // Draw vector shapes
    for (int i = 0; i < vectorShapes.size(); i++)
        vectorShapes[i]->draw(window);


    ///draw contact points
    for(int i = 0; i < ContactListenerInstance.m_pointCount; ++i){
        ContactPoint* contactPoint = ContactListenerInstance.m_points + i;
        if(contactPoint->state == b2_addState) debugDraw.DrawPoint(contactPoint->position, sf::Color::Cyan);
        else if(contactPoint->state == b2_persistState) debugDraw.DrawPoint(contactPoint->position, sf::Color::White);
    }
    ContactListenerInstance.m_pointCount = 0;

    // Debug draw display
    world.DrawDebugData();
    window.display();
}

void showInstructions()
{
    std::cout << std::endl << std::endl;

    std::cout << " INSTRUCTIONS             "            << std::endl << std::endl;

    std::cout << " Draw square       : Key 1"            << std::endl;
    std::cout << " Draw circle       : Key 2"            << std::endl;
    std::cout << " Draw triangle     : Key 3"            << std::endl;
    std::cout << " Draw rhombus      : Key 4"            << std::endl;
    std::cout << " Random movement   : Key space"        << std::endl << std::endl;

    std::cout << " Debug draw        : Keys A, B";
}

int main()
{

    // Instructions
    showInstructions();

    // Define world Box2D - Zero gravity
    b2World m_world(b2Vec2(0.f, 9.81f));

    std::vector<Shape* > m_vectorShapes;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow m_window(sf::VideoMode(800, 600), "Collision detection", sf::Style::Default, settings);
    m_window.setFramerateLimit(60);

    // Initialize Debug draw -> poveze s sfml dijelom za iscrtavanje
    SFMLDebugDraw debugDraw(m_window);
    m_world.SetDebugDraw(&debugDraw);

    //instantiate ContactListener
    ContactListener ContactListenerInstance;
    m_world.SetContactListener(&ContactListenerInstance);

    //Create walls and platforms
    createWalls(m_vectorShapes, m_world);



    while (m_window.isOpen())
    {

        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if ( event.type == sf::Event::KeyReleased )
            {
                // Create shapes
                if (event.key.code == sf::Keyboard::Num1)
                    createShape(m_vectorShapes, m_world, 1);

                if (event.key.code == sf::Keyboard::Num2)
                    createShape(m_vectorShapes, m_world, 2);

                if (event.key.code == sf::Keyboard::Num3)
                    createShape(m_vectorShapes, m_world, 3);

                if (event.key.code == sf::Keyboard::Num4)
                    createShape(m_vectorShapes, m_world, 4);

                // Move shape
                if (event.key.code == sf::Keyboard::Space)
                {
                    int nShapes = m_vectorShapes.size();

                    if (nShapes > 4)
                    {
                        int randShape = randomNumber(5, nShapes);
                        b2Vec2 force(randomNumber(-100, 100), randomNumber(-100, 100));

                        b2Body* body = m_vectorShapes.at(randShape - 1)->getBody();
                        body->ApplyForce( force, body->GetWorldCenter(), true );
                    }
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

        }
        //Update scene
        drawScene(m_window, m_world, debugDraw, m_vectorShapes, ContactListenerInstance);
    }

    return 0;
}

