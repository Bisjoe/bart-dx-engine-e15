#include "Collider.h"
#include <iostream>

std::vector<Collider*> Collider::colliders;

Collider::Collider()
	:isEnabled(true)
{
	isEnabled = true;
	colliders.push_back(this);
}

Collider::Collider(Component* gameObject, Type type, float x, float y)
	:type(type)
	,gameObject(gameObject)
	,position(x, y)
	,isEnabled(true)
{
	
	colliders.push_back(this);
}

Collider::~Collider()
{

}


void Collider::SetPosition(const float x, const float y)
{
	this->position.x = x;
	this->position.y = y;
}

std::vector<Collider*> Collider::LookForCollisions()
{
	collidees.clear();
	for each (Collider* col in Collider::colliders)
	{
		if (col != this && CheckCollision(col) && col->isEnabled)
		{
			collidees.push_back(col);
		}
	}
	return collidees;
}
