#pragma once

#include "Utils.h"
#include "Vertex.h"
#include "Component.h"

class CustomModel: public Component
{
public:
	CustomModel();
	virtual ~CustomModel();

	void OnLostDevice();
	void OnResetDevice();
	void Draw();

protected:
	virtual void BuildVertexBuffer() { }
	virtual void BuildIndexBuffer() { }
	
	IDirect3DVertexBuffer9* mVB;
	IDirect3DIndexBuffer9* mIB;

};

