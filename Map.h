#pragma once

#include "GameObject.h"
#include <vector>

class Map
{
public:
	Map();
	void Print();
	std::vector<std::string> StrMap();
	std::vector<std::vector<GameObject *>> objects;
};

