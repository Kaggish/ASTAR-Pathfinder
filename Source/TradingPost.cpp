#include "TradingPost.h"

void TradingPost::setEntityPositionOnStart(std::unordered_map<int, Tile> validPosition)
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

void TradingPost::setEntityPosition(std::unordered_map<int, Tile> validPosition, int i)
{
	position = validPosition.at(i).getPosition();
	validPosition.at(i).setOccupied(true);
}

void TradingPost::loadTextures()
{
	tradingPostTexture = LoadTexture("Assets/TradingPost.png");
}

void TradingPost::onStart(std::unordered_map<int, Tile> validPosition)
{
	loadTextures();
	setEntityPositionOnStart(validPosition);
}

void TradingPost::update(std::unordered_map<int, Tile> validPosition, int i)
{
	setEntityPosition(validPosition, i);
}

void TradingPost::draw()
{
	DrawTextureRec(tradingPostTexture, Rectangle{ 0, 0, static_cast <float> (tradingPostTexture.width),static_cast <float> (tradingPostTexture.height) }, position, WHITE);
}

Vector2 TradingPost::getPosition()
{
	return position;
}

void TradingPost::setPosition(Vector2 _position)
{
	position = _position;
}
