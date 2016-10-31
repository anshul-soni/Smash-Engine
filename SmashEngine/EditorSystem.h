////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file EditorSystem.h															 
/// @date 1/30/2016  5:31 PM			 
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
#include "WindowSystem.h"

namespace SmashEngine
{
	class EditorSystem :
		public WindowSystem
	{
	public:
		EditorSystem(void);
		void Init()override;
		void Update(float dt)override;
		SystemType GetType()const override;
		void Release()override;
		virtual ~EditorSystem(void);
	private:
		const SystemType type;
	};
}
