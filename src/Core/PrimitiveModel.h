#pragma once

#include "Model.h"

class PrimitiveModel 
	: public Model
{
public:
	enum PrimitiveModel_Type { CYLINDER, CUBE, SPHERE, TEAPOT };

	PrimitiveModel();
	PrimitiveModel(PrimitiveModel_Type type);
	virtual ~PrimitiveModel();
	virtual void Update(){}

	void OnLostDevice();
	void OnResetDevice();
	void Draw();

protected:
	virtual void BuildVertexBuffer();
	virtual void BuildIndexBuffer();

protected:
	ID3DXMesh* mesh;

};

