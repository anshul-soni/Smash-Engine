#pragma once
#include "Model.h"

namespace SmashEngine
{
	class TextureManager
	{
	public:
		static TextureManager& GetInstance()
		{
			static TextureManager instance;
			return instance;
		}
		TextureManager();
		Texture* GetTexture(const std::string& key);
		~TextureManager();
	private:
		void AddTexture(const std::string& key);
		std::unordered_map<std::string, Texture*> textures;
	};
}