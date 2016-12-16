#include "Obstacle.h"
#include "Projectile.h"


Obstacle::Obstacle()
{
}

void Floor::Collide(GameObject * go)
{
}

void Floor::Collide(Knight * k)
{
}

void Floor::Collide(Zombie * z)
{
}

void Floor::Collide(Floor * f)
{
}

void Floor::Collide(HardWall * hw)
{
}

void Floor::Collide(Dragon * d)
{
}

void Floor::Collide(Arrow * a)
{
}

void Floor::Collide(Fireball * fb)
{
}

void Floor::Collide(HealthPotion * hp)
{
}

void Floor::Collide(Princess * p)
{
}

Floor::Floor(int x, int y)
{
	this->x = x;
	this->y = y;
	this->atribute = oaInvis;
	this->tile = '.';

	this->foreground = Settings::Config()["Obstacles"]["Floor"]["Foreground"];
	this->background = Settings::Config()["Obstacles"]["Floor"]["Background"];
}

char Floor::Tile()
{
	return tile;
}

void HardWall::Collide(GameObject * go)
{
}

void HardWall::Collide(Knight * k)
{
}

void HardWall::Collide(Zombie * z)
{
}

void HardWall::Collide(Floor * f)
{
}

void HardWall::Collide(HardWall * hw)
{
}

void HardWall::Collide(Dragon * d)
{
}

void HardWall::Collide(Arrow * a)
{
	a->Collide(this);
}

void HardWall::Collide(Fireball * fb)
{
	fb->Collide(this);
}

void HardWall::Collide(HealthPotion * hp)
{
}

void HardWall::Collide(Princess * p)
{
}

HardWall::HardWall(int x, int y)
{
	this->x = x;
	this->y = y;
	this->atribute = oaInvis;
	this->tile = '#';
	this->foreground = Settings::Config()["Obstacles"]["HardWall"]["Foreground"];
	this->background = Settings::Config()["Obstacles"]["HardWall"]["Background"];
}

char HardWall::Tile()
{
	return tile;
}
