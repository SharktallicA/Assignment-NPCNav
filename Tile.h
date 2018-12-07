#pragma once
#include "Utility.h"
#include "Entity.h"

using namespace std;

//Locational representation
class Tile
{
private:
	//Tile's type denoted as char (defaulted as ' ' blank space to represent free area)
	char rep = ' ';

	//Tile's position in the Map
	vec2 coord;

public:
	//Flags whether this Tile has been visited by a processing algorithm
	bool visited = false;

	Tile(void) { }
	Tile(vec2 nCoord, char nRep) { coord = nCoord, rep = nRep; }

	//Returns Tile type-denoting character
	char GetType(void) { return rep; }

	//Returns the Tile's coordinate in the 2D Map vector
	vec2 GetCoord(void) { return coord; }
};