#include "Ball.h"
#include "Block.h"


Ball::Ball()
	: Sprite(Texture::Ball)
{
	//Circle Collider at (0, 0) with a radius of 8.0;
	this->SetID(Components::Ball);
	D3DXVECTOR3 center(this->GetTextureInfos()->infos.Width / 2, this->GetTextureInfos()->infos.Height / 2, 0.0f);
	collider = new CCircle(this, center.x, center.y, 8.f);
	this->SetPivot(center);
	this->SetRotationDeg(0, 0, 0);
}


Ball::~Ball()
{
}

void Ball::Update()
{
	//Press C to check if there is a collision
	if (gDInput->keyPressed(DIK_C))
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

	//Move the ball with the four directional arrows
	float speed = 500 * gTimer->GetDeltaTime();
	if (gDInput->keyDown(DIK_UP))
	{
		this->SetPosition(this->GetPosition().x, this->GetPosition().y + speed);
		this->collider->SetPosition(this->collider->GetPosition().x, this->collider->GetPosition().y + speed);
	}
	if (gDInput->keyDown(DIK_DOWN))
	{
		this->SetPosition(this->GetPosition().x, this->GetPosition().y - speed);
		this->collider->SetPosition(this->collider->GetPosition().x, this->collider->GetPosition().y - speed);
	}
	if (gDInput->keyDown(DIK_LEFT))
	{
		this->SetPosition(this->GetPosition().x - speed, this->GetPosition().y);
		this->collider->SetPosition(this->collider->GetPosition().x - speed, this->collider->GetPosition().y);
	}
	if (gDInput->keyDown(DIK_RIGHT))
	{
		this->SetPosition(this->GetPosition().x + speed, this->GetPosition().y);
		this->collider->SetPosition(this->collider->GetPosition().x + speed, this->collider->GetPosition().y);
	}

	//Press A for the circle's position
	if (gDInput->keyPressed(DIK_A))
	{
		std::cout << "Circle X:" << collider->GetPosition().x << std::endl;
		std::cout << "Circle Y:" << collider->GetPosition().y << std::endl;
		std::cout << "Circle Radius:" << collider->GetRadius() << std::endl;
	}
}