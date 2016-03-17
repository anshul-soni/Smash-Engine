////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file ShaderManager.h															 
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
#include "Shader.h"

namespace SmashEngine
{
	class ShaderManager
	{
	public:
		static ShaderManager& GetInstance()
		{
			static ShaderManager instance;
			return instance;
		}
		ShaderManager();
		Shader* GetShader(const std::string& key);
		~ShaderManager();
	private:
		void AddShader(const std::string& key);
		std::unordered_map<std::string, Shader*> shaders;
	};
}