#pragma once
#include "CustomModel.h"
class Cube :
	public CustomModel
{
public:
	Cube();
	~Cube();

protected:
	void BuildVertexBuffer();
	void BuildIndexBuffer();
};

