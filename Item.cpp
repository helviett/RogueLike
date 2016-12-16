#include "Item.h"

const int HEALTH_POTION_FOREGROUND = Settings::Config()["Items"]["HealthPotion"]["Foreground"];;
const int HEALTH_POTION_BACKGROUND = Settings::Config()["Items"]["HealthPotion"]["Background"];

Item::Item()
{
}

HealthPotion::HealthPotion()
{
}

HealthPotion::HealthPotion(int x, int y)
{
	this->x = x;
	this->y = y;
	this->tile = '+';
	this->foreground = HEALTH_POTION_FOREGROUND;
	this->background = HEALTH_POTION_BACKGROUND;
}

void HealthPotion::Collide(GameObject * go)
{
	go->Collide(this);
}

void HealthPotion::Collide(Knight * k)
{
	k->Collide(this);
}

void HealthPotion::Collide(Zombie * z)
{
}

void HealthPotion::Collide(Floor * f)
{
}

void HealthPotion::Collide(HardWall * hw)
{
}

void HealthPotion::Collide(Dragon * d)
{
}

void HealthPotion::Collide(Arrow * a)
{
}

void HealthPotion::Collide(Fireball * fb)
{
	this->state = Dead;
}

void HealthPotion::Collide(HealthPotion * hp)
{
}

void HealthPotion::Collide(Princess * p)
{
}
