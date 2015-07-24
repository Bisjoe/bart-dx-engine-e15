#pragma once

#include "Component.h"
#include "Triangle.h"
#include "Cube.h"
#include "TriGrid.h"
#include "Ship.h"

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
	Cube* cube;
	TriGrid* triGrid;
};

