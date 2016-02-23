#pragma once
#include "Component.h"

namespace SmashEngine
{
	class Transform:public Component
	{
	public:
		Transform();
		void Initialize()override;
		void Deserialize(tinyxml2::XMLElement* pElement)override;
		void Destroy()override;

		const glm::vec3& GetPosition()const;
		const glm::vec3& GetRotation()const;
		const glm::vec3& GetScale()const;
		const glm::mat4& GetRotationMatrix()const;

		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);
		void SetScale(const glm::vec3& scale);
		void SetRotationMatrix(const glm::mat4& rotation);

		void SetPosition(const float x, const float y, const float z);
		void SetRotation(const float x, const float y, const float z);
		void SetScale(const float x, const float y, const float z);

		~Transform();
	private:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::mat4 rotationMatrix;
	};
}