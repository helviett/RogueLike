#pragma once

#include <vector>
#include <string>

class GameObject;

class Map
{
public:
	Map();
	void Print();
	void Update();
	std::vector<GameObject *> LoadFromFile(std::string fileName, std::vector<GameObject *> &dobj);
	std::vector<std::string> StrMap();
	std::vector<std::vector<GameObject *>> objects;
};

