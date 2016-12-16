#pragma once

#include "GameObject.h"
#include <vector>
#include <string>
#include <memory>
#include <ctime>
#include <queue>


class Character : public GameObject
{
public:
	virtual char Tile() = 0;
	virtual void TakeDamage(int dmg);

	virtual int Health();
	virtual int Damage();
	virtual ObjState State();
protected:
	int health, damage, nx, ny;
};

class Knight : public Character
{
public:
	void SetPosition(int x, int y, Map &map) override;
	void GetPosition(int &x, int &y) override;
	void Collide(GameObject *go) override;
	void Collide(Knight *k) override;
	void Collide(Zombie *z) override;
	void Collide(Floor *f) override;
	void Collide(HardWall *hw) override;
	void Collide(Dragon *d) override;
	void Collide(Arrow *a) override;
	void Collide(Fireball *fb) override;
	void Collide(HealthPotion *hp) override;
	void Collide(Princess *p) override;

	GameObject *Shoot(Map &map);
	char Tile() override;
	Knight(int x, int y);
private:

};

class Princess : public Character
{
public:
	void Collide(GameObject *go) override;
	void Collide(Knight *k) override;
	void Collide(Zombie *z) override;
	void Collide(Floor *f) override;
	void Collide(HardWall *hw) override;
	void Collide(Dragon *d) override;
	void Collide(Arrow *a) override;
	void Collide(Fireball *fb) override;
	void Collide(HealthPotion *hp) override;
	void Collide(Princess *p) override;
	char Tile() override;

	bool safe;
	Princess(int x, int y);
};

class Monster : public Character
{
public:
protected:

};

class Zombie : public Monster
{
public:
	void Collide(GameObject *go) override;
	void Collide(Knight *k) override;
	void Collide(Zombie *z) override;
	void Collide(Floor *f) override;
	void Collide(HardWall *hw) override;
	void Collide(Dragon *d) override;
	void Collide(Arrow *a) override;
	void Collide(Fireball *fb) override;
	void Collide(HealthPotion *hp) override;
	void Collide(Princess *p) override;

	void Act(Map &map, std::vector<GameObject *> &dobj) override;
	void SetPosition(int x, int y, Map &map) override;
	char Tile() override;
	Zombie(int x, int y);
};
bool isArrow(char tile);
bool ableToMove(int x, int y, std::vector<std::string> &map);

class Dragon : public Monster
{
public:
	void Collide(GameObject *go) override;
	void Collide(Knight *k) override;
	void Collide(Zombie *z) override;
	void Collide(Floor *f) override;
	void Collide(HardWall *hw) override;
	void Collide(Dragon *d) override;
	void Collide(Arrow *a) override;
	void Collide(Fireball *fb) override;
	void Collide(HealthPotion *hp) override;
	void Collide(Princess *p) override;
	
	GameObject *Fire(Map &map);
	void Act(Map &map, std::vector<GameObject *> &dobj) override;
	void SetPosition(int x, int y, Map &map) override;
	char Tile() override;
	Dragon(int x, int y);
};
