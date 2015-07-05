#pragma once
#include "Common.h"
#include "Engine.h"
#include "Rectangle.h"
#include "TextureInfos.h"

class Sprite :
	public Component
{
public:
	Sprite(Texture::ID id);
	Sprite(Texture::ID id, int x, int y);
	Sprite(Texture::ID id, const D3DXVECTOR2* const srcPos, const D3DXVECTOR2* const srcSize);
	virtual ~Sprite();

	// Getters
	bool IsVisible()										 { return isVisible; }
	RECT GetRect()											 { return{ dstRect->left, dstRect->top, dstRect->right, dstRect->bottom }; }
	D3DXVECTOR3 GetPosition()								 { return D3DXVECTOR3(mTranslation._41, mTranslation._42, 0.f); }
	D3DXVECTOR2 GetSize()									 { return D3DXVECTOR2(dstRect->right, dstRect->bottom); }
	TextureInfos* GetTextureInfos()							 { return texInfos; }

	// Setters
	void SetAlpha(int alpha)								 { this->alpha = alpha; }
	void SetPosition(D3DXVECTOR2* pos)						 { SetPosition(pos->x, pos->y); }
	void SetPosition(float x, float y)						 { dstRect->left = x; dstRect->top = y; 
															   D3DXMatrixTranslation(&mTranslation, x, y, 10.0f); }
	void SetDstFrame(float x, float y, float w, float h)	 { dstRect->left = x, dstRect->top = y; 
															   dstRect->right = w; dstRect->bottom = h;
															   D3DXMatrixTranslation(&mTranslation, x, y, 10.0f); }
	void SetSrcFrame(int x, int y, int w, int h)			 { srcRect->left = x, srcRect->top = y; srcRect->right = w; srcRect->bottom = h; }
	void SetTexInfos(Texture::ID id)						 { texInfos = Textures->Get(id); }
	void SetVisible(bool visible)							 { isVisible = visible; }
	void ResizeTo(int w, int h)								 { dstRect->right = w; dstRect->bottom = h; }
	// void Flip(unsigned int flip);
	void SetRotationRad(float yaw, float pitch, float roll)  { D3DXMatrixRotationYawPitchRoll(&mRotation, yaw, pitch, roll); }
	void SetRotationDeg(float yaw, float pitch, float roll)  { SetRotationRad(D3DXToRadian(yaw), D3DXToRadian(pitch), D3DXToRadian(roll)); }
	void SetPivot(D3DXVECTOR3 pivot)						 { mPivot = pivot; }
	void Scale(float k);
	
	// Methods
	virtual void Start();
	virtual void Update();
	virtual void Stop();
	void Draw();
	void Kill()												 { delete this; }

protected:
	Sprite();
	void ApplyTexture(ID3DXSprite* const spriteBatch);
	void ApplyAlpha();

	TextureInfos* texInfos;
	RECT* dstRect;
	RECT* srcRect;

	int alpha;
	float scaling;
	bool isVisible;

	D3DXVECTOR3 mPivot;
	D3DXMATRIX mRotation;
	D3DXMATRIX mTranslation;
};


