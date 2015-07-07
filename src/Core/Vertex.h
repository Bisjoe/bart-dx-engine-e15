#pragma once

#include "Utils.h"

struct VertexPos
{
	VertexPos()
		: pos(0.f, 0.f, 0.f){}
	VertexPos(float x, float y, float z)
		: pos(x, y, z){}
	VertexPos(D3DXVECTOR3& v)
		: pos(v){}
		
	D3DXVECTOR3 pos;

	static IDirect3DVertexDeclaration9* decl;
};

struct VertexPosCol
{
	VertexPosCol() 
		: pos(0.f, 0.f, 0.f), col(0x00000000){}
	VertexPosCol(float x, float y, float z) 
		: pos(x, y, z), col(0x00000000){}
	VertexPosCol(float x, float y, float z, const D3DCOLOR& c) 
		: pos(x, y, z), col(c){}
	VertexPosCol(const D3DXVECTOR3& v, const D3DCOLOR&c) 
		: pos(v), col(c){}

	D3DXVECTOR3 pos;
	D3DCOLOR col;

	static IDirect3DVertexDeclaration9* decl;
};

void InitAllVertexDeclarations();
void DestroyAllVertexDeclarations();