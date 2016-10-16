#include "Game.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include "curses.h"

#define DEAD NULL

Game::Game()
{

}

void Game::LoadMap(string fileName)
{
	ifstream fin(fileName);
	if (fin.fail())
	{
		cout << "File doesn't exist" << endl;
		exit(1);
	}
	string line;
	while (getline(fin, line))
	{
		map.push_back(line);
	}
	CreateCharacters();
	PrintMap();
}

vector<pair<int, int>> bfs(int x, int y, vector<string> &map, int n, int m)
{
	struct lvledV
	{
		pair<int, int> p;
		int lvl;
		lvledV(pair<int, int> p, int lvl)
		{
			this->p = p;
			this->lvl = lvl;
		}
		lvledV()
		{

		}
	};
	queue<lvledV> q;
	q.push(lvledV(make_pair(x, y), 0));
	vector<pair<int, int>> p;
	lvledV cur;
	while (!q.empty())
	{
		cur = q.front();
		q.pop();
		if (map[cur.p.second][cur.p.first] != 'K')
			p.push_back(cur.p);
		if (cur.lvl >= n)
			continue;
		map[cur.p.second][cur.p.first] = '#';
		if (ableToMove(cur.p.first + 1, cur.p.second, map))
		{
			q.push(lvledV(make_pair(cur.p.first + 1, cur.p.second), cur.lvl + 1));
		}
		if (ableToMove(cur.p.first - 1, cur.p.second, map))
		{
			q.push(lvledV(make_pair(cur.p.first - 1, cur.p.second), cur.lvl + 1));
		}
		if (ableToMove(cur.p.first, cur.p.second + 1, map))
		{
			q.push(lvledV(make_pair(cur.p.first, cur.p.second + 1), cur.lvl + 1));
		}
		if (ableToMove(cur.p.first, cur.p.second - 1, map))
		{
			q.push(lvledV(make_pair(cur.p.first, cur.p.second - 1), cur.lvl + 1));
		}
	}
	return p;
}

void Game::PrintMap()
{
	clear();
	int x, y;
	player->GetPosition(x, y);
	/*for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (y - i < -2 || y - i > 2)
				addch(map[i][j] | A_INVIS);
			else if (x - j < -6 || x - j > 6)

				addch(map[i][j] | A_INVIS);
			else
			{
				addch(map[i][j]);
			}
		}
		addch('\n');
	}*/
	for (int i = 0; i < map.size(); i++)
	{
		addstr(map[i].c_str());
		addch('\n');
		//printf("%s\n", map[i].c_str());a
		//cout << map[i] << endl;
	}
}

void Game::CreateCharacters()
{
	Monster *m;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			switch (map[i][j])
			{
			case 'K':
				player = new Knight(j, i);// shared_ptr<Knight> = (new Knight) Knight(&&Knight
				break;
			case 'Z':
				m = new Zombie(j, i);
				monsters.push_back(m);
				break;
			default:
				break;
			}
		}
	}
}

void Game::UpdateGame()
{
	int pfx, pfy, px, py; bool mfreeToMove = true;
	player->GetFurtherPosition(pfx, pfy);
	player->GetPosition(px, py);
	for (int i = 0; i < monsters.size(); i++)
	{
		if (monsters[i] == DEAD)
			continue;
		int mfx, mfy, my, mx;
		monsters[i]->GetFurtherPosition(mfx, mfy);
		monsters[i]->GetPosition(mx, my);
		if ((mfx == px && mfy == py) || (mx == pfx && my == pfy) || (mfx == pfx && mfy == pfy))
		{
			mfreeToMove = false;
			monsters[i]->Collide(player);
			if (monsters[i]->State() == Dead)
			{
				
				map[my][mx] = '.';
				delete monsters[i];
				monsters[i] = DEAD;
				
			}
			if (player->State() == Dead)
			{
				exit(0);
			}
		}
		if (mfreeToMove)
			monsters[i]->SetPosition(mfx, mfy, map);
	}
	player->SetPosition(pfx, pfy, map);
}


void Game::RunGame()
{
	bool quit = false;

	while (!quit)
	{
		char key;
		PrintMap();
		int px, py;
		player->GetPosition(px, py);
		printw("Current HP: %d\n", player->Health());
		refresh();
		nokey:
		key = _getch();
		switch (key)
		{
		case 's':
			player->Move(px, py + 1);
			break;
		case 'w':
			player->Move(px, py - 1);
			break;
		case 'a':
			player->Move(px - 1, py);
			break;
		case 'd':
			player->Move(px + 1, py);
			break;
		case 'f':
			break;
		default:
			goto nokey;
			break;
		}
		for (int i = 0; i < monsters.size(); i++)
		{
			if (monsters[i] != DEAD)
				monsters[i]->Act(map);
		}
		UpdateGame();
	}
}