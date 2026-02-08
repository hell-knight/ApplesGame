#pragma once

namespace sf
{
	class Sprite;
}

namespace ApplesGame
{
	struct Vector2D
	{
		float x = 0;
		float y = 0;
	};

	typedef Vector2D Position2D;

	struct Rectangle
	{
		Position2D position;
		Vector2D size;
	};

	struct Circle
	{
		Position2D position;
		float radius;
	};

	bool DoShapesCollide(const Rectangle& rect1, const Rectangle& rect2);
	bool DoShapesCollide(const Circle& circle1, const Circle& circle2);
	bool DoShapesCollide(const Rectangle& rect, const Circle& circle);

	Position2D GetRandomPositionInScreen(Rectangle& screen);

	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size,
		Position2D rect2Position, Vector2D rect2Size);

	bool IsCirclesCollide(Position2D square1Position, float circle1Radius,
		Position2D square2Position, float circle2Radius);

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

	sf::Vector2f GetScale(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
}
