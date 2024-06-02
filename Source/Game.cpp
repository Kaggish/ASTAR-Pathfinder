#include "Game.h"
#include <iostream>

bool Game::checkCollision(Vector2 mouse, Rectangle tile)
{
	if (mouse.x >= tile.x && tile.x + tile.width >= mouse.x && 
		mouse.y >= tile.y && tile.y + tile.height >= mouse.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::mouseVStileCheck()
{
	for (int i = 0; i < grid.tile.size(); ++i)
	{
		if (checkCollision(GetMousePosition(), grid.tile.at(i)->getCollisionBox()))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				grid.tile.at(i)->setTextureID(2);
				grid.tile.at(i)->setBlocked(false);
			}
			else if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				grid.tile.at(i)->setTextureID(1);
				grid.tile.at(i)->setBlocked(true);
			}

			if (IsKeyDown(KEY_Q) && grid.tile.at(i)->getBlocked() == false && grid.tile.at(i)->getOccupied() == false)
			{
				star.update(validPositions, i);
			}
			else if (IsKeyDown(KEY_W) && grid.tile.at(i)->getBlocked() == false && grid.tile.at(i)->getOccupied() == false)
			{
				starChaser.update(validPositions, i);
			}
			else if (IsKeyDown(KEY_E) && grid.tile.at(i)->getBlocked() == false && grid.tile.at(i)->getOccupied() == false)
			{
				tradingPost.update(validPositions, i);
			}
			else if (IsKeyDown(KEY_R) && grid.tile.at(i)->getBlocked() == false && grid.tile.at(i)->getOccupied() == false)
			{
				ship.update(validPositions, i);
			}
			else
			{
				grid.tile.at(i)->setOccupied(false);
				return;
			}
		}
	}
}

void Game::insertPosition()
{
	for (int i = 0; i < grid.tile.size(); ++i)
	{
		if (grid.tile.at(i)->getBlocked() == false && grid.tile.at(i)->getOccupied() == false)
		{
			validPositions.insert(std::pair(i, grid.tile.at(i)->getPosition()));
		}
		
		if (validPositions.contains(grid.tile.at(i)->getUniqueID()))
		{
			if (grid.tile.at(i)->getBlocked() == true || grid.tile.at(i)->getOccupied() == true)
			{
				validPositions.erase(i);
			}
		}
	}
}

void Game::findTarget(Vector2 startPos, Vector2 targetPos)
{
	auto FindStartTile = [&](const Tile* t) {
		return t->getPosition().x == startPos.x && t->getPosition().y == startPos.y;
	};

	auto FindEndTile = [&](const Tile* t) {
		return t->getPosition().x == targetPos.x && t->getPosition().y == targetPos.y;
	};

	startTile = Grid::getInstance().getTileIf(FindStartTile);
	endTile = Grid::getInstance().getTileIf(FindEndTile);
}

void Game::goToStar()
{
	findTarget(starChaser.getPosition(), star.getPosition());
	if (startTile && endTile)
	{
		pathFinder.FindPath(*startTile, *endTile, path);
	}
	int i = 0;
	frameTime++;
	if (i < path.size())
	{
		if (frameTime % 15 == 0)
		{
			starChaser.setPosition(path.at(i)->getPosition());
			++i;
		}

		if (starChaser.getPosition().x == star.getPosition().x &&
			starChaser.getPosition().y == star.getPosition().y)
		{
			starChaser.setState(selling);
			starChaser.setAquired(true);
			return;
		}
	}
}

void Game::goToPost()
{
	findTarget(starChaser.getPosition(), tradingPost.getPosition());
	frameTime++;
	if (startTile && endTile)
	{
		pathFinder.FindPath(*startTile, *endTile, path);
	}
	int i = 0;
	if (i < path.size())
	{
		if (starChaser.getStamina() > 0 && starChaser.getAquired() == true)
		{
			if (frameTime % 15 == 0)
			{
				starChaser.setPosition(path.at(i)->getPosition());
				starChaser.loseStamina(10);
				star.setPosition(starChaser.getPosition());
				++i;
			}
		}
		else
		{
			starChaser.setState(returning);
			starChaser.setAquired(false);
			return;
		}
	}
	if (starChaser.getPosition().x == tradingPost.getPosition().x &&
		starChaser.getPosition().y == tradingPost.getPosition().y)
	{
		starChaser.setState(chasing);
		starChaser.setAquired(false);
		return;
	}
}

void Game::goToShip()
{
	findTarget(starChaser.getPosition(), ship.getPosition());
	if (startTile && endTile)
	{
		pathFinder.FindPath(*startTile, *endTile, path);
	}
	int i = 0;
	frameTime++;
	if (i < path.size())
	{
		if (frameTime % 15 == 0)
		{
			starChaser.setPosition(path.at(i)->getPosition());
			++i;
		}
		if (starChaser.getPosition().x == ship.getPosition().x &&
			starChaser.getPosition().y == ship.getPosition().y)
		{
			starChaser.recoverStamina(100);
			starChaser.setState(chasing);
			return;
		}
	}
}


void Game::onStart()
{
	grid.onStart();
	insertPosition();
	star.onStart(validPositions);
	insertPosition();
	starChaser.onStart(validPositions);
	insertPosition();
	ship.onStart(validPositions);
	insertPosition();
	tradingPost.onStart(validPositions);
}

void Game::update()
{
	grid.update();
	mouseVStileCheck();
	insertPosition();

	switch (starChaser.getState())
	{
	case chasing:
		goToStar();
		break;
	case selling:
		goToPost();
		break;
	case returning:
		goToShip();
		break;
	}
}

void Game::draw()
{
	grid.draw();
	ship.draw();
	tradingPost.draw();
	star.draw();
	starChaser.draw();
	if (path.size() > 0)
	{
		for (int i = 0; i < path.size(); ++i)
		{
			if (i < path.size() - 1)
			{
				DrawLine(path.at(i)->getPosition().x + 25, path.at(i)->getPosition().y +25, path.at(i + 1)->getPosition().x + 25, path.at(i + 1)->getPosition().y + 25, BLACK);
			}
		}
		path.clear();
	}
}
