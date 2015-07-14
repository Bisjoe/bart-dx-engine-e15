#include "Cube.h"

Cube::Cube()
{
	BuildVertexBuffer();
	BuildIndexBuffer();
}

Cube::~Cube()
{
}

void Cube::BuildVertexBuffer()
{
	HR(gD3DDevice->CreateVertexBuffer(8 * sizeof(VertexPos),
		D3DUSAGE_WRITEONLY, 0,
		D3DPOOL_MANAGED, &mVB, 0));

	VertexPos* v = 0;
	HR(mVB->Lock(0, 0, (void**)&v, 0));

	v[0] = VertexPos(-1.0f, -1.0f, -1.0f);
	v[1] = VertexPos(-1.0f, 1.0f, -1.0f);
	v[2] = VertexPos(1.0f, 1.0f, -1.0f);
	v[3] = VertexPos(1.0f, -1.0f, -1.0f);
	v[4] = VertexPos(-1.0f, -1.0f, 1.0f);
	v[5] = VertexPos(-1.0f, 1.0f, 1.0f);
	v[6] = VertexPos(1.0f, 1.0f, 1.0f);
	v[7] = VertexPos(1.0f, -1.0f, 1.0f);

	HR(mVB->Unlock());
}

void Cube::BuildIndexBuffer()
{
	HR(gD3DDevice->CreateIndexBuffer(36 * sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &mIB, 0));

	WORD* k = 0;
	HR(mIB->Lock(0, 0, (void**)&k, 0));

	// Front face
	k[0] = 0, k[1] = 1, k[2] = 2;
	k[3] = 0, k[4] = 2, k[5] = 3;

	// Back face
	k[6] = 4; k[7] = 6; k[8] = 5;
	k[9] = 4; k[10] = 7; k[11] = 6;

	// Left face
	k[12] = 4; k[13] = 5; k[14] = 1;
	k[15] = 4; k[16] = 1; k[17] = 0;

	// Right face
	k[18] = 3; k[19] = 2; k[20] = 6;
	k[21] = 3; k[22] = 6; k[23] = 7;

	// Top face
	k[24] = 1; k[25] = 5; k[26] = 6;
	k[27] = 1; k[28] = 6; k[29] = 2;

	// Bottom face
	k[30] = 4; k[31] = 0; k[32] = 3;
	k[33] = 4; k[34] = 3; k[35] = 7;

	HR(mIB->Unlock());
}
