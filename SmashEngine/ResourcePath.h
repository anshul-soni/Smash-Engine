////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file ResourcePath.h															 
/// @date 1/26/2016  7:43 PM			 
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
#include "ResourceType.h"

namespace SmashEngine
{
	class ResourcePath
	{
	public:
		static ResourcePath& GetInstance();
		std::string GetPath(ResourceType type,const std::string& key) const;
	private:
		ResourcePath();
		ResourcePath(const ResourcePath&) = delete;
		ResourcePath& operator=(const ResourcePath&) = delete;
	};
}