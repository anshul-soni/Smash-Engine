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
		omega(5),
		torque(0),
		orientation(glm::quat(0,0,0,0)),
		damping(0.99f),
		angularDamping(0.99f),
		collider(nullptr),
		isStatic(false)
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
			inverseMass = 1 / mass;
		}else
		{
			std::cout << "error reading inverseMass" << std::endl;
		}
		if (pElement->FirstChildElement("collider") != nullptr)
		{
			std::string colliderType = pElement->FirstChildElement("collider")->GetText();
			if(colliderType == "sphere")
			{
				collider = new SphereCollider(this, 0.5f);
			}
			if (colliderType == "box")
			{
				collider = new BoxCollider(this, glm::vec3(1));
			}
		}
		else
		{
			std::cout << "error reading collider" << std::endl;
		}
		if (pElement->FirstChildElement("isstatic") != nullptr)
		{
			pElement->FirstChildElement("isstatic")->QueryBoolText(&isStatic);
		}
		else
		{
			std::cout << "error reading collider" << std::endl;
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

	void Body::SetCollider(Collider* collider)
	{
		this->collider = collider;
	}

	Collider* Body::GetCollider() const
	{
		return collider;
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

	void Body::CalculateAuxilaryVariables(Transform* transform,float dt)
	{
		if(isStatic)
		{
			glm::vec3 rotation = transform->GetRotation();
			orientation = glm::quat(rotation);
			rotationMatrix = glm::toMat3(glm::normalize(orientation));
			this->position = transform->GetPosition();
			return;
		}
		auto acceleration = force * inverseMass + GRAVITY;

		orientation = glm::normalize(orientation);
		rotationMatrix = glm::toMat3(orientation);
		inverseInertialTensor = glm::transpose(rotationMatrix)*inverseInertiaTensorLocal*rotationMatrix;
		auto alpha = inverseInertialTensor*torque;

		velocity += acceleration * dt;
		omega += alpha * dt;

		auto position = transform->GetPosition();
		position += velocity * dt;
		transform->SetPosition(position);
		this->position = position;
		auto dq = glm::quat(0, omega) * dt;
		orientation += dq * orientation * 0.5f;

		velocity *= damping;
		omega *= angularDamping;

		transform->SetRotationMatrix(glm::toMat4(orientation));
		force = glm::vec3(0, 0, 0);
		torque = glm::vec3(0, 0, 0);
	}

	const glm::vec3& Body::GetPosition() const
	{
		return position;
	}

	const glm::mat3& Body::GetRotationMatrix() const
	{
		return rotationMatrix;
	}

	glm::vec3 Body::LocalToWorld(const glm::vec3& lPoint)const
	{
		glm::vec3 com = GetPosition();
		return (rotationMatrix*lPoint+com);
	}

	glm::vec3 Body::WorldToLocal(const glm::vec3& wPoint)const 
	{
		glm::vec3 com = GetPosition();
		return ((glm::transpose(rotationMatrix))*(wPoint - com));
	}

	glm::vec3 Body::LocalToWorldDir(const glm::vec3& lDir)const 
	{
		return (rotationMatrix * lDir);
	}

	glm::vec3 Body::WorldToLocalDir(const glm::vec3& wDir)const
	{
		return (glm::transpose(rotationMatrix) * wDir);
	}

	void Body::SetStatic(bool isStatic)
	{
		this->isStatic = isStatic;
	}
}
