#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Collider.h"

class Rectangle : public Collider
{
private:

	//DO NOT USE
	Rectangle();

	//Rectangle's width and height.
	float width;
	float height;

	

public:
	//Our defaults.
	Rectangle(bool isActive);
	~Rectangle();

	//Our 'specials' constructors.
	Rectangle(float x, float y, float width, float height);

	//Wheter or not a point is contained within a rectangle, considers points ON the rectangle as part of the rectangle.
	bool Contains(const float x, const float y);

	//Getters
	float GetWidth() const { return width; }
	float GetHeight() const { return height; }

	//Setters
	void SetSize(const float w, const float h);

	//Determines if a rectangle collides with another rectangle.
	bool CollidesWith(const Rectangle* const rect) const;
};

#endif