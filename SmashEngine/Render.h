#pragma once
#include "Component.h"

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
		~Render();
	private:

	};
}