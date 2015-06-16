#pragma once

#include "Common.h"
#include "Component.h"
//#include "DirectInput.h"
//#include "GameTimer.h"

// Resources
#define Textures gEngine->GetTextures()
//#define Fonts cEngine->GetFonts()
//#define Sounds cEngine->GetSounds()
//#define Musics cEngine->GetMusics()

// Audio
//#define AudioSys cEngine->GetAudio()

// Inputs
//#define ThisKeyPressed gDInput->IsKeyPressed
//#define ThisKeyHeld cEngine->GetInput()->IsKeyHeld
//#define ThisKeyReleased cEngine->GetInput()->IsKeyReleased

class Engine: App
{

public:
	Engine();
	Engine(HINSTANCE hInstance, std::string winCaption);
	~Engine();

	void Init();
	void Init(int screenWidth, int screenHeight, D3DXVECTOR2* nativeResolution);
	int Run();
	void Stop();

	/**
		Remove a component from the update list
		Can also destroy it
		-------------------------
		@comp Component to delete
		[!] WARNING: Also destroy the component, use only if you won't be needing it again
	**/
	void DeleteComponent(Component* comp);

	void ClearComponents();

//	 WORK IN PROGRESS, problem of memory leak until a safe method of access for the component removed is implemented, do not use as of now
//
//	/**
//		Move a component to the end of the update list
//		-------------------------
//		@comp Component to move
//	**/
//	void MoveBack(Component* comp);-
//
//
//	/**
//		Remove a component from the update list
//		Add it in the "removed" list for later use (Does not destroy it)
//		-------------------------
//		@comp Component to delete
//		[!] WARNING: The component will be removed from the update list and no longer updated, but will still exist.
//	**/
//	void RemoveComponent(Component* comp);
//
//
//	/**
//		
//	**/
//	void AddComponent(Component* comp);

	

	//Audio*								GetAudio()		 { return audio;	}
	//Input*								GetInput()		 { return input;	}
	//Timer*								GetTimer()		 { return timer;	}
	//SDL_Renderer*						GetRenderer()	 { return renderer; }
	//SDL_Window*							GetWindow()		 { return window;	}
	ResourceHolder<IDirect3DTexture9, int>*	GetTextures()	 { return textures; }
	//ResourceHolder<TTF_Font, int>*		GetFonts()		 { return fonts;	}
	//ResourceHolder<Mix_Music, int>*		GetMusics()		 { return musics;	}
	//ResourceHolder<Mix_Chunk, int>*		GetSounds()		 { return sounds;	}

private:
	void Start();
	void Update();
	void Draw();

	void CheckNew();
	void CheckDeleted();

	//Audio*								audio;
	//Input*								input;
	//Timer*								timer;
	ID3DXSprite* spriteBatch;
	//SDL_Window*							window;
	ResourceHolder<IDirect3DTexture9, int>*	textures;
	//ResourceHolder<TTF_Font, int>*		fonts;
	//ResourceHolder<Mix_Music, int>*		musics;
	//ResourceHolder<Mix_Chunk, int>*		sounds;
	//point<float>						scaling;
};

extern Engine* gEngine;