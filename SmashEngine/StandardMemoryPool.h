#pragma once
#include "MemoryPool.h"

namespace SmashEngine
{
	class StandardMemoryPool :public MemoryPool
	{
	public:
		StandardMemoryPool(unsigned int size, bool boundCheck);
		~StandardMemoryPool();

		void*			Allocate(unsigned int size);
		void			Free(void* ptr);
	private:
		unsigned char*						m_poolMemory;
		static const unsigned char			s_minFreeBlockSize = 16;

		class MemoryChunk
		{
		public:
			MemoryChunk(unsigned int dataSize) :m_pNext(nullptr), m_pPrev(nullptr), m_iDataSize(dataSize), m_bIsFree(true) {}
			void			Write(void* destination) { std::memcpy(destination, this, sizeof(MemoryChunk)); }
			void			Read(void* source) { std::memcpy(this, source, sizeof(MemoryChunk)); }
			MemoryChunk*	m_pNext;
			MemoryChunk*	m_pPrev;
			unsigned int	m_iDataSize;
			bool			m_bIsFree;
		};
	};
}
