#include "Sprite.h"

//////////////////////////////
//Default Sprite constructor//
//////////////////////////////
//Shouldn't ever be used directly
//////////////////////////////
Sprite::Sprite()
	: texture(nullptr)
	, isVisible(true)
	, alpha(255)
	, angle(0)
	, srcRect(0)
	, dstRect(0)
	//, flipType (SDL_FLIP_NONE)
{

	srcRect = new RECT();
	srcRect->left = 0;
	srcRect->top = 0;
	srcRect->bottom = 0;
	srcRect->right = 0;

	dstRect = new RECT();
	dstRect->left = 0;
	dstRect->top = 0;
	dstRect->bottom = 0;
	dstRect->right = 0;
}

////////////////////////////////
//Sprite (Texture) constructor//
////////////////////////////////
//This'll create a sprite out of a texture.
//This is suited for any non-animated images like a game's HUD, Map or "Title Screen".
//@id - This is your "Sprite sheet" ID.
////////////////////////////////
Sprite::Sprite(Texture::ID id)
	: 
	//texture(Textures->Get(id)),
	isVisible(true)
	, alpha(255)
	, angle(0)
	, srcRect(0)
	, dstRect(0)
	//, flipType(SDL_FLIP_NONE)
{
	srcRect = new RECT();
	srcRect->left = 0;
	srcRect->top = 0;

	//D3DXCreateTextureFromFileEx();
	
	//SDL_QueryTexture(texture, NULL, NULL, &srcRect->w, &srcRect->h);

	dstRect = new RECT();
	dstRect->left = srcRect->left;
	dstRect->top = srcRect->top;
}

/////////////////////////////////////////////////////
//Sprite (Texture & Sprite Coordinates) constructor//meow
/////////////////////////////////////////////////////
//This'll create a sprite out of a texture's using specific coordinates.
//This is suited for all actors (Tiles, Characters, Enemies...)
//@id - This is your "Sprite sheet" ID.
//@srcPos - The Sprite's starting (X,Y) position from the Sprite Sheet
//@srcSize - The Sprite's width/height
////////////////////////////////////////////////////////////////////
Sprite::Sprite(Texture::ID id, const D3DXVECTOR2* const srcPos, const D3DXVECTOR2* const srcSize)
	: 
	//texture(Engine::GetInstance()->GetTextures()->Get(id)), 
	isVisible(true)
	, alpha(255)
	, angle(0)
	, srcRect(0)
	, dstRect(0)
	//, flipType(SDL_FLIP_NONE)
{
	srcRect = new RECT();
	srcRect->left = srcPos->x;
	srcRect->top = srcPos->y;
	srcRect->right = srcSize->x;
	srcRect->bottom = srcSize->y;

	dstRect = new RECT();
	dstRect->left = 0;
	dstRect->top = 0;
	dstRect->right = srcSize->x;
	dstRect->bottom = srcSize->y;
}

Sprite::~Sprite()
{
	delete srcRect;
	delete dstRect;
}

void Sprite::Start()
{

}

void Sprite::Update()
{

}

void Sprite::Stop()
{

}

void Sprite::Draw()
{
	if (isVisible)
	{
		ApplyAlpha();
		//ApplyTexture(gEngine->GetSpriteBatch());
	}
}

void Sprite::ApplyAlpha()
{
	//SDL_SetTextureAlphaMod(texture, alpha);
}

void Sprite::ApplyTexture(const ID3DXSprite* const renderer)
{
	//SDL_RenderCopyEx(renderer, texture, srcRect, dstRect, angle, NULL, flipType);
}


//////////////////
//Sprite Scaling//
//////////////////
//This'll scale a sprite by the desired K factor.
//ScaleBy(1) will reset the texture back to its original file's size.
//@k - Scaling factor
////////////////////////////////////////////////////////////////////
void Sprite::Scale(float k)
{
	//SDL_QueryTexture(texture, NULL, NULL, &dstRect->w, &dstRect->h);
	//dstRect->right = (int)(srcRect->right*k);
	//dstRect->bottom = (int)(srcRect->bottom*k);
	scaling = k;
}

///////////////////
//Sprite Resizing//
///////////////////
//This'll manually resize a sprite to your desired size.
//This will not modify your sprite's sourcing.
//@w - Desired sprite width
//@h - Desired sprite height
////////////////////////////////////////////////////////
void Sprite::ResizeTo(int w, int h)
{
	dstRect->right = w;
	dstRect->bottom = h;
}

///////////////////
//Sprite Flipping//
///////////////////
void Sprite::Flip(unsigned int flip)
{
	//this->flipType = (SDL_RendererFlip)flip;
}

///////////////////
//Sprite Rotation//
///////////////////
void Sprite::SetRotation(float angle)
{
	this->angle = angle;
}

//////////////////////
//Sprite Rotation By//
//////////////////////
void Sprite::RotateBy(float angle)
{
	this->angle += angle;
}
