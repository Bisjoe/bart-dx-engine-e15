#include "CustomModel.h"

CustomModel::CustomModel()
	: mVB(nullptr)
	, mIB(nullptr)
{

}

CustomModel::~CustomModel()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}

void CustomModel::OnLostDevice()
{

}

void CustomModel::OnResetDevice()
{

}

void CustomModel::Draw()
{
	HR(gD3DDevice->SetStreamSource(0, mVB, 0, sizeof(VertexPos)));
	HR(gD3DDevice->SetVertexDeclaration(VertexPos::decl));

	if (mIB == nullptr)
	{
		HR(gD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 3));
	}
	else
	{
		HR(gD3DDevice->SetIndices(mIB));
		HR(gD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12));
	}
}