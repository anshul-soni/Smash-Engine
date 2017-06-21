////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file PrimitiveManager.h															 
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
#include "Model.h"

namespace SmashEngine
{
	class PrimitiveManager
	{
	public:
		static PrimitiveManager& GetInstance()
		{
			static PrimitiveManager instance;
			return instance;
		}
													PrimitiveManager();
		Model*										GetModel(const std::string& key);
		Primitive*									GetPrimitive(const std::string& key);
													~PrimitiveManager();
	private:
		void										AddModel(const std::string& key);
		void										AddPrimitive(const std::string& key);
		std::unordered_map<std::string, Model*>		models;
		std::unordered_map<std::string, Primitive*> primitives;
	};
}