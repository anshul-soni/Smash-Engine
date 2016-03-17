////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Texture.h															 
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
#pragma once

namespace SmashEngine
{
	class Texture {
	public:
		Texture();
		Texture(const std::string& path);
		void BindTexture() const;
		void Unbind() const;
		int GetWidth() const;
		int GetHeight() const;
		int GetTextureID() const;
		bool LoadTexture2D(const std::string& path);
		std::string& GetPath();
		~Texture();
	private:
		GLuint id;

		int width;
		int height;
		int channels;
		std::string path;
	};
}