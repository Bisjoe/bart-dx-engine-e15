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
		return (0.3f * (z*sinf(0.1f * x) + x * cosf(0.1f * z)));
	}

	float tileW;
	int width, height;

	D3DXHANDLE mhTime;
	D3DXHANDLE mhEyePos;
	D3DXHANDLE mhFogColor;

};

