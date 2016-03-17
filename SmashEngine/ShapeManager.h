////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file ShapeManager.h															 
/// @date 2/5/2016  11:27 PM			 
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
#include "Shape.h"

namespace SmashEngine
{
	class ShapeManager
	{
	public:
		static ShapeManager& GetInstance()
		{
			static ShapeManager instance;
			return instance;
		}
		ShapeManager();
		Shape* GetShape(const std::string& key);
		~ShapeManager();
	private:
		void AddShape(const std::string& key);
		std::unordered_map<std::string, Shape*> Shapes;
	};
}