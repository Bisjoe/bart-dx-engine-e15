#include "Triangle.h"

Triangle::Triangle()
{
	BuildVertexBuffer();
}

Triangle::~Triangle()
{
	ReleaseCOM(mVB);
}

void Triangle::BuildVertexBuffer()
{
	// Vertex Buffer créé sur la carte video.
	HR(gD3DDevice->CreateVertexBuffer(3 * sizeof(VertexPos),
		D3DUSAGE_WRITEONLY, 0,
		D3DPOOL_MANAGED, &mVB, 0));

	VertexPos* v = 0;
	HR(mVB->Lock(0, 0, (void**)&v, 0));

	v[0] = VertexPos(-1.0f, 0.0f, 2.0f);
	v[1] = VertexPos(0.0f, 1.0f, 2.0f);
	v[2] = VertexPos(1.0f, 0.0f, 2.0f);

	HR(mVB->Unlock());
}
