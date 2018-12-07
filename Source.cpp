#include "Game.h"

using namespace std;

int main(void)
{
	try
	{
		Game game;
		while (game.Play());
	}
	catch (string msg) { cout << msg; }

	Utility::pause();
	return 0;
}