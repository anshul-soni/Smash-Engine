////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file ModelManager.cpp															 
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
#include "ModelManager.h"

namespace SmashEngine
{
	ModelManager::ModelManager()
	{
	}

	Model* ModelManager::GetModel(const std::string& key)
	{
		if (models.find(key)==models.end())
		{
			AddModel(key);
		}
		return models[key];
	}

	ModelManager::~ModelManager()
	{
	}

	void ModelManager::AddModel(const std::string& key)
	{
		models[key] = new Model(key.c_str());
	}
}
