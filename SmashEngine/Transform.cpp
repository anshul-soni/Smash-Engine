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
	}

	void Transform::Update(float dt)
	{
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
