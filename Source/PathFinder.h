#pragma once
#include "raylib.h"
#include <vector>
#include "Grid.h"

class PathFinder
{
public:
	static void FindPath(const Tile& startTile, const Tile& endTile, std::vector<const Tile*>& result );
	static float getDistance(const Tile& tileA, const Tile& tileB);
};

