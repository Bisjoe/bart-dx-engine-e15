#pragma once

#include "Common.h"
#include "Engine.h"
#include "Component.h"

class Model :
	public Component
{
public:
	Model();
	virtual ~Model();

	virtual void Update(){}
	virtual void Draw();

	virtual void BuildVertexBuffer(){}
	virtual void BuildIndexBuffer(){}

	D3DXMATRIX GetWorldMatrix() { return world; }

	void SetRotationY(float rot) { mRotationY = rot; }
	void SetRotationX(float rot) { mRotationX = rot; }
	void SetRotationZ(float rot) { mRotationZ = rot; }
	float GetRotationY() { return mRotationY; }
	float GetRotationX() { return mRotationX; }
	float GetRotationZ() { return mRotationZ; }

	void SetPosition(float x, float y, float z) { mPosition.x = x; mPosition.y = y; mPosition.z = z; }
	D3DXVECTOR3 GetPosition() { return mPosition; }

	void SetScale(float x, float y, float z) { mScale.x = x; mScale.y = y; mScale.z = z; }

protected:
	IDirect3DVertexBuffer9* mVB;
	IDirect3DIndexBuffer9* mIB;

	ID3DXEffect* mFx;
	ID3DXBuffer* mErrors;

	D3DXHANDLE mhTech;
	D3DXHANDLE mhWVP;

private:
	float mRotationY;
	float mRotationX;
	float mRotationZ;
	D3DXVECTOR3 mPosition;
	D3DXVECTOR3 mScale;

	D3DXMATRIX world;
	D3DXMATRIX trans;
	D3DXMATRIX rotX;
	D3DXMATRIX rotY;
	D3DXMATRIX rotZ;
	D3DXMATRIX scale;


};

