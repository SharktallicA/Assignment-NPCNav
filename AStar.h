#pragma once
#include "SearchAlgorithm.h"

//A* algorithm implementation
class AStar : public SearchAlgorithm
{
protected:
	//Stores temporal distance values for each Tile
	vector<vector<double>> distances;

	//Flags which Tiles have been visited
	vector<vector<Tile*>> previous;

	//Diagonal distance heuristic
	double heuristic(Tile* d)
	{
		vec2 cur = d->GetCoord();
		vec2 dest = endRef->GetCoord();
		return (sqrt((cur.x - dest.x) * (cur.x - dest.x) + (cur.y - dest.y)*(cur.y - dest.y))) + tileCosts[d->GetType()];
	}

	//Processes the distances between neighbouring Tiles to the current Tile
	void calculateTentatives(void)
	{
		//If visited, exit immediately
		if (current->visited) return;

		//
		Tile* neighbour;

		for (Tile* nT : getAdjacents(current))
		{
			neighbour = nT;

			//Tentative distance
			double tDist = distances[current->GetCoord().y][current->GetCoord().x] + tileCosts[nT->GetType()] + heuristic(neighbour);


			if (tDist > distances[nT->GetCoord().y][nT->GetCoord().x])
			{
				distances[nT->GetCoord().y][nT->GetCoord().x] = tDist;
				previous[nT->GetCoord().y][nT->GetCoord().x] = nT;
			}
		}
		current->visited = true;
	}

	//Attempts to find the next Tile on the path
	void findNext(void)
	{
		//Stores the current processed best distance (initialised as max integer value)
		double currentBestDist = INT_MAX;

		for (Tile* nT : getAdjacents(current))
		{
			//Checks if processed Tile is closer than last
			if (distances[nT->GetCoord().y][nT->GetCoord().x] < currentBestDist && !nT->visited)
			{
				current = nT;
				currentBestDist = distances[nT->GetCoord().y][nT->GetCoord().x];
			}
		}
	}

public:
	//
	void Prepare(void)
	{
		distances.resize(tileMap.size());
		for (int i = 0; i < distances.size(); i++)
			distances[i].resize(tileMap[i].size());
		previous.resize(tileMap.size());
		for (int i = 0; i < previous.size(); i++)
			previous[i].resize(tileMap[i].size());
	}

	AStar(void) {}
	AStar(vector<vector<Tile*>> nMap, map<char, int> nCosts, Tile* nStart, Tile* nEnd)
	{
		tileMap = nMap;
		tileCosts = nCosts;
		current = nStart;
		endRef = nEnd;
		Prepare();
	}
	using SearchAlgorithm::SearchAlgorithm;

	//Runs A* algorithm and returns map with path
	bool Run(void)
	{
		if (!current) throw "There is no path to the end Tile!\n";

		calculateTentatives();
		findNext();

		if (current != endRef) return false;
		else return true;
	}
};