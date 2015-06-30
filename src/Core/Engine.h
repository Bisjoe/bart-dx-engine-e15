 #pragma once

#include "Common.h"
#include "Component.h"
#include "TextureInfos.h"
//#include "DirectInput.h"
//#include "GameTimer.h"

// Resources
#define Textures gEngine->GetTextures()
//#define Fonts cEngine->GetFonts()
#define Sounds gEngine->GetSounds()

// Audio
// Using irrKlang library
// Doc: http://www.ambiera.com/irrklang/docu/index.html
#define AudioSys gEngine->GetSoundEngine()

// Inputs
//#define ThisKeyPressed gDInput->IsKeyPressed
//#define ThisKeyHeld cEngine->GetInput()->IsKeyHeld
//#define ThisKeyReleased cEngine->GetInput()->IsKeyReleased

class Engine: App
{

public:
	Engine();
	Engine(HINSTANCE hInstance, std::string winCaption, int screenWidth = DEFAULT_WIN_W, int screenHeight = DEFAULT_WIN_H);
	~Engine();

	void Init();
	void Init(D3DXVECTOR2* nativeResolution);
	int Run();
	void Stop();

	/*
	 *	Remove a component from the update list
	 *	Can also destroy it
	 *	-------------------------
	 *	@comp Component to delete
	 *	[!] WARNING: Also destroy the component, use only if you won't be needing it again
	 */
	void DeleteComponent(Component* comp);

	void ClearComponents();

	ID3DXSprite*									GetSpriteBatch() { return spriteBatch; }
	irrklang::ISoundEngine*							GetSoundEngine() { return soundEngine; }
	D3DXVECTOR2										GetScreenSize()  { return screenSize;  }
	//Audio*										GetAudio()		 { return audio;	}
	//Input*										GetInput()		 { return input;	}
	//Timer*										GetTimer()		 { return timer;	}
	//SDL_Renderer*									GetRenderer()	 { return renderer;	}
	//SDL_Window*									GetWindow()		 { return window;	}
	ResourceHolder<TextureInfos, int>*				GetTextures()	 { return textures;	}
	//ResourceHolder<TTF_Font, int>*				GetFonts()		 { return fonts;	}
	ResourceHolder<irrklang::ISoundSource, int>*	GetSounds()		 { return sounds;	}

private:
	void OnResetDevice();
	void OnLostDevice();
	void Start();
	void Update();
	void Draw();

	void CheckNew();
	void CheckDeleted();

	D3DXVECTOR2										screenSize;
	irrklang::ISoundEngine*							soundEngine;
	//Input*										input;
	//Timer*										timer;
	ID3DXSprite*									spriteBatch;
	//SDL_Window*									window;
	ResourceHolder<TextureInfos, int>*				textures;
	//ResourceHolder<TTF_Font, int>*				fonts;
	ResourceHolder<irrklang::ISoundSource, int>*	sounds;
	//point<float>									scaling;
};

extern Engine* gEngine;