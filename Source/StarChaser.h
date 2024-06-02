#pragma once
#include "raylib.h"
#include <unordered_map>
#include "PathFinder.h"
#include "Entity.h"

enum state
{
	chasing,
	selling,
	returning,
};

class StarChaser : public Entity
{
private:
	Vector2 position;
	Vector2 starPosition;
	Vector2 tradingPostPosition;
	Vector2 shipPosition;

	state currentState = state::chasing;

	float stamina = 100;
	bool starAquired = false;

	Texture2D chaserTexture;
private:
	void setEntityPositionOnStart(std::unordered_map<int, Tile> validPosition) override;
	void setEntityPosition(std::unordered_map<int, Tile> validPosition, int i) override;


public:
	void loadTextures();
	void recoverStamina(float recover);
	void loseStamina(float loss);
	void onStart(std::unordered_map<int, Tile> validPosition) override; // set texture, position
	void update(std::unordered_map<int, Tile> validPosition, int i) override;
	void draw() override;

	Vector2 getPosition();
	state getState();
	float getStamina();
	bool getAquired();

	void setPosition(Vector2 _position);
	void setState(state _state);
	void setAquired(bool aquired);
};