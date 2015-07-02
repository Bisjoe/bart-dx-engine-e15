#pragma once

#include "ResourceIDs.h"
#include "Sprite.h"
#include "CCircle.h"

class Ball :
	public Sprite
{
public:
	Ball();
	~Ball();

	void Update();

	//Circle Collider
	CCircle* collider;

private:
	D3DXVECTOR3 pivot;
};

