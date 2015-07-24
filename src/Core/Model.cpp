#include "Model.h"

Model::Model()
	: mVB(nullptr)
	, mIB(nullptr)
	, mRotation(0.f)
{
	BuildVertexBuffer();
	BuildIndexBuffer();
}

Model::~Model()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}
