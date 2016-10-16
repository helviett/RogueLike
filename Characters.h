#pragma once

#include "GameObject.h"
#include <vector>
#include <string>
#include <memory>
#include <ctime>
#include <queue>

using namespace std;

class Knight;
class Princess;
class Zombie;
class Dragon;
class Monster;

enum CharState
{
	Dead, Alive
};

class Character : public GameObject
{
public:
	virtual void GetFurtherPosition(int &nx, int &ny);
	virtual void Collide(Character *ch) = 0;
	virtual void Collide(Zombie *z) = 0;
	virtual void Collide(Knight *k) = 0;
	virtual void Move(int x, int y) = 0;
	virtual char Tile() = 0;
	virtual void TakeDamage(int dmg);
	virtual int Health();
	virtual int Damage();
	virtual CharState State();
protected:
	int health, damage, nx, ny;
	CharState state;
};

class Knight : public Character
{
public:
	void SetPosition(int x, int y, vector<string> &map) override;
	void GetPosition(int &x, int &y) override;
	void Collide(Character *ch) override;
	void Collide(Zombie *z) override;
	void Collide(Knight *k) override;
	void Collide(GameObject *go) override;
	virtual void Move(int x, int y) override;
	char Tile() override;
	Knight(int x, int y);
private:

};



class Monster : public Character
{
public:
	virtual void Act(vector<string> &map) = 0;
protected:

};

class Zombie : public Monster
{
public:
	void Collide(GameObject *go) override;
	void Collide(Character *ch) override;
	void Collide(Zombie *z) override;
	void Collide(Knight *k) override;
	void Move(int x, int y) override;
	void Act(vector<string> &map) override;
	void SetPosition(int x, int y, vector<string> &map) override;
	char Tile() override;
	Zombie(int x, int y);
};

bool ableToMove(int x, int y, vector<string> &map);
//class Dragon : public Monster
//{
//public:
//	void Collide(Character *ch) override;
//	void Collide(Zombie *z) override;
//	void Collide(Knight *k) override;
//	void Collide(Princess *p) override;
//	void Collide(Monster *m) override;
//	void Collide(Dragon *d) override;
//	Dragon(int x, int y);
//};
