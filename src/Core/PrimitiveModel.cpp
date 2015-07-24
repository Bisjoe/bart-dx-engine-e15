#include "PrimitiveModel.h"

PrimitiveModel::PrimitiveModel()
	: mesh(nullptr)
{
	HR(D3DXCreateEffectFromFile(gD3DDevice, "Transform.fx", 0, 0, D3DXSHADER_DEBUG, 0, &mFx, &mErrors));
	if (mErrors)
	{
		MessageBox(0, (char*)mErrors->GetBufferPointer(), 0, 0);
	}

	mhTech = mFx->GetTechniqueByName("TransformTech");
	mhWVP = mFx->GetParameterByName(0, "gWVP");

	mFx->SetTechnique(mhTech);
}

PrimitiveModel::PrimitiveModel(PrimitiveModel_Type type)
	: mesh(nullptr)
{
	switch (type)
	{
	case PrimitiveModel::CYLINDER:
		D3DXCreateCylinder(gD3DDevice, 1.f, 1.f, 6.0f, 20.0f, 20.0f, &mesh, 0);
		break;
	case PrimitiveModel::CUBE:

		break;
	case PrimitiveModel::SPHERE:

		break;
	case PrimitiveModel::TEAPOT:

		break;
	default:
		break;
	}

	HR(D3DXCreateEffectFromFile(gD3DDevice, "Transform.fx", 0, 0, D3DXSHADER_DEBUG, 0, &mFx, &mErrors));
	if (mErrors)
	{
		MessageBox(0, (char*)mErrors->GetBufferPointer(), 0, 0);
	}

	mhTech = mFx->GetTechniqueByName("TransformTech");
	mhWVP = mFx->GetParameterByName(0, "gWVP");

	mFx->SetTechnique(mhTech);
}

PrimitiveModel::~PrimitiveModel()
{
	ReleaseCOM(mesh);
	ReleaseCOM(mFx);
	ReleaseCOM(mErrors);
}

void PrimitiveModel::OnLostDevice()
{
	mFx->OnLostDevice();
}

void PrimitiveModel::OnResetDevice()
{
	mFx->OnLostDevice();
}

void PrimitiveModel::BuildVertexBuffer()
{
	if (mesh != nullptr)
	{
		mesh->GetVertexBuffer(&mVB);
	}
	else
	{
		std::cout << "PrimitiveModel: variable mesh is null, please affect one in child constructor using D3DXCreate... (Cylinder or Cube or Sphere)" << std::endl;
	}
}

void PrimitiveModel::BuildIndexBuffer()
{
	if (mesh != nullptr)
	{
		mesh->GetIndexBuffer(&mIB);
	}
}

void PrimitiveModel::Draw()
{
	Model::Draw();

	if (mesh == nullptr)
		return;

	gD3DDevice->SetStreamSource(0, mVB, 0, sizeof(VertexPosCol::decl));
	gD3DDevice->SetIndices(mIB);
	
	UINT numPasses = 0;
	mFx->Begin(&numPasses, 0);
	
	for (UINT i = 0; i < numPasses; i++)
	{
		mFx->BeginPass(i);
		mesh->DrawSubset(0);
		mFx->EndPass();
	}
	mFx->End();
}
