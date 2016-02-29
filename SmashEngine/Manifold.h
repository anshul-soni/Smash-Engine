#pragma once
#include "Body.h"

namespace SmashEngine
{
	class Manifold
	{
	public:
		Manifold(Body* A, Body* B);
		void SetBodyA(Body* b);
		Body* GetBodyA() const;
		void SetBodyB(Body* b);
		Body* GetBodyB() const;
		void SetContact(const glm::vec3& c);
		glm::vec3 GetContact() const;
		void SetNormal(const glm::vec3& n);
		glm::vec3 GetNormal() const;
		void SetContactData(const glm::vec3& c, const glm::vec3& n, const float p);
	protected:
		Body* A;
		Body* B;
		glm::vec3 contact;
		glm::vec3 normal;
	};
}
