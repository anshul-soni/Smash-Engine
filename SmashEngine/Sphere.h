#pragma once
#include "Primitive.h"
#include "VertexBufferObject.h"

namespace SmashEngine
{
	class Sphere :public Primitive
	{
	public:
		Sphere();
		bool						Init()override;
		void						Render()override;
		~Sphere();
	private:
		int							latitude = 20;
		int							longitude = 20;
	};
}
