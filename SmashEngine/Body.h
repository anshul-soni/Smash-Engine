#pragma once
#include "Component.h"
#include "Transform.h"
#include "Collider.h"

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
		void SetCollider(Collider* collider);
		Collider* GetCollider()const;
		const glm::vec3& GetVelocity()const;
		const glm::vec3& GetForce()const;
		const glm::quat& GetOrientation()const;
		float GetInverseMass()const;
		void CalculateAuxilaryVariables(Transform* transform,float dt);
		const glm::vec3& GetPosition()const;
		const glm::mat3& GetRotationMatrix()const;
		glm::vec3 LocalToWorld(const glm::vec3& bodyPoint)const;
		glm::vec3 WorldToLocal(const glm::vec3& wPoint)const;
		glm::vec3 LocalToWorldDir(const glm::vec3& dir)const;
		glm::vec3 WorldToLocalDir(const glm::vec3& dir)const;
		void SetStatic(bool isStatic);
	private:
		const ComponentType type;
		//constant quantities
		float inverseMass;
		glm::mat3 inertiaTensorLocal;
		glm::mat3 inverseInertiaTensorLocal;
		Collider* collider;

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

		glm::quat orientation;

		float damping;
		float angularDamping;

		//attributes to store for collision
		glm::vec3 position;
		glm::mat3 rotationMatrix;

		bool isStatic;
	};
}
