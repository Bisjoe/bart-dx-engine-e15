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

	HR(mFx->SetTechnique(mhTech));
}

PrimitiveModel::PrimitiveModel(PrimitiveModel_Type type)
	: mesh(nullptr)
{
	switch (type)
	{
	case PrimitiveModel::CYLINDER:
		HR(D3DXCreateCylinder(gD3DDevice, 1.f, 1.f, 6.f, 20.f, 20.f, &mesh, 0));
		break;
	case PrimitiveModel::CUBE:
		HR(D3DXCreateBox(gD3DDevice, 1.f, 1.f, 1.f, &mesh, 0));
		break;
	case PrimitiveModel::SPHERE:
		HR(D3DXCreateSphere(gD3DDevice, 1.f, 10.f, 10.f, &mesh, 0));
		break;
	case PrimitiveModel::TEAPOT:
		HR(D3DXCreateTeapot(gD3DDevice, &mesh, 0));
		break;
	case PrimitiveModel::CONE:
		HR(D3DXCreateCylinder(gD3DDevice, 0, 1.f, 6.f, 20.f, 20.f, &mesh, 0));
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

	HR(mFx->SetTechnique(mhTech));
}

PrimitiveModel::~PrimitiveModel()
{
	ReleaseCOM(mesh);
	ReleaseCOM(mFx);
	ReleaseCOM(mErrors);
}

void PrimitiveModel::OnLostDevice()
{
	HR(mFx->OnLostDevice());
}

void PrimitiveModel::OnResetDevice()
{
	HR(mFx->OnLostDevice());
}

void PrimitiveModel::BuildVertexBuffer()
{
	if (mesh != nullptr)
	{
		HR(mesh->GetVertexBuffer(&mVB));
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
		HR(mesh->GetIndexBuffer(&mIB));
	}
}

void PrimitiveModel::Draw()
{
	Model::Draw();

	if (mesh == nullptr)
		return;

	HR(gD3DDevice->SetStreamSource(0, mVB, 0, sizeof(VertexPosCol::decl)));
	HR(gD3DDevice->SetIndices(mIB));
	
	UINT numPasses = 0;
	HR(mFx->Begin(&numPasses, 0));
	
	for (UINT i = 0; i < numPasses; i++)
	{
		HR(mFx->BeginPass(i));
		HR(mesh->DrawSubset(0));
		HR(mFx->EndPass());
	}
	HR(mFx->End());
}
