#include "Engine.h"

extern Engine* gEngine = 0;

Engine::Engine()
	//:window(nullptr)
	//, audio(nullptr)
	//, input(nullptr)
	//, renderer(nullptr)
	//, timer(nullptr)
	//, textures(nullptr)
	//, fonts(nullptr)
	//, musics(nullptr)
	//, sounds(nullptr)
	//, scaling({1, 1})
{

}
Engine::Engine(HINSTANCE hInstance, std::string winCaption)
	: App(hInstance
	, winCaption
	, D3DDEVTYPE_HAL
	, D3DCREATE_HARDWARE_VERTEXPROCESSING)
{
	gApp = this;
}

Engine::~Engine()
{
	//SDL_DestroyWindow(window);
	//window = nullptr;
	//
	//SDL_DestroyRenderer(renderer);
	//renderer = nullptr;
	//
	//delete input;
	//input = nullptr;
	//
	//delete timer;
	//timer = nullptr;
	//
	//delete audio;
	//audio = nullptr;
	//
	//textures = nullptr;
	//musics = nullptr;
	//sounds = nullptr;
	//fonts = nullptr;
	//
	//SDL_Quit();
}

void Engine::Init()
{
	D3DXVECTOR2 res(0.f, 0.0f);
	Init(DEFAULT_WIN_W, DEFAULT_WIN_H, &res);
}

void Engine::Init(int screenWidth, int screenHeight, D3DXVECTOR2* nativeResolution) 
{
	D3DXCreateSprite(gD3DDevice, &spriteBatch);

	//audio = new Audio();
	//input = new Input();
	//timer = new Timer();

	textures = new ResourceHolder<IDirect3DTexture9, int>();
	//fonts = new ResourceHolder<TTF_Font, int>();
	//musics = new ResourceHolder<Mix_Music, int>();
	//sounds = new ResourceHolder<Mix_Chunk, int>();

	//if (NativeResolution.x != 0 && NativeResolution.y != 0)
	//{
	//	this->scaling.x = (screenWidth / NativeResolution.x);
	//	this->scaling.y = (screenHeight / NativeResolution.y);
	//}
}

void Engine::Start()
{
	auto iter = Component::components.begin();
	for (; iter != Component::components.end(); iter++)
	{
		(*iter)->Start();
	}

	gDInput = new DirectInput(GetAppInstance(), GetMainWindow(),
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	gTimer = new GameTimer();
	gTimer->Reset();
}

void Engine::Update()
{
	if (!Component::toAdd.empty())
		CheckNew();
	if (!Component::toDelete.empty())
		CheckDeleted();
	auto iter = Component::components.begin();
	for (; iter != Component::components.end(); iter++)
	{
		if ((*iter)->isActive)
		{
			(*iter)->Update();
		}
	}

	gTimer->Tick();
}

void Engine::Draw()
{

	// TODO Camera class
	// Camera updating
	D3DXMATRIX view;
	D3DXMATRIX orth;
	
	D3DXVECTOR3 pos(0.f, 0.f, -100.f);
	D3DXVECTOR3 up(0.f, 1.f, 0.f);
	D3DXVECTOR3 target(0.f, 0.f, 0.f);
	
	D3DXMatrixLookAtLH(&view, &pos, &target, &up);
	D3DXMatrixOrthoLH(&orth, (float)mD3Dpp.BackBufferWidth, 
		(float)mD3Dpp.BackBufferHeight,	1.f, 5000.f);
	
	// Fixed pipeline
	HR(gD3DDevice->SetRenderState(D3DRS_LIGHTING, false));
	HR(gD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));
	
	HR(gD3DDevice->SetTransform(D3DTS_VIEW, &view));
	HR(gD3DDevice->SetTransform(D3DTS_PROJECTION, &orth));
	// ---------------------

	auto iter = Component::components.begin();
	for (; iter != Component::components.end(); iter++)
	{
		if ((*iter)->isActive)
		{
			(*iter)->Draw();
		}
	}

	//SDL_RenderSetScale(renderer, scaling.x, scaling.y);
	//SDL_RenderPresent(renderer);
	//SDL_RenderClear(renderer);
}

void Engine::OnResetDevice()
{
	spriteBatch->OnResetDevice();

	auto iter = Component::components.begin();
	for (; iter != Component::components.end(); iter++)
	{
		(*iter)->OnResetDevice();
	}
}

void Engine::OnLostDevice()
{
	spriteBatch->OnLostDevice();

	auto iter = Component::components.begin();
	for (; iter != Component::components.end(); iter++)
	{
		(*iter)->OnLostDevice();
	}
}


int Engine::Run()
{
	Start();
	
	int assert = App::Run();
	
	Stop();

	return assert;
}

void Engine::Stop()
{
	//TTF_Quit();
	auto iter = Component::components.begin();
	for (; iter != Component::components.end(); iter++)
	{
		(*iter)->Stop();
	}
	gTimer->Stop();
}

/**
	Remove a component from the update list
	Can also destroy it
	-------------------------
	@comp Component to delete
	@kill Enter "true" to destroy the component and "false" to only remove it from the update list, default is true
	[!] WARNING: Only use false if you have kept another pointer to the element, or you will have memory leak
**/
void Engine::DeleteComponent(Component* comp)
{
	Component::toDelete.push_back(comp);
}

void Engine::ClearComponents()
{
	auto iter = Component::components.begin();
	for (; iter != Component::components.end(); iter++)
	{
		(*iter)->Kill();
	}
}

// /**
//		Move a component to the end of the update list
//		-------------------------
//		@comp Component to move
// **/
// void Engine::MoveBack(Component* comp)
// {
// 	Component::toAdd.push_back(comp);
// 	DeleteComponent(comp);
// } 

void Engine::CheckNew()
{
	auto iter = Component::toAdd.begin();
	for (; iter != Component::toAdd.end(); iter++)
	{
		Component::components.push_back((*iter));
	}
	Component::toAdd.clear();
}

void Engine::CheckDeleted()
{
	auto iter = Component::toDelete.begin();
	for (; iter != Component::toDelete.end(); iter++)
	{
		auto cIter = Component::components.begin();
		for (; cIter != Component::components.end(); cIter++)
		{
			if (*cIter == *iter)
			{
				(*cIter)->Kill();
				Component::components.erase(cIter);
				break;
			}
		}
	}
	Component::toDelete.clear();
}
