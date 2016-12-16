#include "Characters.h"
#include "Obstacle.h"
#include "Projectile.h"
#include "Item.h"
#include <iostream>
#include <cstdlib>
#include "Settings.h"

void Character::TakeDamage(int dmg)
{
	this->health -= dmg;
	state = health <= 0 ? Dead : Alive;
}

int Character::Health()
{
	return this->health;
}

int Character::Damage()
{
	return this->damage;
}

ObjState Character::State()
{
	return this->state;
}

void Knight::SetPosition(int x, int y, Map &map)
{
	this->direction.first =  x - this->x;
	this->direction.second = y - this->y;
	switch (map.objects[y][x]->Tile())
	{
	case '.':
		map.objects[y][x]->SetPosition(this->x, this->y, map);
		map.objects[this->y][this->x] = map.objects[y][x];
		map.objects[y][x] = this;
		this->x = x;
		this->y = y;
		break;
	case '+':
		map.objects[y][x]->Collide(this);
		map.objects[y][x] = new Floor(x, y);
		SetPosition(x, y, map);
		break;
	case '#':
		break;
	default:
		map.objects[y][x]->Collide(this);
		break;
	}
}

void Knight::GetPosition(int &x, int &y)
{
	x = this->x;
	y = this->y;
}

void Knight::Collide(Zombie *z)
{
	this->health -= z->Damage();
	state = health <= 0 ? Dead : Alive;
}

void Knight::Collide(Floor * f)
{
}

void Knight::Collide(HardWall * hw)
{
}

void Knight::Collide(Dragon * d)
{
	this->health -= d->Damage();
	state = health <= 0 ? Dead : Alive;
}

void Knight::Collide(Arrow * a)
{
}

void Knight::Collide(Fireball * fb)
{
	this->health -= fb->Damage();
	state = health <= 0 ? Dead : Alive;
	fb->state = Dead;
}

void Knight::Collide(HealthPotion * hp)
{
	this->health += 100;
	hp->state = Dead;
}

void Knight::Collide(Princess * p)
{
	p->safe = true;
}

void Knight::Collide(Knight * k)
{
}

void Knight::Collide(GameObject * go)
{
	go->Collide(this);
}

GameObject * Knight::Shoot(Map &map)
{
	int x, y;
	x = this->x + this->direction.first;
	y = this->y + this->direction.second;
	if (x < 0 || y < 0)
		return NULL;
	if (map.objects[y][x]->Tile() == '.')
	{
		delete map.objects[y][x];
		map.objects[y][x] = new Arrow(x, y, this->direction);
		return map.objects[y][x];
	}
	return NULL;
	
}

char Knight::Tile()
{
	return this->tile;
}

Knight::Knight(int x, int y)
{
	this->x = x;
	this->y = y;
	damage = Settings::Config()["Characters"]["Knight"]["Damage"];
	health = Settings::Config()["Characters"]["Knight"]["Health"];
	this->state = Alive;
	this->tile = 'K';
	this->direction = std::make_pair<int, int>(1, 1);
	this->foreground = Settings::Config()["Characters"]["Knight"]["Foreground"];
	this->background = Settings::Config()["Characters"]["Knight"]["Background"];;
}

void Zombie::Collide(GameObject * go)
{
	go->Collide(this);
}

void Zombie::Collide(Zombie * z)
{
}

void Zombie::Collide(Floor * f)
{
}

void Zombie::Collide(HardWall * hw)
{
}

void Zombie::Collide(Dragon * d)
{
}

void Zombie::Collide(Arrow * a)
{
	this->health -= a->Damage();
	state = health <= 0 ? Dead : Alive;
	a->state = Dead;
}

void Zombie::Collide(Fireball * fb)
{
	this->health -= fb->Damage();
	state = health <= 0 ? Dead : Alive;
	fb->state = Dead;
}

void Zombie::Collide(HealthPotion * hp)
{
}

void Zombie::Collide(Princess * p)
{
}

void Zombie::Collide(Knight * k)
{
	this->health -= k->Damage();
	state = health <= 0 ? Dead : Alive;

}

bool isArrow(char tile)
{
	return tile == 'V' || tile == '^' || tile == '<' || tile == '>';
}

bool ableToMove(int x, int y, std::vector<std::string> &map)
{
	if (y >= map.size() || x >= map[y].size())
		return false;
	if (map[y][x] == '.' || map[y][x] == 'K' || map[y][x] == '*' || isArrow(map[y][x]))
		return true;
	return false;
}

