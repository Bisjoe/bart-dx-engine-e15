#pragma once
#include <vector>
#include <math.h>
#include "Vector.h"
#include <iostream>
#include "Component.h"

enum Type
{
	RECTANGLE,
	CIRCLE
};

class Collider
{

public:
	Collider();
	Collider(Component* gameObject, Type type, float x, float y);
	~Collider();

	float  GetX(){ return x; }
	float  GetY(){ return y; }
	Component* GetGameObject() { return gameObject; }
	const Type GetType() { return type; }

	void SetPosition(const Vector2D* const vect);
	void SetPosition(const float x, const float y);

	virtual bool Contains(const float x, const float y) { return false; }
	virtual bool CheckCollision(Collider* const collider) { return false; }

	std::vector<Collider*> LookForCollisions();

	std::vector<Collider*> collidees;
	static std::vector<Collider*> colliders;
	Component* gameObject;
	Type type;
	float x, y;


protected:
};

