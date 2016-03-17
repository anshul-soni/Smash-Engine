////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Transform.h															 
/// @date 1/29/2016  5:32 PM			 
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

namespace SmashEngine
{
	class Transform:public Component
	{
	public:
		Transform();
		void Initialize()override;
		void Deserialize(tinyxml2::XMLElement* pElement)override;
		void Destroy()override;

		const glm::vec3& GetPosition()const;
		const glm::vec3& GetRotation()const;
		const glm::vec3& GetScale()const;

		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& position);
		void SetScale(const glm::vec3& position);

		void SetPosition(const float x, const float y, const float z);
		void SetRotation(const float x, const float y, const float z);
		void SetScale(const float x, const float y, const float z);

		~Transform();
	private:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
}