std::pair<int,int> bfs(int x, int y, std::vector<std::string> &map, int n, int m)
{
	struct lvledV
	{
		std::pair<int, int> p;
		int lvl;
		lvledV(std::pair<int, int> p, int lvl)
		{
			this->p = p;
			this->lvl = lvl;
		}
		lvledV()
		{

		}
	};
	std::queue<lvledV> q;
	q.push(lvledV(std::make_pair(x, y), 0));
	std::vector<std::vector<std::pair<int, int>>> p;
	for (int i = 0; i < map.size(); i++)
	{
		std::vector<std::pair<int, int>> v(map[i].size());
		p.push_back(v);
	}
	p[y][x] = std::make_pair(-1, -1);
	lvledV cur;
	while (!q.empty())
	{
		cur = q.front();
		q.pop();
		if (map[cur.p.second][cur.p.first] == 'K')
			break;
		if (cur.lvl >= n)
			continue;
		map[cur.p.second][cur.p.first] = '#';
		if (ableToMove(cur.p.first + 1, cur.p.second, map))
		{
			q.push(lvledV(std::make_pair(cur.p.first + 1, cur.p.second), cur.lvl + 1));
			p[cur.p.second][cur.p.first + 1] = cur.p;
		}
		if (ableToMove(cur.p.first - 1, cur.p.second, map))
		{
			q.push(lvledV(std::make_pair(cur.p.first - 1, cur.p.second), cur.lvl + 1));
			p[cur.p.second][cur.p.first - 1] = cur.p;
		}
		if (ableToMove(cur.p.first, cur.p.second + 1, map))
		{
			q.push(lvledV(std::make_pair(cur.p.first, cur.p.second + 1), cur.lvl + 1));
			p[cur.p.second + 1][cur.p.first] = cur.p;
		}
		if (ableToMove(cur.p.first, cur.p.second - 1, map))
		{
			q.push(lvledV(std::make_pair(cur.p.first, cur.p.second - 1), cur.lvl + 1));
			p[cur.p.second - 1][cur.p.first] = cur.p;
		}
	}
	if (map[cur.p.second][cur.p.first] == 'K')
	{
		std::vector<std::pair<int, int>> path;
		for (std::pair<int, int> v = cur.p; v != p[y][x]; v = p[v.second][v.first])
		{
			path.push_back(v);
		}
		return path[path.size() - 2];
	}
	return p[y][x];
}

void Zombie::Act(Map &map, std::vector<GameObject *> &dobj)
{
	std::pair<int, int> res = bfs(this->x, this->y, map.StrMap(), 5, 0);
	if (res.first != -1 && res.second != -1)
		this->SetPosition(res.first, res.second, map);
	else
	{
		int direction = rand() % 5 + 1;
		switch (direction)
		{
		case 1:
			SetPosition(x - 1, y, map);
			break;
		case 2:
			SetPosition(x + 1, y, map);
			break;
		case 3:
			SetPosition(x, y + 1, map);
			break;
		case 4:
			SetPosition(x, y - 1, map);
			break;
		default:
			break;
		}
	}
}

void Zombie::SetPosition(int x, int y, Map &map)
{
	this->direction.first = x - this->x;
	this->direction.second = y - this->y;
	switch (map.objects[y][x]->Tile())
	{
	case '.':
		map.objects[y][x]->SetPosition(this->x, this->y, map);
		map.objects[this->y][this->x] = map.objects[y][x];
		map.objects[y][x] = this;
		this->x = x;
		this->y = y;
		break;
	case '#':
		break;
	default:
		map.objects[y][x]->Collide(this);
		if (this->state == Dead)
		{
			map.objects[this->y][this->x] = new Floor(this->x, this->y);
		}
		break;
	}
}

char Zombie::Tile()
{
	return this->tile;
}

Zombie::Zombie(int x, int y)
{
	this->x = x;
	this->y = y;
	damage = Settings::Config()["Characters"]["Zombie"]["Damage"];
	health = Settings::Config()["Characters"]["Zombie"]["Health"];
	this->state = Alive;
	this->nx = 0;
	this->ny = 0;
	this->tile = 'Z';
	this->foreground = Settings::Config()["Characters"]["Zombie"]["Foreground"];
	this->background = Settings::Config()["Characters"]["Zombie"]["Background"];
}

void Dragon::Collide(GameObject * go)
{
	go->Collide(this);
}

void Dragon::Collide(Knight * k)
{
	this->health -= k->Damage();
	state = health <= 0 ? Dead : Alive;
}

void Dragon::Collide(Zombie * z)
{
}

void Dragon::Collide(Floor * f)
{
}

void Dragon::Collide(HardWall * hw)
{
}

void Dragon::Collide(Dragon * d)
{
}

