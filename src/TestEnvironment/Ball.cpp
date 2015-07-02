#include "Ball.h"
#include "Block.h"


Ball::Ball()
	: Sprite(Texture::Ball)
{
	//Circle Collider at (0, 0) with a radius of 8.0;
	this->SetID(Components::Ball);
	collider = new CCircle(this, 0, 0, 8.f);

	D3DXVECTOR3 center(this->GetTextureInfos()->infos.Width / 2, this->GetTextureInfos()->infos.Height / 2, 0.0f);
	this->SetPivot(center);
	this->SetRotationDeg(0, 0, 0);
}


Ball::~Ball()
{
}

void Ball::Update()
{
	//Go through each collider collided with though the LookForCollision Function
	for each (Collider* col in collider->LookForCollisions())
	{
		//If one of the collider is a block
		if (col->GetGameObject()->GetID() == Components::Block)
		{
			//Consider that collider's component a block and make him shout
			static_cast<Block*>(col->GetGameObject())->Shout();
		}
	}
}