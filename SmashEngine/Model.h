#pragma once
#include "VertexBufferObject.h"
#include "Texture.h"
#include "Drawable.h"

namespace SmashEngine
{
	class Model:public Drawable
	{
	public:
		explicit Model(const std::string& filePath);
		bool LoadModel()override;
		void Render()override;
		void BindVAO()const override;
		Shader& GetShader()override;
		void SetTexture(const std::string& filePath);
		void SetShader(const std::string& shader)override;
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
		Shader* shader;
		Model() = delete;
	};
}
