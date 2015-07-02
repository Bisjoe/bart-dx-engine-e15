#include "Collider.h"
#include <iostream>

std::vector<Collider*> Collider::colliders;

Collider::Collider()
{
	colliders.push_back(this);
}

Collider::Collider(Component* gameObject, Type type, float x, float y)
	:type(type)
	,gameObject(gameObject)
	,x(x)
	,y(y)
{
	colliders.push_back(this);
}

Collider::~Collider()
{

}

std::vector<Collider*> Collider::LookForCollisions()
{
	collidees.clear();
	for each (Collider* col in Collider::colliders)
	{
		if (col != this && CheckCollision(col))
		{
			collidees.push_back(col);
		}
	}
	return collidees;
}
