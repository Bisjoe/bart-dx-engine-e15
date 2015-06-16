#pragma once
#include "Common.h"
#include "Engine.h"
#include "Rectangle.h"

// Flip shortcuts, lolwut
#ifndef FLIPPERS
#define FLIPPERS
#define FLIP_N SDL_FLIP_NONE
#define FLIP_H SDL_FLIP_HORIZONTAL
#define FLIP_V SDL_FLIP_VERTICAL
#endif

class Sprite :
	public Component
{
public:
	Sprite(Texture::ID id);
	Sprite(Texture::ID id, const D3DXVECTOR2* const srcPos, const D3DXVECTOR2* const srcSize);
	~Sprite();

	virtual void Start();
	virtual void Update();
	virtual void Stop();

	void Draw();
	void Kill() { delete this; }

	void SetAlpha(int alpha)						{ this->alpha = alpha; }
	void SetPosition(int x, int y)					{ dstRect->left = x; dstRect->top = y; }
	void SetDstFrame(int x, int y, int w, int h)	{ dstRect->left = x, dstRect->top = y; dstRect->right = w; dstRect->bottom = h; }
	void SetSrcFrame(int x, int y, int w, int h)	{ srcRect->left = x, srcRect->top = y; srcRect->right = w; srcRect->bottom = h; }
	//void SetTexture(Texture::ID id)				{ texture = gEngine->GetTextures()->Get(id); }
	void SetVisible(bool visible)					{ isVisible = visible; }
	RECT GetRect()									{ return{ dstRect->left, dstRect->top, dstRect->right, dstRect->bottom }; }

	void ResizeTo(int w, int h);
	void Flip(unsigned int flip);
	void SetRotation(float angle);
	void RotateBy(float angle);
	void Scale(float k);

	// Getters
	bool IsVisible()			{ return isVisible; }
	D3DXVECTOR3 GetPosition()	{ return D3DXVECTOR3(dstRect->left, dstRect->top, 0.f); }
	D3DXVECTOR2 GetSize()		{ return D3DXVECTOR2(dstRect->right, dstRect->bottom); }

protected:
	Sprite();
	void ApplyTexture(const ID3DXSprite* const spriteBatch);
	void ApplyAlpha();

	IDirect3DTexture9* texture;
	RECT* dstRect;
	RECT* srcRect;
	//SDL_RendererFlip flipType;

	int alpha;
	float angle;
	float scaling;
	bool isVisible;

};


