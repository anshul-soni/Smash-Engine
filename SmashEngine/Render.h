#pragma once
#include "Component.h"
#include "Shader.h"
#include "Model.h"

namespace SmashEngine
{
	class Render:public Component
	{
	public:
		Render();
		void Initialize()override;
		void Deserialize(tinyxml2::XMLElement* pElement)override;
		void Update(float dt)override;
		void Destroy()override;
		void SetShader(const std::string& key);
		~Render();
	private:
		Shader* shader;
		Model* model;
	};
}
