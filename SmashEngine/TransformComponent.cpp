#include "stdafx.h"
#include "TransformComponent.h"

namespace SmashEngine
{
	TransformComponent::TransformComponent() :position(glm::vec3(0)),
		rotation(glm::vec3(0)),
		scale(glm::vec3(1))
	{
	}

	void TransformComponent::Initialize()
	{
	}

	void TransformComponent::Deserialize(tinyxml2::XMLElement* pElement)
	{
	}

	void TransformComponent::Update(float dt)
	{
	}

	void TransformComponent::Destroy()
	{
	}

	const glm::vec3& TransformComponent::GetPosition() const
	{
		return position;
	}

	const glm::vec3& TransformComponent::GetRotation() const
	{
		return rotation;
	}

	const glm::vec3& TransformComponent::GetScale() const
	{
		return scale;
	}

	void TransformComponent::SetPosition(const glm::vec3& position)
	{
		this->position = position;
	}

	void TransformComponent::SetRotation(const glm::vec3& rotation)
	{
		this->rotation = rotation;
	}

	void TransformComponent::SetScale(const glm::vec3& scale)
	{
		this->scale = scale;
	}

	void TransformComponent::SetPosition(const float x, const float y, const float z)
	{
		this->position.x = x;
		this->position.y = y;
		this->position.z = z;
	}

	void TransformComponent::SetRotation(const float x, const float y, const float z)
	{
		this->rotation.x = x;
		this->rotation.y = y;
		this->rotation.z = z;
	}

	void TransformComponent::SetScale(const float x, const float y, const float z)
	{
		this->scale.x = x;
		this->scale.y = y;
		this->scale.z = z;
	}

	TransformComponent::~TransformComponent()
	{
	}
}
