////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Render.h															 
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
#include "Component.h"
#include "Shader.h"
#include "Model.h"

namespace SmashEngine
{
	class Render:public Component
	{
	public:
		Render();
		void Initialize()override;
		void Deserialize(tinyxml2::XMLElement* pElement)override;
		void Draw();
		void Destroy()override;
		~Render();
	private:
		Drawable* drawableComponent;
	};
}
