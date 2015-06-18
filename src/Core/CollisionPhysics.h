#pragma once
#include "Common.h"

class CollisionPhysics
{
public:
	CollisionPhysics();
	~CollisionPhysics();

	bool CollidesWith();
	D3DXVECTOR2 CollisionResult();

	float GetX() const { return x; };
	float GetY() const { return y; };
	float GetRadius() const { return radius; }


private:

	float x, y;
	float radius;

};


