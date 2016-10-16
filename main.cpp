#include "Game.h"
#include "curses.h"

int main()
{
	initscr();
	curs_set(0);
	srand(0);
	Game game;
	game.LoadMap("map.txt");
	game.RunGame();
	system("pause");
	endwin();
	return 0;
}