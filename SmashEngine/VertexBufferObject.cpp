////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file VertexBufferObject.cpp															 
/// @date 1/28/2016  8:45 PM			 
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
#include "VertexBufferObject.h"

namespace SmashEngine
{

	VertexBufferObject::VertexBufferObject()
	{
		dataUploaded = false;
		buffer = 0;
	}

	void VertexBufferObject::CreateVBO(int size)
	{
		glGenBuffers(1, &buffer);
		data.reserve(size);
		this->size = size;
		currentSize = 0;
	}

	void VertexBufferObject::DeleteVBO()
	{
		glDeleteBuffers(1, &buffer);
		dataUploaded = false;
		data.clear();
	}

	void* VertexBufferObject::MapBufferToMemory(int uh)const
	{
		if (!dataUploaded)
			return nullptr;
		auto res = glMapBuffer(bufferType, uh);
		return res;
	}

	void* VertexBufferObject::MapSubBufferToMemory(int uh, unsigned int offset, unsigned int length)const
	{
		if (!dataUploaded)
			return nullptr;
		auto res = glMapBufferRange(bufferType, offset, length, uh);
		return res;
	}
	void VertexBufferObject::UnMapBuffer()const
	{
		glUnmapBuffer(bufferType);
	}

	void VertexBufferObject::BindVBO(int bufferType)
	{
		this->bufferType = bufferType;
		glBindBuffer(bufferType, buffer);
	}

	void VertexBufferObject::UploadDataToGPU(int uh)
	{
		glBufferData(bufferType, data.size(), &data[0], uh);
		dataUploaded = true;
		data.clear();
	}

	void VertexBufferObject::AddData(void* data, unsigned int datasize)
	{
		this->data.insert(this->data.end(), static_cast<unsigned char*>(data), static_cast<unsigned char*>(data) + datasize);
		currentSize += datasize;
	}

	void* VertexBufferObject::GetDataPointer()
	{
		if (dataUploaded)return nullptr;
		return reinterpret_cast<void*>(data[0]);
	}

	unsigned int VertexBufferObject::GetBufferID()const
	{
		return buffer;
	}

	int VertexBufferObject::GetCurrentSize()const
	{
		return currentSize;
	}
}