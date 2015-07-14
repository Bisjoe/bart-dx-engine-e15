#pragma once

#include "CustomModel.h"

class TriGrid :
	public CustomModel
{
public:
	TriGrid(int w, int h, int dx);
	~TriGrid();

protected:
	int GetNumFaces() { return (width + 1) * (height + 1) * 2; }
	int GetNumVertices(){ return (width + 1) * (height + 1); }

	void BuildVertexBuffer();
	void BuildIndexBuffer();

private:
	TriGrid();

	float tileW;
	int width, height;
};

