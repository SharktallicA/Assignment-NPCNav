#pragma once
#include "TileLoader.h"
#include "AStar.h"
#include <map>

using namespace std;

class Game
{
private:
	//Tile Map
	vector<vector<Tile*>> tileMap;

	//Reference to what colours certain Tile types should be rendered as
	map<char, cvec> tileColours;

	//Reference to what costs certain Tile type
	map<char, int> tileCosts;

	//
	AStar* search;

	//Prints a coloured representation of the tileMap onto the screen
	void render(void)
	{
		Utility::moveCursor(vec2(0, 0));
		for (vector<Tile*> l : tileMap)
		{
			for (Tile* t : l)
			{
				if(t->visited)
					Utility::setColour(cvec(RED, RED));
				else Utility::setColour(tileColours[t->GetType()]);
				cout << t->GetType();
			}
			Utility::resetColour();
			cout << "\n";
		}
		cout << "\n\n";
	}

	//Checks if given tile coordinates are valid
	bool checkIfValid(vec2 toCheck)
	{
		if (toCheck.y < 0 || toCheck.y == tileMap.size()) return false;
		if (toCheck.x < 0 || toCheck.x == tileMap[toCheck.y].size()) return false;
		if (tileMap[toCheck.y][toCheck.x]->visited) return false;
		return true;
	}

public:
	Game(void)
	{
		Utility::setWindowTitle("Imperial Shark Software's NPC Navmate 2000 Version 10 Second Edition");
		try
		{
			TileLoader tLoad("map.txt");
			tileMap = tLoad.GetMap();
			tileColours = tLoad.GetTileColours();
			tileCosts = tLoad.GetTileCosts();

			Tile* start = nullptr;
			Tile* end = nullptr;

			for (vector<Tile*> vT : tileMap)
			{
				for (Tile* t : vT)
				{
					if (t->GetType() == 'O') start = t;
					if (t->GetType() == 'D') end = t;
				}
			}

			search = new AStar(tileMap, tileCosts, start, end);
		}
		catch (string msg) { throw msg; }
	}
	~Game(void)
	{
		delete search;
		for (vector<Tile*> vT : tileMap)
			for (Tile* t : vT) delete t;
	}

	bool Play(void)
	{
		//cout << "Travel cost " << travelCost << endl;
		bool complete;
		
		try { complete = search->Run(); }
		catch (string msg) { throw msg; }

		//Utility::sleep(100);
		
		render();
		return !complete;
	}
};