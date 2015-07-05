#include "Utils.h"
#include "ResourceHolder.h"
#include <irrKlang.h>
#include <fstream>

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder()
{
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::LoadTexture(Identifier id, const std::string& filename)
{
	TextureInfos* texInfos = new TextureInfos();

	HR(D3DXCreateTextureFromFileEx(gD3DDevice, filename.c_str(), 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT,
		D3DX_DEFAULT, D3DCOLOR_XRGB(255,255,255), &texInfos->infos, NULL,
		&texInfos->texture));

	InsertResource(id, std::move(texInfos));
}


template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::LoadSound(Identifier id, const std::string& filename)
{
	// Turns out the irrKlang function to load sound only check if a sound was already loaded by comparing the paths 
	// (but never check if a file actually exist for this path)
	// This little check serve that very purpose
	std::ifstream ifile(filename.c_str());
	if (!ifile) {
		std::cout << "ERROR [ResourceHolder:Sound]: sound " << filename << " could not be loaded (File doesn't exist)" << std::endl;
		return;
	}
	irrklang::ISoundSource* sound = gEngine->GetSoundEngine()->addSoundSourceFromFile(filename.c_str());
	if (sound) {
		InsertResource(id, std::move(sound));
		return;
	}
}

//template <typename Resource, typename Identifier>
//void ResourceHolder<Resource, Identifier>::LoadFont(Identifier id, const std::string& filename, int fontSize)
//{
//	TTF_Font* font;
//	font = TTF_OpenFont(filename.c_str(), fontSize);
//	//If the font couldn't be loaded
//	if (!font)
//	{
//		printf("Font could not be loaded, ERROR: %s\n", TTF_GetError());
//	}
//	else
//	{
//		InsertResource(id, std::move(font));
//	}
//}

template <typename Resource, typename Identifier>
Resource* ResourceHolder<Resource, Identifier>::Get(Identifier id) const
{
	//Tries to retrieve the resource corresponding to the specified ID
	auto found = mResources.find(id);
	if (found != mResources.end())
	{
		return found->second; 
	}
	else
	{
		std::cout << "ERROR [ResourceHolder:Get]: Resource not found." << std::endl;
		return NULL;
	}
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::InsertResource(Identifier id, Resource* resource)
{
	auto inserted = mResources.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
bool ResourceHolder<Resource, Identifier>::RemoveResource(Identifier id)
{
	auto found = mResources.find(id);
	if (found != mResources.end()) {
		mResources.erase(found);
		return true;
	}
	else {
		return false;
	}
}