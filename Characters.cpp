#include "Characters.h"
#include <iostream>
#include <cstdlib>

void Character::GetFurtherPosition(int & nx, int & ny)
{
	nx = this->nx;
	ny = this->ny;
}

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

CharState Character::State()
{
	return this->state;
}

void Knight::SetPosition(int x, int y, std::vector<std::string> &map)
{
	if (x < 0 || y < 0)
		exit(1);
	switch (map[y][x])
	{
	case '.':
		map[this->y][this->x] = '.';
		map[y][x] = 'K';
		this->y = y;
		this->x = x;
		break;
	case '#':
		break;
	case 'P':
		exit(0);
		break;
	default:
		
		break;
	}
}

void Knight::GetPosition(int &x, int &y)
{
	x = this->x;
	y = this->y;
}

void Knight::Collide(Character *ch)
{
	ch->Collide(this);
}

void Knight::Collide(Zombie *z)
{
	this->health -= z->Damage();
	state = health <= 0 ? Dead : Alive;
	z->TakeDamage(this->damage);
}

void Knight::Collide(Knight * k)
{
}

void Knight::Collide(GameObject * go)
{
	go->Collide(this);
}

void Knight::Move(int x, int y)
{
	this->nx = x;
	this->ny = y;
}

char Knight::Tile()
{
	return this->tile;
}

Knight::Knight(int x, int y)
{
	this->x = x;
	this->y = y;
	damage = 10;
	health = 100;
	this->state = Alive;
	this->tile = 'K';
}

void Zombie::Collide(GameObject * go)
{
	go->Collide(this);
}

void Zombie::Collide(Character * ch)
{
	ch->Collide(this);
}

void Zombie::Collide(Zombie * z)
{
}

void Zombie::Collide(Knight * k)
{
	this->health -= k->Damage();
	state = health <= 0 ? Dead : Alive;
	k->TakeDamage(damage);

}

void Zombie::Move(int x, int y)
{
	this->nx = x;
	this->ny = y;
}
bool ableToMove(int x, int y, std::vector<std::string> &map)
{
	if (y >= map.size() || x >= map[y].size())
		return false;
	if (map[y][x] == '.' || map[y][x] == 'K')
		return true;
	return false;
}

bool dfs(int x, int y, std::vector<std::string> &map, int n, int m)
{
	bool up, down, right, left;
	if (map[x][y] == 'K')
		return true;
	if (n == m)
		return false;
	if (ableToMove(x + 1, y, map))
		 right = dfs(x + 1, y, map, n + 1, m);
	if (ableToMove(x - 1, y, map))
		left = dfs(x - 1, y, map, n + 1, m);
	if (ableToMove(x, y + 1, map))
		down =  dfs(x, y + 1, map, n + 1, m);
	if (ableToMove(x, y - 1, map))
		up = dfs(x, y - 1, map, n + 1, m);
	return right || left || down || up;
}

pair<int,int> bfs(int x, int y, vector<string> &map, int n, int m)
{
	struct lvledV
	{
		pair<int, int> p;
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
	p[y][x] = make_pair(-1, -1);
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

void Zombie::Act(vector<string> &map)
{
	std::vector<string> copy(map);
	pair<int, int> res = bfs(this->x, this->y, copy, 5, 0);
	if (res.first != -1 && res.second != -1)
		Move(res.first, res.second);
	else
	{
		int direction = rand() % 4 + 1;
		switch (direction)
		{
		case 1:
			Move(x + 1, y);
			break;
		case 2:
			Move(x - 1, y);
			break;
		case 3:
			Move(x, y + 1);
			break;
		case 4:
			Move(x, y - 1);
			break;
		}
	}
	
}

void Zombie::SetPosition(int x, int y, std::vector<std::string>& map)
{
	if (x < 0 || y < 0)
		exit(1);
	switch (map[y][x])
	{
	case '.':
		map[this->y][this->x] = '.';
		map[y][x] = 'Z';
		this->y = y;
		this->x = x;
		break;
	default:
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
	damage = 10;
	health = 20;
	this->state = Alive;
	this->nx = 0;
	this->ny = 0;
	this->tile = 'Z';
}