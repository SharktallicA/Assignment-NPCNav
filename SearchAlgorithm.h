#pragma once
#include "Tile.h"
#include <map>

class SearchAlgorithm
{
protected:
	//Tile Map
	vector<vector<Tile*>> tileMap;

	//Reference to what costs certain Tile type
	map<char, int> tileCosts;

	//Reference to current processed Tile
	Tile* current = nullptr;

	//Reference to end Tile
	Tile* endRef = nullptr;

	//Amount of iterations the algorithm has used to complete the search 
	int count = 1;

	//Checks if given tile coordinates are valid
	bool checkIfValid(vec2 toCheck)
	{
		if (toCheck.y < 0 || toCheck.y == tileMap.size()) return false;
		if (toCheck.x < 0 || toCheck.x == tileMap[toCheck.y].size()) return false;
		if (tileMap[toCheck.y][toCheck.x]->visited) return false;
		return true;
	}

	//Returns valid adjacent Tiles around the specified Tile
	vector<Tile*> getAdjacents(Tile* toFindAround)
	{
		vector<Tile*> adjs;
		vec2 tPos = toFindAround->GetCoord();

		if (checkIfValid(vec2(tPos.x, tPos.y - 1)))
			adjs.push_back(tileMap[tPos.y - 1][tPos.x]);
		if (checkIfValid(vec2(tPos.x + 1, tPos.y)))
			adjs.push_back(tileMap[tPos.y][tPos.x + 1]);
		if (checkIfValid(vec2(tPos.x, tPos.y + 1)))
			adjs.push_back(tileMap[tPos.y + 1][tPos.x]);
		if (checkIfValid(vec2(tPos.x - 1, tPos.y)))
			adjs.push_back(tileMap[tPos.y][tPos.x - 1]);

		return adjs;
	}

public:
	//
	virtual void Prepare(void) {}

	SearchAlgorithm(void) {}
	SearchAlgorithm(vector<vector<Tile*>> nMap, map<char, int> nCosts, Tile* nStart, Tile* nEnd)
	{
		tileMap = nMap;
		tileCosts = nCosts;
		current = nStart;
		endRef = nEnd;
		Prepare();
	}

	//Runs search algorithm and returns map with path
	virtual bool Run(void) { return true; }
};