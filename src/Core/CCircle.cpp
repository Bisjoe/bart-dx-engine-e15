#include "CCircle.h"
#include "CRectangle.h"

//Default Constructor, everything's a zero.
CCircle::CCircle()
	: Collider(nullptr, Type::CIRCLE, 0, 0)
	, radius(0)
{
}

//Default deconstructor
CCircle::~CCircle()
{
}

//Remember kids, there's no such thing as a negative radius in heaven, at least not for an ordinary Circle.
CCircle::CCircle(Component* caller, float x, float y, float radius)
	: Collider(caller, Type::CIRCLE, x, y)
	, radius(abs(radius))
{
}

// If a point is contained within a Circle
// Points ON the Circle's border are considered to be part of the CCircle
bool CCircle::Contains(const float x, const float y)
{
	return (pow(x - this->GetPosition().x, 2) + pow(y - this->GetPosition().y, 2)) <= pow(this->radius, 2);
}


//If a Circle collides with another specified Circle, we'll return it.
bool CCircle::CollidesWith(CCircle* const circ)
{
	
	return (pow(circ->GetPosition().x - this->GetPosition().x, 2) + pow(circ->GetPosition().y - this->GetPosition().y, 2)) <= pow(this->GetRadius() + circ->GetRadius(), 2);
}


//WARNING: THIS FUNCTION IS ONLY LEGAL WHEN USING AXIS ALIGNED RECTANGLE, which are the only kind of rectangle we're using... so yeah.
//This formula wouldn't work in any other circumstances.
bool CCircle::CollidesWith(CRectangle* const rect)
{
	//We're using a vector2D to store the X and Y distance positions of the circle
	D3DXVECTOR2 circleDistance;
	//We're storing the rectangle's center coordinate, minus its actual position, so let's consider it it's relative center?
	//Alternatively you might consider it the super vector of HalfRectangleWidth and HalfRectangleHeight... weee!!!
	D3DXVECTOR2 rectCenter;
	rectCenter.x = rect->GetWidth() / 2;
	rectCenter.y = rect->GetHeight() / 2;

	//Self-Explaining boolean
	bool areColliding = false;

	//This part is really nifty, by getting the absolute value of the distance of the circle's center and the rectangle's center...
	//We only have to do math once instead of four time. That's the magic of axis aligned rectangles
	circleDistance.x = fabs(this->position.x - (rect->GetPosition().x + rectCenter.x));
	circleDistance.y = fabs(this->position.y - (rect->GetPosition().y + rectCenter.y));

	//We're storing the squared distance of the circle's from the rectangle, minus half the rectangle's size.
	//It's gonna be really useful when calculating wheter or not the corner is colliding with the circle. Trust me.
	float cornerDistance_sq = pow((circleDistance.x - rectCenter.x), 2) + pow((circleDistance.y - rectCenter.y), 2);

	//Cases where the circle is far enough from the rectangle, no collisions.
	if ((circleDistance.x > (rectCenter.x + this->radius)) || (circleDistance.y > (rectCenter.y + this->radius)))
	{
		areColliding = false;
	}
	//Cases where the circle is close enough to the rectangle in any direction, collision.
	else if ((circleDistance.x <= (rectCenter.x)) && (circleDistance.y <= (rectCenter.y)))
	{
		areColliding = true;
	}
	//Rare cases when the corner of the rectangle is colliding with the circle
	else if (cornerDistance_sq <= pow((this->radius), 2))
	{
		//Requires more testing, I'd rather not use it for now.
		areColliding = true;
	}

	return areColliding;
}

//Based upon the tested collider, we'll look for a circle-circle collision or a circle-rectangle collision.
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