void Dragon::Collide(Arrow * a)
{
	this->health -= a->Damage();
	state = health <= 0 ? Dead : Alive;
	a->state = Dead;
}

void Dragon::Collide(Fireball * fb)
{
	
}

void Dragon::Collide(HealthPotion * hp)
{
}

void Dragon::Collide(Princess * p)
{
}

GameObject * Dragon::Fire(Map & map)
{
	int x, y;
	x = this->x + this->direction.first;
	y = this->y + this->direction.second;
	if (x < 0 || y < 0)
		return NULL;
	if (map.objects[y][x]->Tile() == '.')
	{
		delete map.objects[y][x];
		map.objects[y][x] = new Fireball(x, y, this->direction);
		return map.objects[y][x];
	}
	return NULL;
}

void Dragon::Act(Map & map, std::vector<GameObject *> &dobj)
{

	std::pair<int, int> res = bfs(this->x, this->y, map.StrMap(), 8, 0);
	if (res.first != -1 && res.second != -1)
	{
		this->direction.first = res.first - this->x;
		this->direction.second = res.second - this->y;
		if (this->direction.first != 0)
		{
			for (int i = 2; i <= 6; i++)
			{
				int shift = this->x + this->direction.first * i;
				if (shift > map.objects[y].size() || shift < 0)
					break;
				if (map.objects[this->y][shift]->Tile() == '#')
					break;
				if (map.objects[this->y][shift]->Tile() == 'K')
				{
					GameObject *go = this->Fire(map);
					if (go)
						dobj.push_back(go);
					return;
				}
					
			}
		}
		else
		{
			for (int i = 2; i < 6; i++)
			{
				int shift = this->y + this->direction.second * i;
				if (shift > map.objects.size() || shift < 0)
					break;
				if (map.objects[this->y + this->direction.second * i][this->x]->Tile() == '#')
					break;
				if (map.objects[this->y + this->direction.second * i][this->x]->Tile() == 'K')
				{
					GameObject *go = this->Fire(map);
					if (go)
						dobj.push_back(go);
					return;
				}

			}
		}
		this->SetPosition(res.first, res.second, map);
	}
	else
	{
		int direction = rand() % 5 + 1;
		switch (direction)
		{
		case 1:
			SetPosition(x - 1, y, map);
			break;
		case 2:
			SetPosition(x + 1, y, map);
			break;
		case 3:
			SetPosition(x, y + 1, map);
			break;
		case 4:
			SetPosition(x, y - 1, map);
			break;
		default:
			break;
		}
	}
}

void Dragon::SetPosition(int x, int y, Map & map)
{
	this->direction.first = x - this->x;
	this->direction.second = y - this->y;
	switch (map.objects[y][x]->Tile())
	{
	case '.':
		map.objects[y][x]->SetPosition(this->x, this->y, map);
		map.objects[this->y][this->x] = map.objects[y][x];
		map.objects[y][x] = this;
		this->x = x;
		this->y = y;
		break;
	case '#':
		break;
	default:
		map.objects[y][x]->Collide(this);
		break;
	}
}

char Dragon::Tile()
{
	return tile;
}

Dragon::Dragon(int x, int y)
{
	this->x = x;
	this->y = y;
	damage = Settings::Config()["Characters"]["Dragon"]["Damage"];
	health = Settings::Config()["Characters"]["Dragon"]["Health"];
	this->state = Alive;
	this->nx = 0;
	this->ny = 0;
	this->tile = 'D';
	this->foreground = Settings::Config()["Characters"]["Dragon"]["Foreground"];
	this->background = Settings::Config()["Characters"]["Dragon"]["Background"];
}

void Princess::Collide(GameObject * go)
{
	go->Collide(this);
}

void Princess::Collide(Knight * k)
{
	safe = true;
}

void Princess::Collide(Zombie * z)
{
}

void Princess::Collide(Floor * f)
{
}

void Princess::Collide(HardWall * hw)
{
}

void Princess::Collide(Dragon * d)
{
}

void Princess::Collide(Arrow * a)
{
}

void Princess::Collide(Fireball * fb)
{
}

void Princess::Collide(HealthPotion * hp)
{
}

void Princess::Collide(Princess * p)
{
}

char Princess::Tile()
{
	return tile;
}

Princess::Princess(int x, int y)
{
	this->x = x;
	this->y = y;
	this->state = Alive;
	this->tile = 'P';
	this->safe = false;
	this->foreground = Settings::Config()["Characters"]["Princess"]["Foreground"];
	this->background = Settings::Config()["Characters"]["Princess"]["Background"];
}
