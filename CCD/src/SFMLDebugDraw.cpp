#include "SFMLDebugDraw.h"

SFMLDebugDraw::SFMLDebugDraw(sf::RenderWindow &window) : m_window(&window) {}


//neispunjeni, samo bridovi (aabb)
void SFMLDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon(vertexCount);

	for(int i = 0; i < vertexCount; i++)
	{
        polygon.setPoint(i, sf::Vector2f(std::floor(SFMLDebugDraw::B2VecToSFVec(vertices[i]).x),
                                         std::floor(SFMLDebugDraw::B2VecToSFVec(vertices[i]).y)));

    }
    polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineThickness(-1.f);
	polygon.setOutlineColor(SFMLDebugDraw::GLColorToSFML(color));

	m_window->draw(polygon);
}


void SFMLDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon(vertexCount);

    for(int i = 0; i < vertexCount; i++)
    {
        polygon.setPoint(i, sf::Vector2f(std::floor(SFMLDebugDraw::B2VecToSFVec(vertices[i]).x),
                                         std::floor(SFMLDebugDraw::B2VecToSFVec(vertices[i]).y)));

    }

	polygon.setOutlineThickness(-1.f);
    polygon.setFillColor(sf::Color::Transparent);
    polygon.setOutlineColor(SFMLDebugDraw::GLColorToSFML(color));

	m_window->draw(polygon);
}


void SFMLDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	sf::CircleShape circle(radius * sfdd::SCALE);

	circle.setOrigin(radius * sfdd::SCALE, radius * sfdd::SCALE);
	circle.setPosition(SFMLDebugDraw::B2VecToSFVec(center));
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(-1.f);
	circle.setOutlineColor(SFMLDebugDraw::GLColorToSFML(color));

	m_window->draw(circle);
}



void SFMLDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	sf::CircleShape circle(radius * sfdd::SCALE);
	circle.setOrigin(radius * sfdd::SCALE, radius * sfdd::SCALE);
	circle.setPosition(SFMLDebugDraw::B2VecToSFVec(center));
	circle.setFillColor(SFMLDebugDraw::GLColorToSFML(color, 60));
	circle.setOutlineThickness(1.f);
	circle.setOutlineColor(SFMLDebugDraw::GLColorToSFML(color));

	b2Vec2 endPoint = center + radius * axis;
	sf::Vertex line[2] =
	{
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(center), SFMLDebugDraw::GLColorToSFML(color)),
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(endPoint), SFMLDebugDraw::GLColorToSFML(color)),
	};

	m_window->draw(circle);
    m_window->draw(line, 2, sf::Lines);
}


void SFMLDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	sf::Vertex line[] =
	{
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(p1), SFMLDebugDraw::GLColorToSFML(color)),
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(p2), SFMLDebugDraw::GLColorToSFML(color))
	};

	m_window->draw(line, 2, sf::Lines);
}


void SFMLDebugDraw::DrawTransform(const b2Transform& xf)
{
    float lineLength = 0.5;

	b2Vec2 xAxis = xf.p + lineLength * xf.q.GetXAxis();
	sf::Vertex redLine[] =
	{
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(xf.p), sf::Color::Red),
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(xAxis), sf::Color::Red)
	};


	b2Vec2 yAxis = xf.p + lineLength * xf.q.GetYAxis();
	sf::Vertex greenLine[] =
	{
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(xf.p), sf::Color::Green),
		sf::Vertex(SFMLDebugDraw::B2VecToSFVec(yAxis), sf::Color::Green)
	};

	m_window->draw(redLine, 2, sf::Lines);
	m_window->draw(greenLine, 2, sf::Lines);
}


void SFMLDebugDraw::DrawPoint(const b2Vec2 &p, sf::Color color){
    //const sf::Vertex point = sf::Vertex(SFMLDebugDraw::B2VecToSFVec(p));
    sf::CircleShape circle;
    circle.setFillColor(color);
    circle.setPosition(SFMLDebugDraw::B2VecToSFVec(p));
    circle.setRadius(3.f);
    m_window->draw(circle);
}
