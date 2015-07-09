#pragma once
#include "CustomModel.h"
class Triangle :
	public CustomModel
{
public:
	Triangle();
	~Triangle();

protected:
	void BuildVertexBuffer();

};

