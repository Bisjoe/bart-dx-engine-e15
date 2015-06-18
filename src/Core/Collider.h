#pragma once
#include <vector>
#include <math.h>
#include "Vector.h"

class Rectangle2;
class Circle;

class Collider
{
friend class Engine;

public:
	Collider(bool isActive);
	~Collider();

	virtual void Start() {} //= 0;
	virtual void Update(){} //= 0;
	virtual void Stop()  {} //= 0;
	virtual void Kill()  {} //= 0;

	virtual void SetActive(bool toggle) { isActive = toggle; };

	float GetX(){ return x; }
	float GetY(){ return y; }

	void SetPosition(const Vector2D* const vect);
	void SetPosition(const float x, const float y);

	virtual bool CollidesWith(const Rectangle2* const rect);
	virtual bool CollidesWith(const Circle* const circ);

	virtual bool Contains();

	bool CheckCollision(const Collider* const collider);

private:
	//DO NOT USE
	Collider();

	// Components vectors
	static std::vector<Collider*> components;
	static std::vector<Collider*> toAdd;
	static std::vector<Collider*> toDelete;
	static std::vector<Collider*> removed;

	bool isActive;
	std::string TAG;

	float x, y;
};

