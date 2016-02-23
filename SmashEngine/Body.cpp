#include "stdafx.h"
#include "Body.h"

#define GRAVITY glm::vec3(0.0f,-10.0f,0.0f)
namespace SmashEngine
{
	Body::Body() :
		type(TYPE_Body),
		inverseMass(0.0f),
		velocity(glm::vec3(0)),
		force(glm::vec3(0)),
		inertiaTensorLocal(0),
		inverseInertiaTensorLocal(0),
		inverseInertialTensor(0),
		omega(0),
		torque(0),
		orientation(glm::quat(0,0,0,0)),
		damping(0.99f),
		angularDamping(0.99f)
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

	void Body::CalculateAuxilaryVariables(Transform& transform,float dt)
	{
		auto acceleration = force * inverseMass + GRAVITY;

		orientation = glm::normalize(orientation);
		auto rotationMatrix = glm::toMat3(orientation);
		inverseInertialTensor = glm::transpose(rotationMatrix)*inverseInertiaTensorLocal*rotationMatrix;
		auto alpha = inverseInertialTensor*torque;

		velocity += acceleration * dt;
		omega += alpha * dt;

		auto position = transform.GetPosition();
		position += velocity * dt;
		transform.SetPosition(position);

		auto dq = glm::quat(0, omega) * dt;
		orientation += dq * orientation * 0.5f;

		velocity *= damping;
		omega *= angularDamping;

		transform.SetRotationMatrix(glm::toMat4(orientation));

		force = glm::vec3(0, 0, 0);
		torque = glm::vec3(0, 0, 0);
	}
}
