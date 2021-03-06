#include "CustomModel.h"

CustomModel::CustomModel()
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

CustomModel::~CustomModel()
{
	ReleaseCOM(mFx);
	ReleaseCOM(mErrors);
}

void CustomModel::OnLostDevice()
{
	mFx->OnLostDevice();
}

void CustomModel::OnResetDevice()
{
	mFx->OnResetDevice();
}

void CustomModel::Draw()
{
	Model::Draw();

	HR(gD3DDevice->SetStreamSource(0, mVB, 0, sizeof(VertexPosCol)));
	HR(gD3DDevice->SetVertexDeclaration(VertexPosCol::decl));
	if (mIB != nullptr)
	{
		HR(gD3DDevice->SetIndices(mIB));
	}
	
	UINT numPasses = 0;
	mFx->Begin(&numPasses, 0);
	
	for (UINT i = 0; i < numPasses; i++)
	{
		mFx->BeginPass(i);
		if (mIB == nullptr)
		{
			HR(gD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0,
				GetNumVertices()));
		}
		else
		{
			HR(gD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0,
				0, GetNumVertices(), 0, GetNumFaces()));
		}
		mFx->EndPass();
	}
	mFx->End();
}