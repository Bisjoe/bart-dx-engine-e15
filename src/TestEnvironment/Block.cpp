#include "Ball.h"
#include "Block.h"


Block::Block()
	: Sprite(Texture::Block)
{
	this->SetID(Components::Block);
	//Rectangle Collider at (5, 5) with a width/height of (10/10)
	collider = new CRectangle(this, 5, 5, 10, 10);

	D3DXVECTOR3 center(this->GetTextureInfos()->infos.Width / 2, this->GetTextureInfos()->infos.Height / 2, 0.0f);
	this->SetPivot(center);
	this->SetRotationDeg(0,0,0);
}


Block::~Block()
{
}

void Block::Shout()
{
	std::cout << "THE BALL IS TOUCHING ME." << std::endl;
}