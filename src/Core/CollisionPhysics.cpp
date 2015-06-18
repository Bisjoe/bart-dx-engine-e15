#include "CollisionPhysics.h"



CollisionPhysics::CollisionPhysics()
{
}


CollisionPhysics::~CollisionPhysics()
{
}


bool CollisionPhysics::CollidesWith(const Circle* const circ)
{
	return (pow(circ->GetX() - this->GetX(), 2) + pow(circ->GetY() - this->GetY(), 2)) <= pow(this->GetRadius() + circ->GetRadius(), 2);
}

D3DX

