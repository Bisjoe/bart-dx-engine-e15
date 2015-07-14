#include "ShipRace.h"
#include "ResourceIDs.h"

ShipRace::ShipRace()
{
	triangle = new Triangle();
	cube = new Cube();
	triGrid = new TriGrid(10, 10, 0.5f);
}

ShipRace::~ShipRace()
{
	delete triangle;
	delete cube;
	delete triGrid;
}

void ShipRace::Start()
{

}

void ShipRace::Update()
{

}

void ShipRace::Draw()
{

}

void ShipRace::Stop()
{

}