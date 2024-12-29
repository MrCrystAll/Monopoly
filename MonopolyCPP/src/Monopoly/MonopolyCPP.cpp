// MonopolyCPP.cpp : Defines the entry point for the application.
//

#include <Monopoly/Game.h>
int main()
{
	Game game = Game(4);
	game.Start();

	return 0;
}
