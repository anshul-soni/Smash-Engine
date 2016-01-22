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