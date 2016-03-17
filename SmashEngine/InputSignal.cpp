////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file InputSignal.cpp															 
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
#include "stdafx.h"
#include "InputSignal.h"

namespace SmashEngine
{
	InputSignal::InputSignal(InputType type, const glm::vec3& param)
		:type(type),
		param(param)
	{
	}

	InputType InputSignal::GetType() const
	{
		return type;
	}

	const glm::vec3& InputSignal::GetParam() const
	{
		return param;
	}
}
