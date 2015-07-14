#pragma once
#include "CustomModel.h"

class Triangle :
	public CustomModel
{
public:
	Triangle();
	~Triangle();

	static const int NUM_VERTICES = 3;
	static const int NUM_FACES = 1;

protected:
	int GetNumFaces() { return NUM_FACES; }
	int GetNumVertices(){ return NUM_VERTICES; }

	void BuildVertexBuffer();

};

