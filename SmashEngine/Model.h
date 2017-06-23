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
#include "Texture.h"
#include "Primitive.h"

namespace SmashEngine
{
	class Model:public Primitive
	{
	public:
		explicit Model(const std::string& filePath);
		bool Init()override;
		void Render()override;
		~Model();
	private:
		const std::string key;
		std::vector<Texture*> textures;
		std::vector<int> meshStartIndices;
		std::vector<int> meshSizes;
		std::vector<int> materialIndices;
		int numMaterial;
		Model() = delete;
	};
}
