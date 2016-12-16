#pragma once

#include "GameObject.h"
#include "Characters.h"

class Item : public GameObject
{
public:
	Item();
};

class HealthPotion : public Item
{
public:
	HealthPotion();
	HealthPotion(int x, int y);
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
};