////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Body.cpp															 
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
#include "stdafx.h"
#include "Body.h"

namespace SmashEngine
{
	Body::Body() :
		type(TYPE_Body), 
		inverseMass(0.0f), 
		velocity(glm::vec3(0)), 
		force(glm::vec3(0))
	{
	}

	void Body::Initialize()
	{
	}

	void Body::Deserialize(tinyxml2::XMLElement* pElement)
	{
		if (pElement->FirstChildElement("velocity") != nullptr)
		{
			if (pElement->FirstChildElement("velocity")->QueryFloatAttribute("x", &velocity.x) != tinyxml2::XML_SUCCESS)
			{
				std::cout << "error reading velocity" << std::endl;
			}
			if (pElement->FirstChildElement("velocity")->QueryFloatAttribute("y", &velocity.y) != tinyxml2::XML_SUCCESS)
			{
				std::cout << "error reading velocity" << std::endl;
			}
			if (pElement->FirstChildElement("velocity")->QueryFloatAttribute("z", &velocity.z) != tinyxml2::XML_SUCCESS)
			{
				std::cout << "error reading velocity" << std::endl;
			}
		}
		if (pElement->FirstChildElement("mass") != nullptr)
		{
			float mass;
			pElement->FirstChildElement("mass")->QueryFloatText(&mass);
			if(mass == 0.0f)
			{
				inverseMass = 0.0f;
			}else
			{
				inverseMass = 1 / mass;
			}
		}else
		{
			std::cout << "error reading mass" << std::endl;
		}
	}

	void Body::Destroy()
	{
	}

	void Body::SetVelocity(const glm::vec3& velocity)
	{
		this->velocity = velocity;
	}

	void Body::SetForce(const glm::vec3& force)
	{
		this->force = force;
	}

	const glm::vec3& Body::GetVelocity() const
	{
		return velocity;
	}

	const glm::vec3& Body::GetForce() const
	{
		return force;
	}

	float Body::GetInverseMass() const
	{
		return inverseMass;
	}
}
