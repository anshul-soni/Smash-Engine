#pragma once
#include "Primitive.h"
#include "VertexBufferObject.h"

namespace SmashEngine
{
	class Wireframe :public Primitive
	{
	public:
		Wireframe();
		bool					Init()override;
		void					Render()override;
		~Wireframe();
	private:
		int						size= 50;
	};
}