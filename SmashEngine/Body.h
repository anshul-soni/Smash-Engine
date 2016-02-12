#pragma once
#include "Component.h"

namespace SmashEngine
{
	enum Collider
	{
		COLLIDER_Cube = 0,
		COLLIDER_Sphere
	};
	class Body:public Component
	{
	public:
		Body();
		void Initialize()override;
		void Deserialize(tinyxml2::XMLElement* pElement)override;
		void Destroy()override;
		void SetVelocity(const glm::vec3& velocity);
		void SetAngularVelocity(const glm::vec3& omega);
		void SetForce(const glm::vec3& force);
		void SetTorque(const glm::vec3& torque);
		void SetCollider(const std::string& colliderType);
		void SetAngularMomentum(const glm::vec3& angularMomentum);
		void SetLinearMomentum(const glm::vec3& linearMomentum);
		const glm::vec3& GetVelocity()const;
		const glm::vec3& GetForce()const;
		float GetInverseMass()const;
	private:
		const ComponentType type;
		//constant quantities
		float inverseMass;
		glm::mat3 inertiaTensorLocal;
		glm::mat3 inverseInertiaTensorLocal;
		Collider collider;

		//State variables
		//Rotation is stored in transform
		glm::vec3 linearMomentum;
		glm::vec3 angularMomentum;

		//Derived quantities(auxilary variables)
		glm::mat3 inverseInertialTensor;
		glm::vec3 velocity;
		glm::vec3 omega;

		//computed quantitites
		glm::vec3 force;
		glm::vec3 torque;
	};
}
