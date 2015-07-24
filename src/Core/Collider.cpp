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
Collider::Collider(Component* gameObject, Type type, float x, float y, float z)
	:type(type)
	,gameObject(gameObject)
	,position3D(x,y,z)
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
void Collider::SetPosition3D(const float x, const float y, const float z)
{
	this->position3D.x = x;
	this->position3D.y = y;
	this->position3D.z = z;
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
