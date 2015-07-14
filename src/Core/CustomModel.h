#pragma once

#include "Engine.h"
#include "Vertex.h"
#include "Component.h"

class CustomModel: public Component
{
public:
	CustomModel();
	virtual ~CustomModel();

	void OnLostDevice();
	void OnResetDevice();
	void Update();
	void Draw();

protected:
	virtual int GetNumFaces() = 0;
	virtual int GetNumVertices() = 0;

	virtual void BuildVertexBuffer() { }
	virtual void BuildIndexBuffer() { }
	
	IDirect3DVertexBuffer9* mVB;
	IDirect3DIndexBuffer9* mIB;

	ID3DXEffect* mFx;
	ID3DXBuffer* mErrors;

	D3DXHANDLE mhTech;
	D3DXHANDLE mhWVP;

	float currentRotation;
};

