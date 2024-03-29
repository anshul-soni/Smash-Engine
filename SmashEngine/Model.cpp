////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Model.cpp															 
/// @date 2/5/2016  11:27 PM			 
/// @author Anshul Soni <soni.anshul93@gmail.com>								 
///																				 
/// As a condition of your accessing this Engine, you agree to be bound 		 
///	by the following terms and conditions: 										 
/// The software was created by Anshul Soni, and all copyright and other 		 
///	rights in such is owned by Anshul Soni. While you are allowed to access,  	 
/// download and use the code for non-commercial, home use you hereby expressly  
/// agree that you will not otherwise copy, distribute, modify, the code. 		 
////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Model.h"
#include "TextureManager.h"
#include "ResourcePath.h"

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
		numMaterial(0)
	{
		Init();
	}

	bool Model::Init()
	{
		if (vbo->GetBufferID() == 0)
		{
			vbo->CreateVBO();
			textures.reserve(50);
		}
		Assimp::Importer importer;
		std::string filePath = ResourcePath::GetInstance().GetPath(RESOURCE_Model, key);
		const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
		if (!scene)
		{
			std::cout << "error reading model file " << filePath << std::endl;
			return false;
		}
		unsigned int vertexTotalSize = sizeof(aiVector3D) * 2 + sizeof(aiVector2D);
		int totalVertices = 0;
		for (auto i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];
			unsigned int meshFaces = mesh->mNumFaces;
			materialIndices.push_back(mesh->mMaterialIndex);
			int sizeBefore = vbo->GetCurrentSize();
			meshStartIndices.push_back(sizeBefore / vertexTotalSize);
			for (auto j = 0; j < meshFaces; j++)
			{
				aiFace face = mesh->mFaces[j];
				for (auto k = 0; k < 3; k++)
				{
					aiVector3D pos = mesh->mVertices[face.mIndices[k]];
					aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[k]];
					aiVector3D normal = mesh->HasNormals() ? mesh->mNormals[face.mIndices[k]] : aiVector3D(1.0f, 1.0f, 1.0f);
					vbo->AddData(&pos, sizeof(aiVector3D));
					vbo->AddData(&uv, sizeof(aiVector2D));
					vbo->AddData(&normal, sizeof(aiVector3D));
				}
			}
			unsigned int meshVertices = mesh->mNumVertices;
			totalVertices += meshVertices;
			meshSizes.push_back((vbo->GetCurrentSize() - sizeBefore) / vertexTotalSize);
		}
		numMaterial = scene->mNumMaterials;
		std::vector<int> materialRemap(numMaterial);
		for (auto i = 0; i < numMaterial; i++)
		{
			const aiMaterial* material = scene->mMaterials[i];
			int texIndex = 0;
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, texIndex, &path) == AI_SUCCESS)
			{
				std::string dir = GetDirectoryPath(ResourcePath::GetInstance().GetPath(RESOURCE_Model, key).c_str());
				char* textureName = path.data;
				std::string fullPath = dir + textureName;
				int texFound = -1;
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
			int oldIndex = materialIndices[i];
			materialIndices[i] = materialRemap[oldIndex];
		}
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		vbo->BindVBO();
		vbo->UploadDataToGPU(GL_DYNAMIC_DRAW);
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
		size_t numMeshes = static_cast<int>(meshSizes.size());
		for (unsigned int i = 0; i < numMeshes; i++)
		{
			int matIndex = materialIndices[i];
			if (textures.size()>0)
				textures[matIndex]->BindTexture();
			glDrawArrays(GL_TRIANGLES, meshStartIndices[i], meshSizes[i]);
		}
		//glEnable(GL_PROGRAM_POINT_SIZE);
		//glDrawArrays(GL_POINTS, 0, meshSizes[i]);
	}

	Model::~Model()
	{
	}
}
