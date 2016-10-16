#include "Map.h"
#include "curses.h"



Map::Map()
{
}

void Map::Print()
{
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = 0; j < objects[i].size(); j++)
		{
			addch(objects[i][j]->Tile());
		}
		addch('\n');
	}
}

std::vector<std::string> Map::StrMap()
{
	return std::vector<std::string>();
}
