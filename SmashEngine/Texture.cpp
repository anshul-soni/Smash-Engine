////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Texture.cpp															 
/// @date 1/23/2016  2:49 PM			 
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
#include "Texture.h"

namespace SmashEngine
{
	Texture::Texture() :
		id(0),
		width(0),
		height(0),
		channels(0)
	{
	};

	Texture::Texture(const std::string& path)
	{
		LoadTexture2D(path);
	};

	Texture::~Texture() {
		glDeleteTextures(1, &id);
	}

	bool Texture::LoadTexture2D(const std::string& path){
		// Get the bytes for the texture.
		auto image = SOIL_load_image(
			path.c_str(),
			&width,
			&height,
			&channels,
			SOIL_LOAD_RGBA);
		if (image == nullptr)
			return false;
		GLuint id;
		// Create OpenGL texture and load bytes into it.
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Clean image data.
		SOIL_free_image_data(image);
		// Return new texture.
		this->id = id;
		this->path = path;
		return true;
	}

	void Texture::BindTexture() const {
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void Texture::Unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	int Texture::GetWidth() const {
		return width;
	}

	int Texture::GetHeight() const {
		return height;
	}

	int Texture::GetTextureID() const {
		return id;
	}
	std::string& Texture::GetPath()
	{
		return this->path;
	}
}