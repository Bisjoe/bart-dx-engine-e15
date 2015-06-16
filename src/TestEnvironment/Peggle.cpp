#include "Peggle.h"
#include "Sprite.h"
#include "ResourceIDs.h"

Peggle::Peggle()
{
	Textures->LoadTexture(Texture::ELEPHANT_DE_MER, "safe_image.jpg");
	Textures->LoadTexture(Texture::POW_POW_POW, "powpowpow.png");

	Sprite* s = new Sprite(Texture::ELEPHANT_DE_MER);
	Sprite* s2 = new Sprite(Texture::POW_POW_POW);
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
