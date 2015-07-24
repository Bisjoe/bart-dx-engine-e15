#pragma once

#include "Common.h"
#include "Component.h"

class Model :
	public Component
{
public:
	Model();
	virtual ~Model();

	virtual void Update(){}
	virtual void Draw(){}

	virtual void BuildVertexBuffer(){}
	virtual void BuildIndexBuffer(){}

	void SetRotation(float rot) { mRotation = rot; }
	float GetRotation() { return mRotation; }

	void SetPosition(float x, float y, float z) { mPosition.x = x; mPosition.y = y; mPosition.z = z; }
	D3DXVECTOR3 GetPosition() { return mPosition; }

protected:
	IDirect3DVertexBuffer9* mVB;
	IDirect3DIndexBuffer9* mIB;

	ID3DXEffect* mFx;
	ID3DXBuffer* mErrors;

	D3DXHANDLE mhTech;
	D3DXHANDLE mhWVP;

private:
	float mRotation;
	D3DXVECTOR3 mPosition;

};

