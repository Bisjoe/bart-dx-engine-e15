#include "TriGrid.h"

TriGrid::TriGrid()
	: width(100)
	, height(100)
	, tileW(1.0f)
{
	numVertices = (++width) * (++height);
	numFaces = width * height * 2;

	BuildVertexBuffer();
	BuildIndexBuffer();
}

TriGrid::TriGrid(int w, int h, int dx)
	: width(w)
	, height(h)
	, tileW(dx)
{
	numVertices = (++width) * (++height);
	numFaces = width * height * 2;

	BuildVertexBuffer();
	BuildIndexBuffer();
}

TriGrid::~TriGrid()
{

}

void TriGrid::BuildVertexBuffer()
{
	HR(gD3DDevice->CreateVertexBuffer(8 * sizeof(VertexPos),
		D3DUSAGE_WRITEONLY, 0,
		D3DPOOL_MANAGED, &mVB, 0));

	VertexPos* v = 0;
	HR(mVB->Lock(0, 0, (void**)&v, 0));

	float halfWidth = (width - 1) * tileW * 0.5f;
	float halfHeight = (height - 1) * tileW * 0.5f;

	for (DWORD i = 0; i < width; i++)
	{
		float z = halfHeight - i * tileW;
		for (DWORD j = 0; j < height; j++)
		{
			float x = -halfHeight + j * tileW;
			float y = 0;

			v[i * height + j].pos = D3DXVECTOR3(x, y, z);
		}
	}
	
	HR(mVB->Unlock());
}

void TriGrid::BuildIndexBuffer()
{
	HR(gD3DDevice->CreateIndexBuffer(36 * sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &mIB, 0));

	WORD* indices = 0;
	HR(mIB->Lock(0, 0, (void**)&indices, 0));

	int k = 0;
	for (DWORD i = 0; i < width-1; i++)
	{
		for (DWORD j = 0; j < height - 1; j++)
		{
			indices[k] = i * height + j;
			indices[k + 1] = i * height + (j + 1);
			indices[k + 2] = (i + 1) * height + j;
			indices[k + 3] = (i + 1) * height + j;
			indices[k + 4] = i * height + j + 1;
			indices[k + 5] = (i + 1) * height + (j + 1);
			k += 6; // Next quad
		}
	}

	HR(mIB->Unlock());
}
