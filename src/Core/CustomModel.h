#pragma once

#include "Engine.h"
#include "Vertex.h"
#include "Model.h"

class CustomModel: public Model
{
public:
	CustomModel();
	virtual ~CustomModel();

	void OnLostDevice();
	void OnResetDevice();
	void Draw();

protected:
	virtual int GetNumFaces() = 0;
	virtual int GetNumVertices() = 0;

	virtual void BuildVertexBuffer() { }
	virtual void BuildIndexBuffer() { }
};

