////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file ShaderManager.cpp															 
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
#include "stdafx.h"
#include "ShaderManager.h"

namespace SmashEngine
{
	ShaderManager::ShaderManager()
	{
	}

	Shader* ShaderManager::GetShader(const std::string& key)
	{
		if (shaders.find(key) == shaders.end())
		{
			AddShader(key);
		}
		return shaders[key];
	}

	void ShaderManager::AddShader(const std::string& key)
	{
		shaders[key] = new Shader(key);
	}

	ShaderManager::~ShaderManager()
	{
	}
}
