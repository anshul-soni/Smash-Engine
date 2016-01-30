#include "stdafx.h"
#include "Transform.h"

namespace SmashEngine
{
	Transform::Transform() :position(glm::vec3(0)),
		rotation(glm::vec3(0)),
		scale(glm::vec3(1))
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Deserialize(tinyxml2::XMLElement* pElement)
	{

		if (pElement->FirstChildElement("position") != nullptr)
		{
			if (pElement->FirstChildElement("position")->QueryFloatAttribute("x", &position.x) != tinyxml2::XML_SUCCESS)
			{
				std::cout << "error reading position" << std::endl;
			}
			if (pElement->FirstChildElement("position")->QueryFloatAttribute("y", &position.y) != tinyxml2::XML_SUCCESS)
			{
				std::cout << "error reading position" << std::endl;
			}
			if (pElement->FirstChildElement("position")->QueryFloatAttribute("z", &position.z) != tinyxml2::XML_SUCCESS)
			{
				std::cout << "error reading position" << std::endl;
			}
		}else
		{
			std::cout << "error reading position" << std::endl;
		}
		if (pElement->FirstChildElement("rotation") != nullptr)
		{
			if (pElement->FirstChildElement("rotation")->QueryFloatAttribute("x", &rotation.x) != tinyxml2::XML_SUCCESS)
			{
				std::cout << "error reading rotation" << std::endl;
			}
			if (pElement->FirstChildElement("rotation")->QueryFloatAttribute("y", &rotation.y) != tinyxml2::XML_SUCCESS)
			{
				std::cout << "error reading rotation" << std::endl;
			}
			if (pElement->FirstChildElement("rotation")->QueryFloatAttribute("z", &rotation.z) != tinyxml2::XML_SUCCESS)
			{
				std::cout << "error reading rotation" << std::endl;
			}
		}
		else
		{
			std::cout << "error reading rotation" << std::endl;
		}
		if (pElement->FirstChildElement("scale") != nullptr)
		{
			if (pElement->FirstChildElement("scale")->QueryFloatAttribute("x", &scale.x) != tinyxml2::XML_SUCCESS)
			{
				std::cout << "error reading scale" << std::endl;
			}
			if (pElement->FirstChildElement("scale")->QueryFloatAttribute("y", &scale.y) != tinyxml2::XML_SUCCESS)
			{
				std::cout << "error reading scale" << std::endl;
			}
			if (pElement->FirstChildElement("scale")->QueryFloatAttribute("z", &scale.z) != tinyxml2::XML_SUCCESS)
			{
				std::cout << "error reading scale" << std::endl;
			}
		}else
		{
			std::cout << "error reading scale" << std::endl;
		}
	}


	void Transform::Destroy()
	{
	}

	const glm::vec3& Transform::GetPosition() const
	{
		return position;
	}

	const glm::vec3& Transform::GetRotation() const
	{
		return rotation;
	}

	const glm::vec3& Transform::GetScale() const
	{
		return scale;
	}

	void Transform::SetPosition(const glm::vec3& position)
	{
		this->position = position;
	}

	void Transform::SetRotation(const glm::vec3& rotation)
	{
		this->rotation = rotation;
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		this->scale = scale;
	}

	void Transform::SetPosition(const float x, const float y, const float z)
	{
		this->position.x = x;
		this->position.y = y;
		this->position.z = z;
	}

	void Transform::SetRotation(const float x, const float y, const float z)
	{
		this->rotation.x = x;
		this->rotation.y = y;
		this->rotation.z = z;
	}

	void Transform::SetScale(const float x, const float y, const float z)
	{
		this->scale.x = x;
		this->scale.y = y;
		this->scale.z = z;
	}

	Transform::~Transform()
	{
	}
}
