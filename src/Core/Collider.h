#pragma once
#include <vector>
#include "Utils.h"
#include <math.h>
#include <iostream>
#include "Component.h"

enum Type
{
	RECTANGLE,
	CIRCLE,
	SPHERE,
	BOX
};

class Collider
{

public:
	//Constructors
	Collider();
	Collider(Component* gameObject, Type type, float x, float y);
	Collider(Component* gameObject, Type type, float x, float y, float z);
	~Collider();

	//Getters
	D3DXVECTOR2 GetPosition() { return position; }
	D3DXVECTOR3 GetPosition3D() { return position3D; }
	Component* GetGameObject() { return gameObject; }
	const Type GetType() { return type; }
	void SetEnabled(bool isEnabled) { this->isEnabled = isEnabled; }

	//Setters
	void SetPosition(const float x, const float y);
	void SetPosition3D(const float x, const float y, const float z);

	//Checks if a point is contained within the collider
	virtual bool Contains(const float x, const float y) = 0;
	virtual bool Contains3D(const float x, const float y, const float z) = 0;

	//Checks collision with another collider
	virtual bool CheckCollision(Collider* const collider) = 0;

	//Returns the current colliding colliders as a vector
	std::vector<Collider*> LookForCollisions();

protected:
	D3DXVECTOR2 position;
	D3DXVECTOR3 position3D;

private:
	//Holds a pointer to the object that own this collider. It's the most crucial part.
	Component* gameObject;

	//Collider type, see enum
	Type type;

	//Will trigger collisions or not. true by default.
	bool isEnabled;

	//Holds a list of the colliders currently colliding
	std::vector<Collider*> collidees;

	//Every colliders currently existing
	static std::vector<Collider*> colliders;

};

