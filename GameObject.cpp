#include "GameObject.h"



GameObject::GameObject()
{
}

void GameObject::SetPosition(int x, int y, Map &map)
{
	this->x = x;
	this->y = y;
}

void GameObject::GetPosition(int & x, int & y)
{
	x = this->x;
	y = this->y;
}

void GameObject::Act(Map & map, std::vector<GameObject *> &dobj)
{

}

char GameObject::Tile()
{
	return tile;
}

int GameObject::Foreground()
{
	return this->foreground;
}

int GameObject::Background()
{
	return this->background;
}

