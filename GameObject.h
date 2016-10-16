#pragma once

#include <string>
#include <vector>

class Zombie;
class Knight;

class GameObject
{
public:
	GameObject();
	virtual void Collide(Zombie *z) = 0;
	virtual void Collide(Knight *k) = 0;
	virtual void Collide(GameObject *go) = 0;
	virtual void SetPosition(int x, int y, std::vector<std::string> &map);
	virtual void GetPosition(int &x, int &y);
	virtual char Tile() = 0;
protected:
	int x, y;
	char tile;
};

