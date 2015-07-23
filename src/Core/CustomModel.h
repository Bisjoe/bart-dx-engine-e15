#pragma once

#include "Engine.h"
#include "Vertex.h"
#include "Component.h"

class CustomModel
	: public Component
{
public:
	CustomModel();
	virtual ~CustomModel();

	void OnLostDevice();
	void OnResetDevice();
	virtual void Update();
	virtual void Draw();

	void SetRotation(float rot) { mRotation = rot; }
	float GetRotation() { return mRotation; }

	void SetPosition(float x, float y, float z) { mPosition.x = x; mPosition.y = y; mPosition.z = z; }
	D3DXVECTOR3 GetPosition() { return mPosition; }

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

	float mRotation;
	D3DXVECTOR3 mPosition;
};

