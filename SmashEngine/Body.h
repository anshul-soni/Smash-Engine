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
		float GetMass()const;
	private:
		const ComponentType type;
		float mass;
		glm::vec3 velocity;
		glm::vec3 force;
	};
}
