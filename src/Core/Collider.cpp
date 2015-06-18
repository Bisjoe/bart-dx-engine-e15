#include "Collider.h"

std::vector<Collider*> Collider::components;
std::vector<Collider*> Collider::toAdd;
std::vector<Collider*> Collider::toDelete;
std::vector<Collider*> Collider::removed;

Collider::Collider()
{
}

Collider::Collider(bool isActive)
	: isActive(isActive)
	, TAG(TAG)
{

}


Collider::~Collider()
{
}

void Collider::Start()
{

}
void Collider::Update()
{

} 
void Collider::Stop()
{

} 
void Collider::Kill()
{

} 
