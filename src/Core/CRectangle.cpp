#include "CRectangle.h"

//Default Constructor, everything's a zero.
CRectangle::CRectangle()
	:Collider(nullptr, Type::RECTANGLE, 0, 0)
	, width(0)
	, height(0)
{
}

//Default deconstructor
CRectangle::~CRectangle()
{
}


//CRectangle's Constructor:
//We do not accept any negative width or height over here. You shall obey!
//Has there been a consensus on wheter the height would mean the Rectangle would go up from X/Y or down from it?
//I'm pretty sure it's assumed that it is the top-left corner based upon the very next constructor...
//You could pretty much do just about anything, heck the x/y could be from the Rectangle's mid point... ARGH

//Assume everything in the code is based upon this very system. We build Rectangles downward, from X/Y, which is the top left point.
/////////////////////////////////////////////////
//(X,Y)//////////////////////////////////////////
////!----------------------!/////////////////////
////|//////////////////////|/////////////////////
////|//////////////////////|Height///////////////
////|//////////////////////|/////////////////////
////!----------------------!(X+Width, Y-Height)//
////////////Width////////////////////////////////
CRectangle::CRectangle(Component* caller, float x, float y, float width, float height)
	: Collider(caller, Type::RECTANGLE, x, y)
	,width(abs(width))
	,height(abs(height))
{
}


//Simple check to determine if a point is within coords
// Please keep in mind if a point was ON one of the Rectangle's border, it will be considered as WITHIN the Rectangle.
bool CRectangle::Contains(const float x, const float y)
{
	return (x >= this->GetPosition().x && x <= (this->GetPosition().x + this->GetWidth()) && y >= this->GetPosition().y && y <= (this->GetPosition().y + this->GetHeight()));
}


//Modify the Rectangle's width and height
void CRectangle::SetSize(float w, float h)
{
	this->width = w;
	this->height = h;
}


//I believe this is the easiest collision algorithm to figure out by oneself. 
// Every axis-aligned Rectangle-Rectangle collisions must respect these statements to actually be colliding.
// Rect1.TopLeftX < B.BottomRight2
// Rect1.BottomRightX > B.TopLeftX1 
// Rect1.TopLeftY < B.BottomRightY
// Rect1.BottomRightY > B.TopLeftY
bool CRectangle::CollidesWith(CRectangle* const rect)
{
	bool areColliding = false;
	if (this->GetPosition().x < (rect->GetPosition().x + rect->GetWidth()) && (this->GetPosition().x + this->GetWidth()) > rect->GetPosition().x &&
		this->GetPosition().y < (rect->GetPosition().y + rect->GetHeight()) && (this->GetPosition().y + this->GetHeight())> rect->GetPosition().y)
	{
		areColliding = true;
	}
	return areColliding;
}

//Based upon the tested collider, we'll look for a rectangle-circle collision or a rectangle-rectangle collision.
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
