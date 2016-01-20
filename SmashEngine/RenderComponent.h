#pragma once
#include "Component.h"

namespace SmashEngine
{
	class RenderComponent:public Component
	{
	public:
		RenderComponent();
		void Initialize()override;
		void Deserialize(tinyxml2::XMLElement* pElement)override;
		void Update(float dt)override;
		void Destroy()override;
		~RenderComponent();
	private:

	};
}