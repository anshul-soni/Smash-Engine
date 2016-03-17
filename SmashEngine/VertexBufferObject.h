////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file VertexBufferObject.h															 
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
	class VertexBufferObject
	{
	public:
		void CreateVBO(int size = 0);
		void DeleteVBO();

		void* MapBufferToMemory(int uh)const;
		void* MapSubBufferToMemory(int uh, unsigned int offset, unsigned int length)const;
		void UnMapBuffer()const;

		void BindVBO(int bufferType = GL_ARRAY_BUFFER);
		void UploadDataToGPU(int uh);

		void AddData(void* ptrData, unsigned int uiDataSize);

		void* GetDataPointer();
		unsigned int GetBufferID()const;
		int GetCurrentSize()const;

		VertexBufferObject();
	private:
		unsigned int buffer;
		int size;
		int currentSize;
		int bufferType;
		std::vector<unsigned char> data;
		bool dataUploaded;
	};
}