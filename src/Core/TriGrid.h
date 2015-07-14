#pragma once

#include "CustomModel.h"

class TriGrid :
	public CustomModel
{
public:
	TriGrid();
	TriGrid(int w, int h, int dx);
	~TriGrid();

protected:
	void BuildVertexBuffer();
	void BuildIndexBuffer();

private:
	float tileW;
	int width, height;
	int numVertices;
	int numFaces;
};

