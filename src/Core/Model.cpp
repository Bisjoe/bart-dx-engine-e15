#include "Model.h"

Model::Model()
	: mVB(nullptr)
	, mIB(nullptr)
	, mRotation(0.f)
	, mPosition(0.f, 0.f, 0.f)
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
	world = rot * trans;

	mFx->SetMatrix(mhWVP, &(world * gEngine->GetCamera()->GetView() * gEngine->GetCamera()->GetProj()));
}
