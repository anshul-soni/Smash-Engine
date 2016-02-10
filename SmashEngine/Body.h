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
		void SetForce(const glm::vec3& force);
		void SetCollider(const std::string& colliderType);
		const glm::vec3& GetVelocity()const;
		const glm::vec3& GetForce()const;
		float GetMass()const;
	private:
		const ComponentType type;
		Collider collider;
		float inverseMass;
		glm::vec3 velocity;
		glm::vec3 force;
		glm::mat3 intertiaTensor;
		glm::mat3 inverseIntertiaTensor;
	};
}
