////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Body.h															 
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
	class Body:public Component
	{
	public:
		Body();
		void Initialize()override;
		void Deserialize(tinyxml2::XMLElement* pElement)override;
		void Destroy()override;
		void SetVelocity(const glm::vec3& velocity);
		void SetForce(const glm::vec3& force);
		const glm::vec3& GetVelocity()const;
		const glm::vec3& GetForce()const;
		float GetInverseMass()const;

		/* Clears the accumalated force in each step.
		   Should be called automatically after each integration step 
		*/
		void ClearAccumulator();

        void AddForce(glm::vec3& force);
	private:
		const ComponentType type;
		float inverseMass;
		glm::vec3 velocity;
		glm::vec3 force;

		/* Holds the force to be applied at next simulation iteration only.
		   This value is zeroed at each integration step*/
		glm::vec3 forceAccumulated;

	};
}
