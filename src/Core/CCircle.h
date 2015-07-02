#ifndef CCircle_HPP
#define CCircle_HPP

#include "Collider.h"

class CRectangle;

class CCircle : public Collider
{
public:
	//Our defaults
	CCircle();
	~CCircle();

	//Our special constructors, we always need a point and a radius.
	CCircle(Component* caller, float x, float y, float radius);

	//Returns whether or not a point is contained in a CCircle, it considers points ON the CCircle as WITHIN it.
	bool Contains(const float x, const float y);

	//Getters
	float GetRadiusSq() const { return sqrt(radius); };
	float GetRadius() const { return radius; };

	//Returns whether or not two CCircles collide with each other
	bool CollidesWith(CCircle* const circ);

	//Returns whether our CCircle collides with a rectangle, and vice versa.
	bool CollidesWith(CRectangle* const rect); //Bonus
	bool CheckCollision(Collider* const collider);

private:
	//Our CCircle's radius
	float radius;

};

#endif
