#include "CCircle.h"
#include "CRectangle.h"

//Default Constructor, everything's a zero.
CCircle::CCircle()
	: Collider(nullptr, Type::CIRCLE, 0, 0)
	, radius(0)
{
	return;
}

//Default deconstructor
CCircle::~CCircle()
{
	return;
}

//Remember kids, there's no such thing as a negative radius in heaven, at least not for an ordinary CCircle.
CCircle::CCircle(Component* caller, float x, float y, float radius)
	: Collider(caller, Type::CIRCLE, x, y)
	, radius(abs(radius))
{
	return;
}

// If a point is contained within a CCircle
// Points ON the CCircle's border are considered to be part of the CCircle
bool CCircle::Contains(const float x, const float y)
{
	return (pow(x - this->x, 2) + pow(y - this->y, 2)) <= pow(this->radius, 2);
}


//If a CCircle collides with another specified CCircle, we'll return it.
bool CCircle::CollidesWith(CCircle* const circ)
{

	return true; // (pow(circ->GetX() - this->GetX(), 2) + pow(circ->GetY() - this->GetY(), 2)) <= pow(this->GetRadius() + circ->GetRadius(), 2);
}


//WARNING: THIS FUNCTION IS ONLY LEGAL WHEN USING AXIS ALIGNED RECTANGLE, which are the only kind of rectangle we're using... so yeah.
//This formula wouldn't work in any other circumstances.
bool CCircle::CollidesWith(CRectangle* const rect)
{
	//We're using a vector2D to store the X and Y distance positions of the CCircle
	Vector2D CCircleDistance;
	//We're storing the rectangle's center coordinate, minus its actual position, so let's consider it it's relative center?
	//Alternatively you might consider it the super vector of HalfRectangleWidth and HalfRectangleHeight... weee!!!
	Vector2D rectCenter;
	rectCenter.x = rect->GetWidth() / 2;
	rectCenter.y = rect->GetHeight() / 2;

	//Self-Explaining boolean
	bool areColliding = false;

	//This part is really nifty, by getting the absolute value of the distance of the CCircle's center and the rectangle's center...
	//We only have to do math once instead of four time. That's the magic of axis aligned rectangles
	CCircleDistance.x = abs(this->x - ((rect->GetX() + rect->GetWidth()) / 2));
	CCircleDistance.y = abs(this->y - ((rect->GetY() + rect->GetHeight()) / 2));

	//We're storing the squared distance of the CCircle's from the rectangle, minus half the rectangle's size.
	//It's gonna be really useful when calculating wheter or not the corner is colliding with the CCircle. Trust me.
	float cornerDistance_sq = pow((CCircleDistance.x - rectCenter.x), 2) + pow((CCircleDistance.y - rectCenter.y), 2);

	//Cases where the CCircle is far enough from the rectangle, no collisions.
	if ((CCircleDistance.x > (rectCenter.x + this->radius)) || (CCircleDistance.y > (rectCenter.y + this->radius)))
	{
		areColliding = false;
	}
	//Cases where the CCircle is close enough to the rectangle in any direction, collision.
	else if ((CCircleDistance.x <= (rectCenter.x)) || (CCircleDistance.y <= (rectCenter.y)))
	{
		areColliding = true;
	}
	//Rare cases when the corner of the rectangle is colliding with the CCircle
	else if (cornerDistance_sq <= pow((this->radius), 2))
	{
		areColliding = true;
	}

	return areColliding;

}

bool CCircle::CheckCollision(Collider* collider)
{
	bool isColliding = false;

	if (collider->GetType() == Type::CIRCLE)
	{
		isColliding = CollidesWith((CCircle*)collider);
	}
	else if (collider->GetType() == Type::RECTANGLE)
	{
		isColliding = CollidesWith((CRectangle*)collider);
	}

	return isColliding;
}