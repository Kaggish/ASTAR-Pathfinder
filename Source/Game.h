#pragma once
#include "Grid.h"
#include "StarShip.h"
#include "TradingPost.h"
#include "StarChaser.h"
#include "Star.h"
#include "PathFinder.h"
#include <unordered_map>
#include <vector>

class Game
{
private:
	Grid& grid = Grid::getInstance();
	std::vector<const Tile*> path;
	StarShip ship;
	TradingPost tradingPost;
	StarChaser starChaser;
	Star star;
	PathFinder pathFinder;

	const Tile* startTile;
	const Tile* endTile;

	unsigned int frameTime = 0;
	bool pathfoundStar = false;
	bool pathfoundPost = false;
	bool pathfoundShip = false;

private:
	bool checkCollision(Vector2 mouse, Rectangle tile);
	void mouseVStileCheck();
	void insertPosition();
	void findTarget(Vector2 startPos, Vector2 targetPos);

	void goToStar();
	void goToShip();
	void goToPost();

public:
	std::unordered_map<int, Tile> validPositions;
	void onStart();
	void update();
	void draw();
};