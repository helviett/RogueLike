#include "Projectile.h"
#include "Characters.h"
#include "Map.h"
#include "Obstacle.h"
#include "Item.h"


const int FIREBALL_DAMAGE = Settings::Config()["Projectiles"]["Fireball"]["Damage"];
const int FIREBALL_FOREGROUND = Settings::Config()["Projectiles"]["Fireball"]["Foreground"];
const int FIREBALL_BACKGROUND = Settings::Config()["Projectiles"]["Fireball"]["Background"];

const int ARROW_DAMAGE = Settings::Config()["Projectiles"]["Arrow"]["Damage"];

Projectile::Projectile()
{
}

Projectile::Projectile(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Projectile::Damage()
{
	return damage;
}

void Arrow::Act(Map & map, std::vector<GameObject *> &dobj)
{
	used = true;
	this->SetPosition(x + direction.first, y + direction.second, map);
}

void Arrow::SetPosition(int x, int y, Map & map)
{
	switch (map.objects[y][x]->Tile())
	{
	case '.':
		map.objects[y][x]->SetPosition(this->x, this->y, map);
		map.objects[this->y][this->x] = map.objects[y][x];
		map.objects[y][x] = this;
		this->x = x;
		this->y = y;
		break;
	default:
		map.objects[y][x]->Collide(this);
		break;
	}
	if (state == Dead)
		map.objects[this->y][this->x] = new Floor(this->x, this->y);
}

Arrow::Arrow(int x, int y, std::pair<int, int> direction)
{
	this->x = x;
	this->y = y;
	this->damage = ARROW_DAMAGE;
	this->direction = direction;
	if (this->direction.first == 1)
		tile = '>';
	else if (this->direction.first == -1)
		tile = '<';
	else if (this->direction.second == 1)
		tile = 'V';
	else
		tile = '^';
	this->state = Alive;
}

void Arrow::Collide(GameObject * go)
{
	go->Collide(this);
}

void Arrow::Collide(Knight * k)
{
}

void Arrow::Collide(Zombie * z)
{
	z->Collide(this);
}

void Arrow::Collide(Floor * f)
{
}

void Arrow::Collide(HardWall * hw)
{
	this->state = Dead;
}

void Arrow::Collide(Dragon * d)
{
	d->Collide(this);
}

void Arrow::Collide(Arrow * a)
{
}

void Arrow::Collide(Fireball * fb)
{
	this->state = Dead;
}

void Arrow::Collide(HealthPotion * hp)
{
	hp->state = Dead;
}

void Arrow::Collide(Princess * p)
{
}

void Fireball::Collide(GameObject * go)
{
}

void Fireball::Collide(Knight * k)
{
	k->Collide(this);
}

void Fireball::Collide(Zombie * z)
{
}

void Fireball::Collide(Floor * f)
{
}

void Fireball::Collide(HardWall * hw)
{
	this->state = Dead;
}

void Fireball::Collide(Dragon * d)
{
}

void Fireball::Collide(Arrow * a)
{
	a->state = Dead;
}

void Fireball::Collide(Fireball * fb)
{
}

void Fireball::Collide(HealthPotion * hp)
{
	hp->state = Dead;
}

void Fireball::Collide(Princess * p)
{
}

void Fireball::Act(Map & map, std::vector<GameObject *> &dobj)
{
	this->SetPosition(x + direction.first, y + direction.second, map);
}

void Fireball::SetPosition(int x, int y, Map & map)
{
	switch (map.objects[y][x]->Tile())
	{
	case '.':
		map.objects[y][x]->SetPosition(this->x, this->y, map);
		map.objects[this->y][this->x] = map.objects[y][x];
		map.objects[y][x] = this;
		this->x = x;
		this->y = y;
		break;
	default:
		map.objects[y][x]->Collide(this);
		break;
	}
	/*if (state == Dead)
		map.objects[this->y][this->x] = new Floor(this->x, this->y);*/
}

Fireball::Fireball(int x, int y, std::pair<int, int> direction)
{
	this->x = x;
	this->y = y;
	this->damage = FIREBALL_DAMAGE;
	this->foreground = FIREBALL_FOREGROUND;
	this->background = FIREBALL_BACKGROUND;
	this->direction = direction;
	this->tile = '*';
	this->state = Alive;
}
