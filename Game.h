#pragma once

#include "Characters.h"
#include <vector>
#include <string>
#include <memory>

using namespace std;

class Game
{
public:
	Game();
	void LoadMap(string fileName);
	void PrintMap();
	void RunGame();
private:
	void CreateCharacters();
	void UpdateGame();
	vector<string> map;
	Knight *player;
	vector<Monster *> monsters;
	//shared_ptr<Knight> player;
};

