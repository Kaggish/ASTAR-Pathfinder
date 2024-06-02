#include "StarShip.h"
#include <unordered_map>

void StarShip::setEntityPositionOnStart(std::unordered_map<int, Tile> validPosition)
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

void StarShip::setEntityPosition(std::unordered_map<int, Tile> validPosition, int i)
{
	position = validPosition.at(i).getPosition();
	validPosition.at(i).setOccupied(true);
}

void StarShip::loadTextures()
{
	shipTexture = LoadTexture("Assets/SpaceShip.png");
}

void StarShip::onStart(std::unordered_map<int, Tile> validPosition)
{
	loadTextures();
	setEntityPositionOnStart(validPosition);
}

void StarShip::update(std::unordered_map<int, Tile> validPosition, int i)
{
	setEntityPosition(validPosition, i);
}

void StarShip::draw()
{
	DrawTextureRec(shipTexture, Rectangle{ 0, 0, static_cast <float> (shipTexture.width),static_cast <float> (shipTexture.height) }, position, WHITE);
}

Vector2 StarShip::getPosition()
{
	return position;
}

void StarShip::setPosition(Vector2 _position)
{
	position = _position;
}
