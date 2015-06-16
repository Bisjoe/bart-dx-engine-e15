#include "Utils.h"
#include "ResourceHolder.h"

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder()
{
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::LoadTexture(Identifier id, const std::string& filename)
{
	IDirect3DTexture9* texture;
	HR(D3DXCreateTextureFromFile(gD3DDevice, filename.c_str(), &texture));

	InsertResource(id, std::move(texture));
}


//template <typename Resource, typename Identifier>
//void ResourceHolder<Resource, Identifier>::LoadSound(Identifier id, const std::string& filename)
//{
//	Mix_Chunk* sound;
//	sound = Mix_LoadWAV(filename.c_str());
//	//If the sound couldn't be loaded
//	if (!sound)
//	{
//		printf("Sound could not be loaded, ERROR: %s\n", Mix_GetError());
//	}
//	else
//	{
//		InsertResource(id, std::move(sound));
//	}
//}
//
//
//template <typename Resource, typename Identifier>
//void ResourceHolder<Resource, Identifier>::LoadMusic(Identifier id, const std::string& filename)
//{
//	Mix_Music* music;
//	music = Mix_LoadMUS(filename.c_str());
//	//If the music couldn't be loaded
//	if (!music)
//	{
//		printf("Music could not be loaded, ERROR: %s\n", Mix_GetError());
//	}
//	else {
//		InsertResource(id, std::move(music));
//	}
//}
//
//
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
		return NULL;
	}
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::InsertResource(Identifier id, Resource* resource)
{
	mResources[id] = resource;
	//auto inserted = mResources.insert(std::make_pair(id, std::move(resource)));
	//assert(inserted.second);
}