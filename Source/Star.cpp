#include "Star.h"

void Star::setEntityPositionOnStart(std::unordered_map<int, Tile> validPosition)
{
	int checker = 0;
	checker = GetRandomValue(0, validPosition.size() - 1);
	if (validPosition.contains(checker))
	{
		position.x = validPosition.at(checker).getPosition().x;
		position.y = validPosition.at(checker).getPosition().y;
	}
	else
	{
		setEntityPositionOnStart(validPosition);
	}
}

void Star::setEntityPosition(std::unordered_map<int, Tile> validPosition, int i)
{
	position = validPosition.at(i).getPosition();
	validPosition.at(i).setOccupied(true);
}

void Star::loadTextures()
{
	starTexture = LoadTexture("Assets/Star.png");
}

void Star::onStart(std::unordered_map<int, Tile> validPosition)
{
	loadTextures();
	setEntityPositionOnStart(validPosition);
}

void Star::update(std::unordered_map<int, Tile> validPosition, int i)
{
	setEntityPosition(validPosition, i);
}

void Star::draw()
{
	DrawTextureRec(starTexture, Rectangle{ 0, 0, static_cast <float> (starTexture.width),static_cast <float> (starTexture.height) }, position, WHITE);
}

Vector2 Star::getPosition()
{
	return position;
}

void Star::setPosition(Vector2 _position)
{
	position = _position;
}
