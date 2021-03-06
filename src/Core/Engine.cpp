#include "Engine.h"

extern Engine* gEngine = 0;

Engine::Engine()
	//: window(nullptr)
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

Engine::Engine(HINSTANCE hInstance, std::string winCaption, int screenWidth, int screenHeight)
	: screenSize(screenWidth, screenHeight)
	, App(hInstance, winCaption, D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING, screenWidth, screenHeight)
	, soundEngine(nullptr)
	
{
	gApp = this;
	InitAllVertexDeclarations();
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
	//textures = nullptr;
	//musics = nullptr;
	//sounds = nullptr;
	//fonts = nullptr;
	//
	//SDL_Quit();

	// Clearing the Sound Engine
	soundEngine->drop();
	soundEngine = nullptr;
	
	delete camera;
	camera = nullptr;
	
	DestroyAllVertexDeclarations();
}

void Engine::Init()
{
	D3DXVECTOR2 res(0.f, 0.0f);
	Init(&res);
}

void Engine::Init(D3DXVECTOR2* nativeResolution) 
{
	// ==================================
	// ----------------------------------
	D3DXCreateSprite(gD3DDevice, &spriteBatch);

	// ==================================
	// Audio System
	// ----------------------------------
	soundEngine = irrklang::createIrrKlangDevice();
	if (!soundEngine)
		std::cout << "Sound engine was not initialized" << std::endl;

	// ==================================
	// ----------------------------------
	//input = new Input();
	//timer = new Timer();

	// ==================================
	// Resource Holder
	// ----------------------------------
	textures = new ResourceHolder<TextureInfos, int>();
	//fonts = new ResourceHolder<TTF_Font, int>();
	sounds = new ResourceHolder<irrklang::ISoundSource, int>();

	// ==================================
	// ----------------------------------
	//if (NativeResolution.x != 0 && NativeResolution.y != 0)
	//{
	//	this->scaling.x = (screenSize.x / NativeResolution.x);
	//	this->scaling.y = (screenSize.y / NativeResolution.y);
	//}
	
	D3DPRESENT_PARAMETERS currentParams = gApp->GetParam();
	camera = new Camera(currentParams);
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
	camera->BuildViewProjMtx();

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

