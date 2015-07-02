#include "Peggle.h"
#include "ResourceIDs.h"
#include "Ball.h"
#include "Block.h"

Peggle::Peggle()
{
	Textures->LoadTexture(Texture::Ball, "ball.png");
	Textures->LoadTexture(Texture::Block, "block.png");

	Sounds->LoadSound(Sound::TestMusicID, "testmusic.mp3");
	Sounds->LoadSound(Sound::TestSoundFXID, "bell.wav");

	AudioSys->play2D(Sounds->Get(Sound::TestMusicID));
	AudioSys->play2D(Sounds->Get(Sound::TestSoundFXID));

	Ball* ball = new Ball();
	Block* block = new Block();
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
