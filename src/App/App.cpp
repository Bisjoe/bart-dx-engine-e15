#include "App.h"

extern App* gApp = 0;
extern IDirect3DDevice9* gD3DDevice = 0;

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	if (gApp != 0)
	{
		return gApp->MsgProc(msg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

App::App()
{

}

App::App(HINSTANCE hInstance, std::string winCaption,
	D3DDEVTYPE devType, DWORD requestVP, int screenWidth, int screenHeight)
	: mMainWindowCaption(winCaption)
	, mhMainWindow(0)
	, mhAppInstance(hInstance)
	, mDevType(devType)
	, mRequestedVP(requestVP)
	, mD3DObject(0)
	, mAppPaused(false)
{
	srand((unsigned int)time(0));

	//standard input/ output/ error file pointers
	FILE *fpStdIn, *fpStdOut, *fpStdErr;

	// Enable run-time memory check for debug build
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (AllocConsole())
	{
		//Assign the stdin/ stdout/ stderr streams to the newly created console
		_tfreopen_s(&fpStdIn, _T("CONIN$"), _T("r"), stdin);
		_tfreopen_s(&fpStdOut, _T("CONOUT$"), _T("w"), stdout);
		_tfreopen_s(&fpStdErr, _T("CONOUT$"), _T("w"), stderr);
	}
#endif

	InitMainWindow(screenWidth, screenHeight);
	InitDirect3D();
}

App::~App()
{
	ReleaseCOM(gD3DDevice);
	ReleaseCOM(mD3DObject);
}

void App::InitMainWindow(int screenWidth, int screenHeight)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mhAppInstance;
	wc.hIcon = ::LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = ::LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
	wc.lpszMenuName = 0;
	wc.lpszClassName = _T("Hello");

	if (!::RegisterClass(&wc))
	{
		::MessageBox(0, _T("RegisterClass - Failed"), 0, 0);
		PostQuitMessage(0);
	}

	RECT r = { 0, 0, screenWidth, screenHeight };

	mhMainWindow = CreateWindow(
		wc.lpszClassName,
		mMainWindowCaption.c_str(),
		WS_OVERLAPPEDWINDOW,
		r.left,
		r.top,
		r.right,
		r.bottom,
		0, 0,
		mhAppInstance,
		0);

	if (!mhMainWindow)
	{
		::MessageBox(0, _T("CreateWindow - Failed"), 0, 0);
		PostQuitMessage(0);
	}

	::ShowWindow(mhMainWindow, SW_SHOW);
	::UpdateWindow(mhMainWindow);
}

void App::InitDirect3D()
{
	// Step 1
	mD3DObject = Direct3DCreate9(D3D_SDK_VERSION);
	if (!mD3DObject)
	{
		MessageBox(0, _T("Direct3DCreate9 - Failed"), 0, 0);
		PostQuitMessage(0);
	}

	// Step 2
	D3DDISPLAYMODE mode;
	HR(mD3DObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode));
	HR(mD3DObject->CheckDeviceType(D3DADAPTER_DEFAULT, mDevType, mode.Format, mode.Format, true));
	HR(mD3DObject->CheckDeviceType(D3DADAPTER_DEFAULT, mDevType, mode.Format, D3DFMT_X8R8G8B8, false));
	
	//	Step 3
	D3DCAPS9 caps;
	HR(mD3DObject->GetDeviceCaps(D3DADAPTER_DEFAULT, mDevType, &caps));
	DWORD devBehaviourFlags = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		devBehaviourFlags |= mRequestedVP;
	}
	else
	{
		devBehaviourFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	if (caps.DevCaps & D3DDEVCAPS_PUREDEVICE && devBehaviourFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		devBehaviourFlags |= D3DCREATE_PUREDEVICE;
	}

	// Step4
	mD3Dpp.BackBufferWidth = 0;
	mD3Dpp.BackBufferHeight = 0;
	mD3Dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	mD3Dpp.BackBufferCount = 1;
	mD3Dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	mD3Dpp.MultiSampleQuality = 0;
	mD3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	mD3Dpp.hDeviceWindow = mhMainWindow;
	mD3Dpp.Windowed = true;
	mD3Dpp.EnableAutoDepthStencil = true;
	mD3Dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	mD3Dpp.Flags = 0;
	mD3Dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	mD3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Step 5
	HR(mD3DObject->CreateDevice(D3DADAPTER_DEFAULT,
		mDevType,
		mhMainWindow,
		devBehaviourFlags,
		&mD3Dpp,
		&gD3DDevice));
}

LRESULT App::MsgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool isMinimized = false;

	RECT clientRect = { 0 };
	::GetClientRect(mhMainWindow, &clientRect);

	switch (msg)
	{
	case WM_ACTIVATE:
		mAppPaused = LOWORD(wParam) == WA_INACTIVE;
		return 0;

	case WM_SIZE:
		if (gD3DDevice)
		{
			mD3Dpp.BackBufferWidth = LOWORD(lParam);
			mD3Dpp.BackBufferHeight = HIWORD(lParam);

			switch (wParam)
			{
			case SIZE_MINIMIZED:
				mAppPaused = true;
				isMinimized = true;
				break;
			case SIZE_MAXIMIZED:
				mAppPaused = false;
				isMinimized = false;
				ResetDevice();
				break;
			case SIZE_RESTORED:
				mAppPaused = false;
				if (isMinimized && mD3Dpp.Windowed)
				{
					ResetDevice();
				}
				isMinimized = false;
				break;
			}
		}
		return 0;

	case WM_EXITSIZEMOVE:
		GetClientRect(mhMainWindow, &clientRect);
		mD3Dpp.BackBufferWidth = clientRect.right;
		mD3Dpp.BackBufferHeight = clientRect.bottom;
		ResetDevice();
		return 0;

	case WM_LBUTTONDOWN:
		::MessageBox(0, "Hello World", 0, 0);
		return 0;
	
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			DestroyWindow(mhMainWindow);
		}
		return 0;

	case WM_CLOSE:
		DestroyWindow(mhMainWindow);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;		
	}
	return ::DefWindowProc(mhMainWindow, msg, wParam, lParam);
}

int App::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	gTimer->Reset();

	while (msg.message != WM_QUIT)
	{
		gDInput->poll();
		gTimer->Tick();

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (mAppPaused)
			{
				Sleep(20);
				continue;
			}

			if (!GetDeviceLost())
			{
				Update();
				PreDraw();
			}
		}
	}

	return (int)msg.wParam;
}

bool App::GetDeviceLost()
{
	HRESULT hr = gD3DDevice->TestCooperativeLevel();
	if (hr == D3DERR_DEVICELOST)
	{
		Sleep(20);
		return true;
	}
	else if (hr == D3DERR_DRIVERINTERNALERROR)
	{
		MessageBox(0, _T("Internal driver error... Exiting"), 0, 0);
		PostQuitMessage(0);
		return true;
	}
	else if (hr == D3DERR_DEVICENOTRESET)
	{
		ResetDevice();
		return false;
	}
	return false;
}

void App::ResetDevice()
{
	OnLostDevice();
	gD3DDevice->Reset(&mD3Dpp);
	OnResetDevice();
}

void App::PreDraw()
{
	HR(gD3DDevice->Clear(0, 0,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0));

	HR(gD3DDevice->BeginScene());

	Draw();

	HR(gD3DDevice->EndScene());

	HR(gD3DDevice->Present(0, 0, 0, 0));
}
