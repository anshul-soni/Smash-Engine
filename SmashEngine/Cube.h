#pragma once
#include "Primitive.h"
#include "VertexBufferObject.h"

namespace SmashEngine
{
	class Cube :public Primitive
	{
	public:
									Cube();
		bool						Init()override;
		void						Render()override;
									~Cube();
	private:
		unsigned int				elementBuffer;
		std::vector<unsigned int>	indices;
	};
}