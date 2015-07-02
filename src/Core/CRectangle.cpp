#include "CRectangle.h"

//Default Constructor, everything's a zero.
CRectangle::CRectangle()
	:Collider(nullptr, Type::RECTANGLE, 0, 0)
	, width(0)
	, height(0)
{
}

//Default Constructor, everything's a zero.
CRectangle::CRectangle(Component* comp, Type type, float x, float y)
	:Collider(comp, Type::RECTANGLE, x, y)
	, width(5)
	, height(5)
{
}

//Default deconstructor
CRectangle::~CRectangle()
{
}


//CRectangle's Constructor:
//We do not accept any negative width or height over here. You shall obey!
//Has there been a consensus on wheter the height would mean the CRectangle would go up from X/Y or down from it?
//I'm pretty sure it's assumed that it is the top-left corner based upon the very next constructor...
//You could pretty much do just about anything, heck the x/y could be from the CRectangle's mid point... ARGH

//Assume everything in the code is based upon this very system. We build CRectangles downward, from X/Y, which is the top left point.
/////////////////////////////////////////////////
//(X,Y)//////////////////////////////////////////
////!----------------------!/////////////////////
////|//////////////////////|/////////////////////
////|//////////////////////|Height///////////////
////|//////////////////////|/////////////////////
////!----------------------!(X+Width, Y-Height)//
////////////Width////////////////////////////////
CRectangle::CRectangle(float x, float y, float width, float height)
	: Collider(nullptr, Type::RECTANGLE, x, y),
	width(abs(width)),
	height(abs(height))
{
	return;
}


//Simple check to determine if a point is within coords
// Please keep in mind if a point was ON one of the CRectangle's border, it will be considered as WITHIN the CRectangle.
bool CRectangle::Contains(const float x, const float y)
{
	//return (x >= this->GetX() && x <= (this->GetX() + this->GetWidth()) && y >= this->GetY() && y <= (this->GetY() + this->GetHeight()));
	return false;
}


//Modify the CRectangle's width and height
void CRectangle::SetSize(float w, float h)
{
	this->width = w;
	this->height = h;
	return;
}


//I believe this is the easiest collision algorithm to figure out by oneself. 
// Every axis-aligned CRectangle-CRectangle collisions must respect these  statements to actually be colliding.
// Rect1.TopLeftX < B.BottomRight2
// Rect1.BottomRightX > B.TopLeftX1 
// Rect1.TopLeftY < B.BottomRightY
// Rect1.BottomRightY > B.TopLeftY
bool CRectangle::CollidesWith(CRectangle* const rect)
{
	bool areColliding = false;
	if (this->GetX() < (rect->GetX() + rect->GetWidth()) && (this->GetX() + this->GetWidth()) > rect->GetX() &&
		this->GetY() < (rect->GetY() + rect->GetHeight()) && (this->GetY() + this->GetHeight())> rect->GetY())
	{
		areColliding = true;
	}
	return areColliding;
}

bool CRectangle::CheckCollision(Collider* const collider)
{
	bool isColliding = false;

	if (collider->GetType() == Type::CIRCLE)
	{
		isColliding = static_cast<CCircle*>(collider)->CheckCollision(this);

	}
	else if (collider->GetType() == Type::RECTANGLE)
	{
		isColliding = CollidesWith(static_cast<CRectangle*>(collider));
	}

	return isColliding;
}
