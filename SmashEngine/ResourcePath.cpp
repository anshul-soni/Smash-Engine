////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file ResourcePath.cpp															 
/// @date 1/28/2016  8:45 PM			 
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
#include "ResourcePath.h"

namespace SmashEngine
{
	ResourcePath& ResourcePath::GetInstance()
	{
		static ResourcePath instance;
		return instance;
	}

	std::string ResourcePath::GetPath(ResourceType type, const std::string& key) const
	{
		std::string resourcePath = "resources/";
		switch(type)
		{
		case RESOURCE_Model:
			resourcePath += "models/";
			resourcePath += key;
			//resourcePath += ".model";
			break;
		case RESOURCE_Object:
			resourcePath += "objects/";
			resourcePath += key;
			resourcePath += ".xml";
			break;
		case RESOURCE_FragmentShader:
			resourcePath += "shaders/";	
			resourcePath += key;
			resourcePath += ".frag";
			break;
		case RESOURCE_VertexShader:
			resourcePath += "shaders/";
			resourcePath += key;
			resourcePath += ".vert";
			break;
		case RESOURCE_Texture:
			resourcePath += "model/";
			resourcePath += key;
			break;
		default:
			resourcePath += key;
			break;
		}
		return resourcePath;
	}

	ResourcePath::ResourcePath()
	{
	}
}
