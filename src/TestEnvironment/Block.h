#pragma once

#include "ResourceIDs.h"
#include "Sprite.h"
#include "CRectangle.h"

class Block :
	public Sprite
{
public:
	Block();
	~Block();

	//Called when a ball hits the block
	void Shout();

	//Rectangle collider
	CRectangle* collider;
};

