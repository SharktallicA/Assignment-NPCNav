#pragma once
#include "Tile.h"
#include <fstream>
#include <map>

using namespace std;

//Tile Map constructing class
class TileLoader
{
private:
	//2D vector of Tile objects that form the program's map
	vector<vector<Tile*>> tiles;

	//STL Map of Utility::Colour coding for each Tile type
	map<char, cvec> tileColours;

	//STL Map of movement costs for each Tile type
	map<char, int> tileCosts;

	//Loads the raw Tile data from Map text file
	void loadData(string fileName)
	{
		ifstream ifMap(fileName);
		if (!ifMap) throw "CRITICAL ERROR: " + fileName + " data file is not present!\n";

		tiles = vector<vector<Tile*>>(24);
		string line;
		int count = 0;

		while (getline(ifMap, line))
		{
			if (line[0] == '#'); //prevent operation for any comment lines within text file
			else if (line[0] == '*') //capture metadata
			{
				//Stores delimited data | Expected layout: [0] Tile's type as char, [1] Tile's Utility::Colour as int, [2] Tile's movement cost
				vector<string> delimited;
				//Parses line into breakable stream
				stringstream pStream(line);

				while (pStream.good())
				{
					string sub;
					getline(pStream, sub, ',');
					//Make sure to not add the meta-flagging char into the delimited vector!
					if (sub != "*") delimited.push_back(sub); 
				}
				tileColours[delimited[0][0]] = cvec(Colour(stoi(delimited[1])), Colour(stoi(delimited[1])));
				tileCosts[delimited[0][0]] = stoi(delimited[2]);
			}
			else 
			{
				for (int i = 0; i < line.length(); i++)
					tiles[count].push_back(new Tile(vec2(i, count), line[i]));
				count++;
			}
		}
		ifMap.close();
	}

public:
	TileLoader(string nFileName) { loadData(nFileName); }

	vector<vector<Tile*>> GetMap(void) { return tiles; }
	map<char, cvec> GetTileColours(void) { return tileColours; }
	map<char, int> GetTileCosts(void) { return tileCosts; }
};