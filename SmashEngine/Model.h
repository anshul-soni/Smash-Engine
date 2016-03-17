////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Model.h															 
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
