#include "PathFinder.h"
#include <cassert>

template< typename T>
bool VectorContains(const std::vector<T>& Vec, const T& t)
{
	const auto Iter = std::find(Vec.begin(), Vec.end(), t);
	return Iter != Vec.end();
}

template< typename T>
T* VectorFindIf(std::vector<T>& Vec, const std::function<bool(const T&)>& Query)
{
	const auto Iter = std::find_if(Vec.begin(), Vec.end(), Query);
	return Iter != Vec.end() ? &*Iter : nullptr;
}

void PathFinder::FindPath(const Tile& startTile, const Tile& endTile, std::vector<const Tile*>& result)
{
	struct Node
	{
		float getFCost() const { return gCost + hCost; }
		const Tile* t = nullptr;
		float gCost = 0;
		float hCost = 0;
		Node* parent = nullptr;
		bool visited = false;
	};

	// Create local copy of all tiles in form of a Node.
	const std::vector<Tile*>& AllTiles = Grid::getInstance().tile;
	std::vector<Node> AllNodes;
	AllNodes.reserve(AllTiles.size());
	for (const Tile* t : AllTiles)
	{
		AllNodes.push_back(Node(t));
	}

	Node* startNode = VectorFindIf<Node>(AllNodes, [ &startTile ](const Node& n) 
	{ 
		return n.t == &startTile; 
	});
	Node* endNode = VectorFindIf<Node>(AllNodes, [ &endTile ](const Node& n) 
	{ 
		return n.t == &endTile; 
	});

	std::vector<Node*> openList2;

	openList2.push_back( startNode );

	while (openList2.size() > 0)
	{
		Node* currentNode = *openList2.begin();

		for( int Index = 1; Index < openList2.size(); ++Index )
		{
			Node& i = *openList2[Index];
			if (i.getFCost() < currentNode->getFCost() || i.getFCost() == currentNode->getFCost() && i.hCost < currentNode->hCost && i.gCost < currentNode->gCost)
			{
 				currentNode = &i;
			}
		}

		std::erase(openList2, currentNode);
		currentNode->visited = true;

		auto retracePath = [startNode, endNode](std::vector<const Tile*>& path)
		{
			Node* current = endNode;
			while (current != startNode)
			{
				path.insert(path.begin(), current->t);
				current = current->parent;
			}
		};

		if (currentNode->t->getPosition().x == endTile.getPosition().x &&
			currentNode->t->getPosition().y == endTile.getPosition().y)
		{
			retracePath(result);
			return;
		}
		
		for ( int Index : currentNode->t->neighborIndex )
		{
			Node* neighborNode = &AllNodes[Index];

			if (neighborNode->t->getBlocked() == true || neighborNode->visited )
			{
				continue;
			}

			float newMovementCost = currentNode->gCost + getDistance(*currentNode->t, *neighborNode->t);
			if (newMovementCost < neighborNode->gCost || !VectorContains(openList2, neighborNode))
			{
				neighborNode->gCost = newMovementCost;
				neighborNode->hCost = getDistance(*neighborNode->t, endTile);
				neighborNode->parent = currentNode;

				if (!VectorContains(openList2, neighborNode))
				{
					openList2.push_back(neighborNode);
				}
			}
		}
	}
}

float PathFinder::getDistance(const Tile& tileA, const Tile& tileB)
{
	float distX = abs(tileA.getPosition().x - tileB.getPosition().x);
	float distY = abs(tileA.getPosition().y - tileB.getPosition().y);

	if (distX > distY)
	{
		return 14 * distY + 10*(distX - distY);
	}
	else
	{
		return 14 * distX + 10*(distY - distX);
	}
}
