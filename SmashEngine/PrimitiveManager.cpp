////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file PrimitiveManager.cpp															 
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
#include "PrimitiveManager.h"
#include "Cube.h"
#include "Sphere.h"
#include "WireFrame.h"

namespace SmashEngine
{
	PrimitiveManager::PrimitiveManager()
	{
	}

	Model* PrimitiveManager::GetModel(const std::string& key)
	{
		if (models.find(key) == models.end())
		{
			AddModel(key);
		}
		return models[key];
	}

	Primitive * PrimitiveManager::GetPrimitive(const std::string & key)
	{
		if (primitives.find(key) == primitives.end())
		{
			AddPrimitive(key);
		}
		return primitives[key];
	}

	PrimitiveManager::~PrimitiveManager()
	{
	}

	void PrimitiveManager::AddModel(const std::string& key)
	{
		models[key] = new Model(key.c_str());
	}
	void PrimitiveManager::AddPrimitive(const std::string & key)
	{
		if (key == "Cube")
		{
			primitives[key] = new Cube();
		}
	    else if (key == "Sphere")
		{
			primitives[key] = new Sphere();
		}
		else if (key == "Wireframe")
		{
			primitives[key] = new Wireframe();
		}
	}
}