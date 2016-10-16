#include "Obstacle.h"



Obstacle::Obstacle()
{
}

Floor::Floor(int x, int y)
{
	this->x = x;
	this->y = y;
	this->atribute = oaInvis;
}

char Floor::Tile()
{
	return overlap == ' ' ? tile : overlap;
}

HardWall::HardWall(int x, int y)
{
	this->x = x;
	this->y = y;
	this->atribute = oaInvis;
}

char HardWall::Tile()
{
	return tile;
}
