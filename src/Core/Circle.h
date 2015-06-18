#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Collider.h"

class Circle : public Collider
{
private:

	//Our circle's radius
	float radius;

public:
	//Our defaults
	Circle();
	~Circle();

	//Our special constructors, we always need a point and a radius.
	Circle(float x, float y, float radius);

	//Returns whether or not a point is contained in a circle, it considers points ON the circle as WITHIN it.
	bool Contains(const float x, const float y);

	//Getters

	float GetRadiusSq() const { return sqrt(radius); };
	float GetRadius() const { return radius; };

	//Returns whether or not two circles collide with each other
	bool CollidesWith(const Circle* const circ);

	//Returns whether our circle collides with a rectangle, and vice versa.
	bool CollidesWith(const Rectangle2* const rect); //Bonus

};


#endif