////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file ResourceType.h															 
/// @date 1/23/2016  3:30 PM			 
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

namespace SmashEngine
{
	enum ResourceType
	{
		RESOURCE_Model = 0,
		RESOURCE_FragmentShader,
		RESOURCE_VertexShader,
		RESOURCE_Texture,
		RESOURCE_Object
	};
}