#include "stdafx.h"
#include "Model.h"

namespace SmashEngine
{

	std::string GetDirectoryPath(std::string filePath)
	{
		std::string directory = "";
		for (int i = (int)filePath.size(); i >= 0; i--)
		{
			if (filePath[i] == '\\' || filePath[i] == '/')
			{
				directory = filePath.substr(0, i + 1);
				break;
			}
		}
		return directory;
	}
	Model::Model(const char* filePath) :key(filePath), bLoaded(false)
	{
	}

	bool Model::LoadModel()
	{
		if (vboModelData.GetBufferID() == 0)
		{
			vboModelData.CreateVBO();
			textures.reserve(50);
		}
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(key, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
		if (!scene)
		{
			//error reading file
			return false;
		}
		const int vertexTotalSize = sizeof(aiVector3D) * 2 + sizeof(aiVector2D);
		int totalVertices = 0;
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];
			int meshFaces = mesh->mNumFaces;
			materialIndices.push_back(mesh->mMaterialIndex);
			int sizeBefore = vboModelData.GetCurrentSize();
			meshStartIndices.push_back(sizeBefore / vertexTotalSize);
			for (int j = 0; j < meshFaces; j++)
			{
				const aiFace& face = mesh->mFaces[j];
				for (int k = 0; k < 3; k++)
				{
					aiVector3D pos = mesh->mVertices[face.mIndices[k]];
					aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[k]];
					aiVector3D normal = mesh->HasNormals() ? mesh->mNormals[face.mIndices[k]] : aiVector3D(1.0f, 1.0f, 1.0f);
					vboModelData.AddData(&pos, sizeof(aiVector3D));
					vboModelData.AddData(&uv, sizeof(aiVector2D));
					vboModelData.AddData(&normal, sizeof(aiVector3D));
				}
			}
			int meshVertices = mesh->mNumVertices;
			totalVertices += meshVertices;
			meshSizes.push_back((vboModelData.GetCurrentSize() - sizeBefore) / vertexTotalSize);
		}
		numMaterial = scene->mNumMaterials;
		std::vector<int> materialRemap(numMaterial);
		for (int i = 0; i < numMaterial; i++)
		{
			const aiMaterial* material = scene->mMaterials[i];
			int a = 5;
			int texIndex = 0;
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, texIndex, &path) == AI_SUCCESS)
			{
				std::string dir = GetDirectoryPath(filePath);
				std::string textureName = path.data;
				std::string fullPath = dir + textureName;
				int texFound = -1;
				for (int j = 0; j < (int)textures.size(); j++)
				{
					if (fullPath == textures[j].GetPath())
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
					materialRemap[i] = (int)textures.size();
					textures.push_back(AssetManager::GetInstance().GetTextureID(fullPath));
					std::cout << "texture loaded" << fullPath << std::endl;
				}
			}
		}
		for (int i = 0; i < (int)meshSizes.size(); i++)
		{
			int oldIndex = materialIndices[i];
			materialIndices[i] = materialRemap[oldIndex];
		}
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		vboModelData.BindVBO();
		vboModelData.UploadDataToGPU(GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(aiVector3D) + sizeof(aiVector2D), 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(aiVector3D) + sizeof(aiVector2D), (void*)sizeof(aiVector3D));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(aiVector3D) + sizeof(aiVector2D), (void*)(sizeof(aiVector3D) + sizeof(aiVector2D)));
		return bLoaded = true;
	}

	void Model::Render(float dt)
	{
	}

	Model::~Model()
	{
	}
}