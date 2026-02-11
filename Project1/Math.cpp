#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight)
	{
		Position2D result;
		result.x = rand() / (float)RAND_MAX * screenWidth;
		result.y = rand() / (float)RAND_MAX * screenHeight;
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
