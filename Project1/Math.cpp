#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	bool DoShapesCollide(const Rectangle& rect1, const Rectangle& rect2)
	{
		return rect1.position.x < rect2.position.x + rect2.size.x && 
			rect1.position.x + rect1.size.x > rect2.position.x &&
			rect1.position.y < rect2.position.y + rect2.size.y &&
			rect1.position.y + rect1.size.y > rect2.position.y;
	}

	bool DoShapesCollide(const Circle& circle1, const Circle& circle2)
	{
		float dx = circle1.position.x - circle2.position.x;
		float dy = circle1.position.y - circle2.position.y;
		float distance = sqrt(dx * dx + dy * dy);
		return distance < circle1.radius + circle2.radius;
	}

	bool DoShapesCollide(const Rectangle& rect, const Circle& circle)
	{
		float dx = circle.position.x - std::max(rect.position.x, std::min(circle.position.x, rect.position.x + rect.size.x));
		float dy = circle.position.y - std::max(rect.position.y, std::min(circle.position.y, rect.position.y + rect.size.y));
		return (dx * dx + dy * dy) < (circle.radius * circle.radius);
	}

	Position2D GetRandomPositionInScreen(Rectangle& screen)
	{
		Position2D result;
		result.x = rand() / (float)RAND_MAX * screen.size.x;
		result.y = rand() / (float)RAND_MAX * screen.size.y;
		return result;
	}

	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size)
	{
		float dX = (float)fabs(rect1Position.x - rect2Position.x);
		float dY = (float)fabs(rect1Position.y - rect2Position.y);
		return (dX <= (rect1Size.x + rect2Size.x) / 2.f &&
			dY <= (rect1Size.y + rect2Size.y) / 2.f);
	}

	bool IsCirclesCollide(Position2D square1Position, float circle1Radius, Position2D square2Position, float circle2Radius)
	{
		float squareDistance = (square1Position.x - square2Position.x) * (square1Position.x - square2Position.x) +
			(square1Position.y - square2Position.y) * (square1Position.y - square2Position.y);
		float squareRadiusSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius);
		return (squareDistance <= squareRadiusSum);
	}

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	sf::Vector2f GetScale(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		return scale;
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}
}
