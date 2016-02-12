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
			pElement->FirstChildElement("mass")->QueryFloatText(&inverseMass);
		}else
		{
			std::cout << "error reading inverseMass" << std::endl;
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

	float Body::GetInverseMass()const
	{
		return inverseMass;
	}
}
