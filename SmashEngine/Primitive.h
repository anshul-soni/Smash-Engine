////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Primitive.h															 
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
#include "stdafx.h"
#include "Shader.h"
namespace SmashEngine
{
	class Primitive
	{
	public:
		Primitive(){};
		virtual bool Init()=0;
		virtual void Render() = 0;
		virtual void BindVAO()const = 0;
		virtual Shader& GetShader() = 0;
		virtual void SetShader(const std::string&) = 0;
		virtual ~Primitive(){};
	private:
	};
}
