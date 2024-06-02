#include "StarChaser.h"

void StarChaser::setEntityPositionOnStart(std::unordered_map<int, Tile> validPosition)
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

void StarChaser::setEntityPosition(std::unordered_map<int, Tile> validPosition, int i)
{
	position = validPosition.at(i).getPosition();
	validPosition.at(i).setOccupied(true);
}

void StarChaser::loadTextures()
{
	chaserTexture = LoadTexture("Assets/StarChaser.png");
}

void StarChaser::recoverStamina(float recover)
{
	stamina += recover;
}

void StarChaser::loseStamina(float loss)
{
	stamina -= loss;
}

void StarChaser::onStart(std::unordered_map<int, Tile> validPosition)
{
	loadTextures();
	setEntityPositionOnStart(validPosition);
}

void StarChaser::update(std::unordered_map<int, Tile> validPosition, int i)
{
	setEntityPosition(validPosition, i);
}

void StarChaser::draw()
{
	DrawTextureRec(chaserTexture, Rectangle{ 0, 0, static_cast <float> (chaserTexture.width),static_cast <float> (chaserTexture.height) }, position, WHITE);
}

Vector2 StarChaser::getPosition()
{
	return position;
}

state StarChaser::getState()
{
	return currentState;
}

float StarChaser::getStamina()
{
	return stamina;
}

bool StarChaser::getAquired()
{
	return starAquired;
}

void StarChaser::setPosition(Vector2 _position)
{
	position = _position;
}

void StarChaser::setState(state _state)
{
	currentState = _state;
}

void StarChaser::setAquired(bool aquired)
{
	starAquired = aquired;
}
