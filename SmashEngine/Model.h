#pragma once
#include "VertexBufferObject.h"
#include "Texture.h"

namespace SmashEngine
{
	class Model
	{
	public:
		explicit Model(const char* filePath);
		bool LoadModel();
		void Render(float dt);
		~Model();
	private:
		const char* key;
		bool bLoaded;
		VertexBufferObject vboModelData;
		unsigned int VAO;
		std::vector<Texture*> textures;
		std::vector<int> meshStartIndices;
		std::vector<int> meshSizes;
		std::vector<int> materialIndices;
		int numMaterial;
		Model() = delete;
		Model operator=(Model&) = delete;
		Model(Model&) = delete;
	};
}