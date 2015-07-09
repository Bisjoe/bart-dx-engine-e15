#include "Vertex.h"

IDirect3DVertexDeclaration9* VertexPos::decl = 0;
IDirect3DVertexDeclaration9* VertexPosCol::decl = 0;

void InitAllVertexDeclarations()
{
	// VertexPos
	D3DVERTEXELEMENT9 vertexPosElements[] = 
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		D3DDECL_END()
	};
	HR(gD3DDevice->CreateVertexDeclaration(vertexPosElements, &VertexPos::decl));

	// VertexPosCol
	int totalSize = 0;
	std::vector<D3DVERTEXELEMENT9> vpe;
	vpe.push_back( { 0, totalSize += sizeof(D3DXVECTOR3), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 } );
	vpe.push_back( { 0, totalSize += sizeof(D3DCOLOR), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 } );
	vpe.push_back( D3DDECL_END() );
	HR(gD3DDevice->CreateVertexDeclaration(&vpe[0], &VertexPosCol::decl));
}

void DestroyAllVertexDeclarations()
{
	ReleaseCOM(VertexPos::decl);
	ReleaseCOM(VertexPosCol::decl);
}