#ifndef SFMLDEBUGDRAW_H
#define SFMLDEBUGDRAW_H

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

namespace sfdd
{
    const float SCALE = 64.f;
}

class SFMLDebugDraw : public b2Draw
{
private:
	sf::RenderWindow* m_window;
public:
	SFMLDebugDraw(sf::RenderWindow &window);

    //scale OpenGL colors [0-1] to SFML [0-255]
	static sf::Color GLColorToSFML(const b2Color &color, sf::Uint8 alpha = 255)
	{
        return sf::Color(color.r * 255, color.g * 255, color.b * 255, alpha);
	}

    //scale Box2d coordinates to pixels
	static sf::Vector2f B2VecToSFVec(const b2Vec2 &vector, bool scaleToPixels = true)
	{
		return sf::Vector2f(vector.x * (scaleToPixels ? sfdd::SCALE : 1.f), vector.y * (scaleToPixels ? sfdd::SCALE : 1.f));
	}

    // Draw a closed polygon provided by vector of points in CCW order.
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

    // Draw a solid closed polygon provided by vector of points in CCW order.
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

    // Draw a circle.
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

    // Draw a solid circle.
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

    // Line segment.
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

    /// Draw a transform.
	void DrawTransform(const b2Transform& xf);

};
	
#endif // SFMLDEBUGDRAW_H
