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
	//Constructors
	Collider();
	Collider(Component* gameObject, Type type, float x, float y);
	~Collider();

	//Getters
	float GetX(){ return x; }
	float GetY(){ return y; }
	Component* GetGameObject() { return gameObject; }
	const Type GetType() { return type; }

	//Setters
	void SetPosition(const Vector2D* const vect);
	void SetPosition(const float x, const float y);

	//Checks if a point is contained within the collider
	virtual bool Contains(const float x, const float y) = 0;

	//Checks collision with another collider
	virtual bool CheckCollision(Collider* const collider) = 0;

	//Returns the current colliding colliders as a vector
	std::vector<Collider*> LookForCollisions();



protected:
	float x, y;

private:
	//Holds a pointer to the object that own this collider. It's the most crucial part.
	Component* gameObject;

	//Collider type, see enum
	Type type;

	//Holds a list of the colliders currently colliding
	std::vector<Collider*> collidees;

	//Every colliders currently existing
	static std::vector<Collider*> colliders;

};

