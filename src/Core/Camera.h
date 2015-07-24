#pragma once
#include "Component.h"
#include "Utils.h"
#include "Common.h"

////////////////////////////////////////////////////////////////////////////////
// Camera Class:
//		-> This is the camera class that's been pulled out of the engine.
//			@Virtual Destructor -> Has been added so that this class can be used as
//								  a base class for different camera types.
//			@Virtual BuildViewProjMtx -> For the same reason as above.
//			@Virtual Update     -> Same reason as above.
///////////////////////////////////////////////////////////////////////////////////


class Camera :
	public Component
{
public:
	Camera();
	Camera(D3DPRESENT_PARAMETERS currentParam);
	virtual ~Camera();
	
	D3DXMATRIX						GetView()							{ return mView; }
	D3DXMATRIX						GetProj()							{ return mProj; }
	D3DXVECTOR3						GetCamPos()							{ return mPos; }
	
	// Sets the position of the camera to allow translations of the camera.
	virtual void							SetCamPos(D3DXVECTOR3 newPosition)	{ mPos.x = newPosition.x; mPos.y = newPosition.y; mPos.z = newPosition.z; }
	
	virtual void Update();
	virtual void BuildViewProjMtx();

private:
	D3DPRESENT_PARAMETERS mD3Dpp;

	D3DXMATRIX mView;
	D3DXMATRIX mProj;
	D3DXVECTOR3 mPos;
	D3DXVECTOR3 mUp;
	D3DXVECTOR3 mTarget;
};

