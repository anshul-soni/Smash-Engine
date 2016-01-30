#pragma once
#include "VertexBufferObject.h"
#include "Texture.h"

namespace SmashEngine
{
	class Model
	{
	public:
		explicit Model(const std::string& filePath);
		bool LoadModel();
		void Render();
		void BindVAO()const;
		~Model();
	private:
		const std::string key;
		bool bLoaded;
		VertexBufferObject* vboModelData;
		unsigned int VAO;
		std::vector<Texture*> textures;
		std::vector<int> meshStartIndices;
		std::vector<int> meshSizes;
		std::vector<int> materialIndices;
		int numMaterial;
		Model() = delete;
	};
}