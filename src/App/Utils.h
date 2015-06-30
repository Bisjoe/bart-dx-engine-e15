#include <Windows.h>
#include <string>
#include <tchar.h>
#include <d3dx9.h>
#include <DxErr.h>
#include <time.h>

// Forward declaration
class App;

extern App* gApp;
extern IDirect3DDevice9* gD3DDevice;

// Macro
#define ReleaseCOM(x)								\
{													\
	if(x)											\
	{												\
		x->Release();								\
		x = 0;										\
	}												\
}

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)										\
{													\
	HRESULT hr = x;									\
	if(FAILED(hr))									\
	{												\
		DXTrace(__FILE__, __LINE__, hr, #x, true);	\
	}												\
}								
#endif // HR
#else
#ifndef HR
#define HR(x) x;
#endif
#endif 