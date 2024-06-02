#pragma once
#include "raylib.h"
#include <unordered_map>

class Entity
{
	virtual void setEntityPositionOnStart(std::unordered_map<int, Tile> validPosition) = 0;
	virtual void setEntityPosition(std::unordered_map<int, Tile> validPosition, int i) = 0;

	virtual void onStart(std::unordered_map<int, Tile> validPosition) = 0;
	virtual void update(std::unordered_map<int, Tile> validPosition, int i) = 0;
	virtual void draw() = 0;

};