#include "Peggle.h"
#include "Sprite.h"
#include "ResourceIDs.h"

Peggle::Peggle()
{
	Textures->LoadTexture(Texture::ELEPHANT_DE_MER, "safe_image.jpg");
	Textures->LoadTexture(Texture::POW_POW_POW, "powpowpow.png");
	Sounds->LoadSound(Sound::TestMusicID, "testmusic.mp3");
	Sounds->LoadSound(Sound::TestSoundFXID, "bell.wav");
	AudioSys->play2D(Sounds->Get(Sound::TestMusicID));
	AudioSys->play2D(Sounds->Get(Sound::TestSoundFXID));

	Sprite* s = new Sprite(Texture::ELEPHANT_DE_MER);

	D3DXVECTOR3 center(s->GetTextureInfos()->infos.Width / 2, s->GetTextureInfos()->infos.Height / 2, 0.0f);
	s->SetPivot(center);
	s->SetRotation(0.0, 0.0, D3DX_PI/2);

	Sprite* s2 = new Sprite(Texture::POW_POW_POW);

	std::cout << s->GetTextureInfos()->infos.Width;
}

Peggle::~Peggle()
{

}

void Peggle::Start()
{

}

void Peggle::Update()
{

}

void Peggle::Draw()
{

}

void Peggle::Stop()
{

}
