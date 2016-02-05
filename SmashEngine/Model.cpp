#include "stdafx.h"
#include "Model.h"
#include "TextureManager.h"
#include "ResourcePath.h"
#include "ShaderManager.h"

namespace SmashEngine
{

	std::string GetDirectoryPath(std::string filePath)
	{
		std::string directory = "";
		for (auto i = static_cast<int>(filePath.size()); i >= 0; i--)
		{
			if (filePath[i] == '\\' || filePath[i] == '/')
			{
				directory = filePath.substr(0, i + 1);
				break;
			}
		}
		return directory;
	}
	Model::Model(const std::string& filePath) :
		key(filePath), 
		bLoaded(false), 
		VAO(0), 
		numMaterial(0)
	{
		vboModelData = new VertexBufferObject();
		LoadModel();
	}

	bool Model::LoadModel()
	{
		if (vboModelData->GetBufferID() == 0)
		{
			vboModelData->CreateVBO();
			textures.reserve(50);
		}
		Assimp::Importer importer;
		auto filePath = ResourcePath::GetInstance().GetPath(RESOURCE_Model, key);
		auto scene = importer.ReadFile(filePath.c_str(), aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
		if (!scene)
		{
			std::cout << "error reading model file " << filePath << std::endl;
			return false;
		}
		auto vertexTotalSize = sizeof(aiVector3D) * 2 + sizeof(aiVector2D);
		auto totalVertices = 0;
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			auto mesh = scene->mMeshes[i];
			auto meshFaces = mesh->mNumFaces;
			materialIndices.push_back(mesh->mMaterialIndex);
			auto sizeBefore = vboModelData->GetCurrentSize();
			meshStartIndices.push_back(sizeBefore / vertexTotalSize);
			for (unsigned int j = 0; j < meshFaces; j++)
			{
				auto face = mesh->mFaces[j];
				for (auto k = 0; k < 3; k++)
				{
					auto pos = mesh->mVertices[face.mIndices[k]];
					auto uv = mesh->mTextureCoords[0][face.mIndices[k]];
					auto normal = mesh->HasNormals() ? mesh->mNormals[face.mIndices[k]] : aiVector3D(1.0f, 1.0f, 1.0f);
					vboModelData->AddData(&pos, sizeof(aiVector3D));
					vboModelData->AddData(&uv, sizeof(aiVector2D));
					vboModelData->AddData(&normal, sizeof(aiVector3D));
				}
			}
			auto meshVertices = mesh->mNumVertices;
			totalVertices += meshVertices;
			meshSizes.push_back((vboModelData->GetCurrentSize() - sizeBefore) / vertexTotalSize);
		}
		numMaterial = scene->mNumMaterials;
		std::vector<int> materialRemap(numMaterial);
		for (auto i = 0; i < numMaterial; i++)
		{
			const aiMaterial* material = scene->mMaterials[i];
			auto texIndex = 0;
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, texIndex, &path) == AI_SUCCESS)
			{
				auto dir = GetDirectoryPath(ResourcePath::GetInstance().GetPath(RESOURCE_Model, key).c_str());
				auto textureName = path.data;
				auto fullPath = dir + textureName;
				auto texFound = -1;
				for (auto j = 0; j < static_cast<int>(textures.size()); j++)
				{
					if (fullPath == textures[j]->GetPath())
					{
						texFound = j;
						break;
					}
				}
				if (texFound != -1)
				{
					materialRemap[i] = texFound;
				}
				else
				{
					Texture newTex;
					newTex.LoadTexture2D(fullPath);
					materialRemap[i] = static_cast<int>(textures.size());
					textures.push_back(TextureManager::GetInstance().GetTexture(fullPath));
					std::cout << "texture loaded" << fullPath << std::endl;
				}
			}
		}
		for (auto i = 0; i < static_cast<int>(meshSizes.size()); i++)
		{
			auto oldIndex = materialIndices[i];
			materialIndices[i] = materialRemap[oldIndex];
		}
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		vboModelData->BindVBO();
		vboModelData->UploadDataToGPU(GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(aiVector3D) + sizeof(aiVector2D), 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(aiVector3D) + sizeof(aiVector2D), (void*)(sizeof(aiVector3D)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(aiVector3D) + sizeof(aiVector2D), (void*)(sizeof(aiVector3D) + sizeof(aiVector2D)));
		return bLoaded = true;
	}

	void Model::Render()
	{
		if (!bLoaded)
			return;
		auto numMeshes = static_cast<int>(meshSizes.size());
		for (auto i = 0; i < numMeshes; i++)
		{
			auto matIndex = materialIndices[i];
			if (textures.size()>0)
				textures[matIndex]->BindTexture();
			glDrawArrays(GL_TRIANGLES, meshStartIndices[i], meshSizes[i]);
		}
	}

	void Model::BindVAO()const
	{
		glBindVertexArray(VAO);
	}

	Shader& Model::GetShader()
	{
		return *shader;
	}

	void Model::SetShader(const std::string& shader)
	{
		this->shader = ShaderManager::GetInstance().GetShader(shader);
	}

	Model::~Model()
	{
	}
}
