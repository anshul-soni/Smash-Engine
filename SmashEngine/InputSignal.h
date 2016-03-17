////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file InputSignal.h															 
/// @date 1/27/2016  10:59 PM			 
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
#include "InputType.h"
namespace SmashEngine
{
	class InputSignal
	{
	public:
		explicit InputSignal(InputType type,const glm::vec3& param);
		InputType GetType()const;
		const glm::vec3& GetParam()const;
	private:
		const InputType type;
		const glm::vec3 param;
	};
}
