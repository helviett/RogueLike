#include "Map.h"
#include "curses.h"
#include "Characters.h"
#include "Obstacle.h"
#include "Item.h"
#include <fstream>



Map::Map()
{
}

void Map::Print()
{
	start_color();
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = 0; j < objects[i].size(); j++)
		{
			
			init_pair(objects[i][j]->Tile(), objects[i][j]->Foreground(), objects[i][j]->Background());
			attron(COLOR_PAIR(objects[i][j]->Tile()));
			addch(objects[i][j]->Tile());
			attroff(COLOR_PAIR(objects[i][j]->Tile()));
			
		}
		addch('\n');
	}
	
}

void Map::Update()
{
	/*for (int i = 0; i < objects.size(); i++)
	{
		for (int j = 0; j < objects[i].size(); j++)
		{
			objects[i][j]->Act(*this, std::vector<GameObject *> dobj);
		}
	}*/
}

std::vector<GameObject *> Map::LoadFromFile(std::string fileName, std::vector<GameObject *> &dobj)
{
	std::ifstream fin(fileName);
	if (fin.fail())
	{
		exit(1);
	}
	objects.clear();
	GameObject *player = NULL;
	GameObject *princess = NULL;
	std::string line;
	int y = 0;
	while (getline(fin, line))
	{
		std::vector<GameObject *> vgo(line.size());
		for (int x = 0; x < line.size(); x++)
		{
			GameObject *go;
			switch (line[x])
			{
			case '.':
				go = new Floor(x, y);
				break;
			case 'K':
				go = new Knight(x, y);
				player = go;
				break;
			case 'Z':
				go = new Zombie(x, y);
				dobj.push_back(go);
				break;
			case '#':
				go = new HardWall(x, y);
				break;
			case 'D':
				go = new Dragon(x, y);
				dobj.push_back(go);
				break;
			case 'P':
				go = new Princess(x, y);
				princess = go;
				break;
			case '+':
				go = new HealthPotion(x, y);
				dobj.push_back(go);
				break;
			default:
				go = new HardWall(x, y);
				break;
			}
			vgo[x] = go;
		}
		objects.push_back(vgo);
		y++;
	}
	std::vector<GameObject *> res;
	res.push_back(player);
	res.push_back(princess);
	return res;
}


std::vector<std::string> Map::StrMap()
{
	std::vector<std::string> res;
	for (int i = 0; i < objects.size(); i++)
	{
		std::string line;
		line.reserve(objects[i].size());
		line.resize(objects[i].size());
		for (int j = 0; j < objects[i].size(); j++)
		{
			line[j] = objects[i][j]->Tile();
		}
		res.push_back(line);
	}
	return res;
}
