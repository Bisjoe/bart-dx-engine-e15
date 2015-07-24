#include "Model.h"

Model::Model()
	: mVB(nullptr)
	, mIB(nullptr)
	, mRotation(0.f)
	, mPosition(0.f, 0.f, 0.f)
	, mScale(1.f, 1.f, 1.f)
{
	BuildVertexBuffer();
	BuildIndexBuffer();
}

Model::~Model()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}

void Model::Draw()
{
	D3DXMatrixIdentity(&world);
	D3DXMatrixRotationY(&rot, mRotation);
	D3DXMatrixTranslation(&trans, mPosition.x, mPosition.y, mPosition.z);
	D3DXMatrixScaling(&scale, mScale.x, mScale.y, mScale.z);
	world = rot * trans * scale;

	mFx->SetMatrix(mhWVP, &(world * gEngine->GetCamera()->GetView() * gEngine->GetCamera()->GetProj()));
}
