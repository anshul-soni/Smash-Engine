////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file TextureManager.h															 
/// @date 1/23/2016  2:49 PM			 
/// @author Anshul Soni <soni.anshul93@gmail.com>								 
///																				 
/// As a condition of your accessing this Engine, you agree to be bound 		 
///	by the following terms and conditions: 										 
/// The software was created by Anshul Soni, and all copyright and other 		 
///	rights in such is owned by Anshul Soni. While you are allowed to access,  	 
/// download and use the code for non-commercial, home use you hereby expressly  
/// agree that you will not otherwise copy, distribute, modify, the code. 		 
////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Texture.h"

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