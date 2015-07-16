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
	HR(gD3DDevice->CreateVertexBuffer(NUM_VERTICES * sizeof(VertexPosCol),
		D3DUSAGE_WRITEONLY, 0,
		D3DPOOL_MANAGED, &mVB, 0));

	VertexPosCol* v = 0;
	HR(mVB->Lock(0, 0, (void**)&v, 0));

	v[0] = VertexPosCol(-1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(255, 255, 255));
	v[1] = VertexPosCol(-1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB(255, 0, 255));
	v[2] = VertexPosCol(1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB(255, 255, 0));
	v[3] = VertexPosCol(1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 255));
	v[4] = VertexPosCol(-1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255));
	v[5] = VertexPosCol(-1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0));
	v[6] = VertexPosCol(1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 0));
	v[7] = VertexPosCol(1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255));

	HR(mVB->Unlock());
}

void Cube::BuildIndexBuffer()
{
	HR(gD3DDevice->CreateIndexBuffer(NUM_FACES * 3 * sizeof(WORD), D3DUSAGE_WRITEONLY,
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
