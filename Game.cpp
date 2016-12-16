#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include "Obstacle.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <fstream>
#include "curses.h"
#include "Settings.h"



Game::Game()
{
	//Settings::GetSettngs(Settings::Config());
}

void Game::LoadMap(string fileName)
{
	std::vector<GameObject *> res =  map.LoadFromFile(fileName, dynamicObjects);
	player = (Knight *)res[0];
	princess = (Princess *)res[1];
}


void Game::RunGame()
{
	bool quit = false;

	while (!quit)
	{
		
		char key;
		clear();
		map.Print();
		printw("Health: %d", player->Health());
		refresh();
		int x, y;
		player->GetPosition(x, y);
		nokey:
		key = _getch();
		GameObject *go;
		switch (key)
		{
		case 's':
			player->SetPosition(x, y + 1, map);
			break;
		case 'w':
			player->SetPosition(x, y - 1, map);
			break;
		case 'a':
			player->SetPosition(x - 1, y, map);
			break;
		case 'd':
			player->SetPosition(x + 1, y, map);
			break;
		case 'f':
			go = player->Shoot(map);
			if (go)
				dynamicObjects.push_back(go);
			break;
		case 'v':
			break;
		default:
			goto nokey;
			break;
		}
		player->GetPosition(x, y);
		for (int i = 0; i < dynamicObjects.size(); i++)
		{
			if (dynamicObjects[i])
			{
				if (dynamicObjects[i]->state == Alive)
					dynamicObjects[i]->Act(map, dynamicObjects);
				if (dynamicObjects[i]->state == Dead)
				{
					int x, y;
					dynamicObjects[i]->GetPosition(x, y);
					if (map.objects[y][x] != player)
					{
						GameObject *go = new Floor(x, y);
						map.objects[y][x] = go;
					}
					delete dynamicObjects[i];
					dynamicObjects[i] = NULL;
					continue;
				}
				
			}
				
		}
		if (princess->safe)
		{
			clear();
			quit = true;
			mvprintw(10, 10, "You won!\n");
			//refresh();
		}
		if (player->state == Dead)
		{
			clear();
			quit = true;
			mvprintw(10, 10, "You lost!\n");
			//refresh();
		}
		
	}
}

void Game::Clear()
{
	map.objects.clear();
	dynamicObjects.clear();
}