#pragma once

#include "Characters.h"
#include <vector>
#include <string>
#include <memory>

using namespace std;

class Map;

class Game
{
public:
	Game();
	void LoadMap(string fileName);
	void RunGame();
	void Clear();
private:
	Map map;
	Knight *player;
	Princess *princess;
	vector<GameObject *> dynamicObjects;
};

