#include "Camera.h"


Camera::Camera()
	: mPos(0.f, 1.f, -20.f)
	, mUp(0.f, 1.f, 0.f)
	, mTarget(0.f, 1.f, 0.f)
{
}

Camera::Camera(D3DPRESENT_PARAMETERS currentParam)
	: mD3Dpp(currentParam)
	, mPos(0.f, 1.f, -20.f)
	, mUp(0.f, 1.f, 0.f)
	, mTarget(0.f, 1.f, 0.f)
{

}


Camera::~Camera()
{
}

void Camera::Update()
{

}

void Camera::BuildViewProjMtx()
{
	D3DXMatrixLookAtLH(&mView, &mPos, &mTarget, &mUp);
	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI * 0.25f,
		(float)mD3Dpp.BackBufferWidth / (float)mD3Dpp.BackBufferHeight,
		1.0f, 5000.0f);

	// Fixed pipeline
	HR(gD3DDevice->SetRenderState(D3DRS_LIGHTING, false));
	HR(gD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));

	HR(gD3DDevice->SetTransform(D3DTS_VIEW, &mView));
	HR(gD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj));
	// ---------------------
}