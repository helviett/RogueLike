#pragma once

#include "GameObject.h"

enum ObstacleAtribute
{
	oaInvis, oaDim, oaNormal
};

class Obstacle : public GameObject
{
public:
	Obstacle();
protected:
	ObstacleAtribute atribute;
	char overlap;
};

class Floor : public Obstacle
{
public:
	Floor(int x, int y);
	char Tile() override;
};

class HardWall : public Obstacle
{
public:
	HardWall(int x, int y);
	char Tile();
};
