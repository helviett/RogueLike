#include "Game.h"
#include <iostream>
#include <conio.h>
#include "curses.h"

int main()
{
	initscr();
	curs_set(0);
	srand(0);
	char key;
	Game game;
restart:
	game.Clear();
	game.LoadMap("map.txt");
	game.RunGame();
	printw("Press r to restart or any key to exit\n");
	refresh();
	clear();
	key = _getch();
	if (key == 'r')
		goto restart;
	endwin();
	return 0;
}