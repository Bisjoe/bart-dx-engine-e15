#include "Ship.h"

Ship::Ship()
	: PrimitiveModel(PrimitiveModel_Type::CYLINDER)
{
	
}

Ship::~Ship()
{
}

void Ship::Update()
{
	SetRotation(GetRotation() + 10.f * gTimer->GetDeltaTime());	
}
