#include "CustomModel.h"

CustomModel::CustomModel()
{

}

CustomModel::~CustomModel()
{

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
	HR(gD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 3));
}