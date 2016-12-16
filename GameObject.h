#pragma once


#include "Map.h"
#include "Settings.h"
#include <string>
#include <vector>

class Dragon;
class Zombie;
class Knight;
class Floor;
class HardWall;
class Arrow;
class Fireball;
class HealthPotion;
class Princess;

enum ObjState
{
	Dead, Alive
};

class GameObject
{
public:
	GameObject();

	virtual void Collide(Zombie *z) = 0;
	virtual void Collide(Knight *k) = 0;
	virtual void Collide(GameObject *go) = 0;
	virtual void Collide(HardWall *hw) = 0;
	virtual void Collide(Floor *f) = 0;
	virtual void Collide(Dragon *d) = 0;
	virtual void Collide(Arrow *a) = 0;
	virtual void Collide(Fireball *fb) = 0;
	virtual void Collide(HealthPotion *hp) = 0;
	virtual void Collide(Princess *p) = 0;

	virtual void SetPosition(int x, int y, Map &map);
	virtual void GetPosition(int &x, int &y);
	virtual void Act(Map &map, std::vector<GameObject *> &dobj);
	virtual char Tile();
	virtual int Foreground();
	virtual int Background();

	ObjState state;
protected:
	int x, y;
	char tile;
	bool used;
	int  foreground, background;
	std::pair<int, int> direction;
};

