#include "stdafx.h"
#include "TextureManager.h"

namespace SmashEngine
{
	TextureManager::TextureManager()
	{
	}

	Texture* TextureManager::GetTexture(const std::string& key)
	{
		if (textures.find(key) == textures.end())
		{
			AddTexture(key);
		}
		return textures[key];
	}

	void TextureManager::AddTexture(const std::string& key)
	{
		textures[key] = new Texture(key);
	}

	TextureManager::~TextureManager()
	{
	}

}
