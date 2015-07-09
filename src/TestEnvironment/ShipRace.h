#pragma once

#include "Component.h"
#include "Triangle.h"

class ShipRace :
	public Component
{
public:
	ShipRace();
	~ShipRace();

	void Start();
	void Update();
	void Draw();
	void Stop();

private:
	Triangle* triangle;
};

