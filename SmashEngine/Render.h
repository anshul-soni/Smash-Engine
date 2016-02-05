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
		void Draw();
		void Destroy()override;
		~Render();
	private:
		Drawable* drawableComponent;
	};
}
