#pragma once
#include "CustomModel.h"

class Cube :
	public CustomModel
{
public:
	Cube();
	~Cube();

	static const int NUM_VERTICES = 8;
	static const int NUM_FACES = 12;

protected:
	int GetNumFaces() { return NUM_FACES; }
	int GetNumVertices(){ return NUM_VERTICES; }

	void BuildVertexBuffer();
	void BuildIndexBuffer();
};

