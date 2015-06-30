#pragma once
#include "Utils.h"
#include "GameTimer.h"
#include "DirectInput.h"

class App
{
public:
	App();
	App(HINSTANCE hInstance, std::string winCaption,
		D3DDEVTYPE devType, DWORD requestVP);
	virtual ~App();

	HWND GetMainWindow() { return mhMainWindow; }
	HINSTANCE GetAppInstance() { return mhAppInstance; }

	virtual LRESULT MsgProc(UINT msg, WPARAM wParam, LPARAM lParam);
	virtual int Run();
	virtual void Stop(){}

	D3DPRESENT_PARAMETERS GetParam() { return mD3Dpp; }

protected:
	virtual void InitMainWindow();
	virtual void InitDirect3D();
	virtual bool CheckDeviceCaps() { return true; }
	virtual void OnResetDevice() {}
	virtual void OnLostDevice() {}
	virtual void Update() {}
	virtual void Draw() {}

	D3DPRESENT_PARAMETERS mD3Dpp;

private:

	void PreDraw();
	bool GetDeviceLost();
	void ResetDevice();

	std::string mMainWindowCaption;
	bool mAppPaused;
	
	IDirect3D9* mD3DObject;
	
	HWND		mhMainWindow;
	HINSTANCE	mhAppInstance;
	D3DDEVTYPE	mDevType;
	DWORD		mRequestedVP;
};

