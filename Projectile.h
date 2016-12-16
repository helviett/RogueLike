#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile();
	Projectile(int x, int y);
	int Damage();

	
protected:
	int damage, strength, speed;
};

class Arrow : public Projectile
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

	void Act(Map &map, std::vector<GameObject *> &dobj);
	void SetPosition(int x, int y, Map &map);
	Arrow(int x, int y, std::pair<int, int> direction);
};

class Fireball : public Projectile
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

	void Act(Map &map, std::vector<GameObject *> &dobj);
	void SetPosition(int x, int y, Map &map);
	Fireball(int x, int y, std::pair<int, int> direction);
};
