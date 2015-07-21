#pragma once

#include "CustomModel.h"

class TriGrid :
	public CustomModel
{
public:
	TriGrid(int w, int h, int dx);
	~TriGrid();

	void Update();

protected:
	int GetNumFaces() { return (width + 1) * (height + 1) * 2; }
	int GetNumVertices(){ return (width + 1) * (height + 1); }

	void BuildVertexBuffer();
	void BuildIndexBuffer();

private:
	TriGrid();

	float GetHeight(float x, float z)
	{
		return (((rand() % 160) + 1) / 1000.0f * (z*sinf(((rand() % 20) + 1) / 1000.0f * x) + x * cosf(((rand() % 20) + 1) / 1000.0f * z)));
	}

	float tileW;
	int width, height;

	D3DXHANDLE mhTime;
	D3DXHANDLE mhEyePos;
	D3DXHANDLE mhFogColor;

};

