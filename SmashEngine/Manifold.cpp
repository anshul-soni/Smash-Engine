
#include "stdafx.h"
#include "Manifold.h"

namespace SmashEngine
{
	Manifold::Manifold(Body* A, Body* B)
		: A(A),
		B(B)
	{

	}

	void Manifold::SetBodyA(Body* b)
	{
		A = b;
	}

	Body* Manifold::GetBodyA() const
	{
		return A;
	}

	void Manifold::SetBodyB(Body* b)
	{
		B = b;
	}

	Body* Manifold::GetBodyB() const
	{
		return B;
	}

	void Manifold::SetContact(const glm::vec3& c)
	{
		contact = c;
	}

	glm::vec3 Manifold::GetContact() const
	{
		return contact;
	}

	void Manifold::SetNormal(const glm::vec3& n)
	{
		normal = n;
	}

	glm::vec3 Manifold::GetNormal() const
	{
		return normal;
	}

	void Manifold::SetContactData(const glm::vec3& c, const glm::vec3& n, const float p)
	{
		contact = c;
		normal = n;

		// calculate the basis matrix for this contact
		glm::vec3 cX, cY, cZ;
		glm::vec3 wY(0, 1, 0);
		glm::vec3 wX(1, 0, 0);
		glm::mat3 contactBasis;
		cX = normal;
		if (glm::dot(normal, wY) > 0.01f)
		{
			cZ = glm::cross(cX, wY);
		}
		else
		{
			cZ = glm::cross(cX, wX);
		}
		cY = glm::cross(cZ, cX);

		contactBasis[0] = cX;
		contactBasis[1] = cY;
		contactBasis[2] = cZ;
	}
}