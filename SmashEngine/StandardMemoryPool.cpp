#include "stdafx.h"
#include "StandardMemoryPool.h"

namespace SmashEngine
{
	StandardMemoryPool::StandardMemoryPool(unsigned int dataSize, bool boundCheck)
	{
		if (boundCheck)
		{
			m_boundsCheck = true;
		}
		m_poolMemory = ::new unsigned char[dataSize];

		m_iFreePoolSize = dataSize - sizeof(MemoryChunk);
		m_iTotalPoolSize = dataSize;

		if (m_trashOnCreation)
			memset(m_poolMemory, m_trashOnCreation, dataSize);

		if (m_boundsCheck)
		{
			m_iFreePoolSize -= s_BoundsCheckSize * 2;

			MemoryChunk freeChunk(dataSize - sizeof(MemoryChunk) - 2 * s_BoundsCheckSize);
			freeChunk.Write(m_poolMemory + s_BoundsCheckSize);
			std::memcpy(m_poolMemory, s_StartBound, s_BoundsCheckSize);
			std::memcpy(m_poolMemory+dataSize - s_BoundsCheckSize,s_EndBound,s_BoundsCheckSize);
		}
		else
		{
			MemoryChunk freeChunk(dataSize - sizeof(MemoryChunk));
			freeChunk.Write(m_poolMemory);
		}
	}

	StandardMemoryPool::~StandardMemoryPool()
	{
		::delete[] m_poolMemory;
	}

	void* StandardMemoryPool::Allocate(unsigned int size)
	{
		unsigned int requiredSize = size + sizeof(MemoryChunk);

		if (m_boundsCheck)
		{
			requiredSize += s_BoundsCheckSize * 2;
		}

		MemoryChunk* block = (MemoryChunk*)(m_boundsCheck == 1 ? m_poolMemory + s_BoundsCheckSize : m_poolMemory);

		while (block)
		{
			if (block->m_bIsFree && block->m_iDataSize >= requiredSize)
				break;
			block = block->m_pNext;
		}

		unsigned char* blockData = (unsigned char*)block;

		if (!block)
			return NULL;

		unsigned int freeUserDataSize = block->m_iDataSize - requiredSize;
		if (freeUserDataSize > s_minFreeBlockSize)
		{
			MemoryChunk freeBlock(freeUserDataSize);
			freeBlock.m_pNext = block->m_pNext;
			freeBlock.m_pPrev = block;
			freeBlock.Write(blockData + requiredSize);
			if (freeBlock.m_pNext)
			{
				freeBlock.m_pNext->m_pPrev = (MemoryChunk*)(blockData + requiredSize);
			}
			if (m_boundsCheck)
			{
				memcpy(blockData + requiredSize - s_BoundsCheckSize, s_StartBound, s_BoundsCheckSize);

			}
			block->m_pNext = (MemoryChunk*)(blockData + requiredSize);
			block->m_iDataSize = size;
		}

		m_iFreePoolSize -= block->m_iDataSize;

		block->m_bIsFree = false;

		if (m_boundsCheck)
		{
			memcpy(blockData - s_BoundsCheckSize, s_StartBound, s_BoundsCheckSize);
			memcpy(blockData + sizeof(MemoryChunk) + block->m_iDataSize, s_EndBound,
				s_BoundsCheckSize);
		}

		//Trash on alloc if required
		if (m_trashOnAlloc)
			memset(blockData + sizeof(MemoryChunk), s_TrashOnAllocSignature,
				block->m_iDataSize);

		return (blockData + sizeof(MemoryChunk));
	}

	void StandardMemoryPool::Free(void* ptr)
	{
		if (!ptr)
		{
			return;
		}
		MemoryChunk* block = (MemoryChunk*)(unsigned char*)ptr - sizeof(MemoryChunk);
		//assert(block->m_bIsFree == false, "This block is already free");
		if (block->m_bIsFree)
		{
			return;
		}
		unsigned int fullBlockSize = block->m_iDataSize + sizeof(MemoryChunk) + (m_boundsCheck == 1 ? s_BoundsCheckSize * 2 : 0);
		m_iFreePoolSize += block->m_iDataSize;
		MemoryChunk* headBlock = block;
		MemoryChunk* prev = block->m_pPrev;
		MemoryChunk* next = block->m_pNext;

		if (block->m_pPrev && block->m_pPrev->m_bIsFree)
		{
			headBlock = block->m_pPrev;
			prev = block->m_pPrev->m_pPrev;
			next = block->m_pNext;

			fullBlockSize += m_boundsCheck == 1 ? sizeof(MemoryChunk) + block->m_pPrev->m_iDataSize + s_BoundsCheckSize * 2 : sizeof(MemoryChunk) + block->m_pPrev->m_iDataSize;

			if (block->m_pNext)
			{
				block->m_pNext->m_pPrev = headBlock;

				if (block->m_pNext->m_bIsFree)
				{
					next = block->m_pNext->m_pNext;
					if (block->m_pNext->m_pNext)
					{
						block->m_pNext->m_pNext->m_pPrev = headBlock;

						fullBlockSize += m_boundsCheck == 1 ? sizeof(MemoryChunk) + block->m_pNext->m_iDataSize + s_BoundsCheckSize * 2 : sizeof(MemoryChunk) + block->m_pNext->m_iDataSize;
					}
				}
			}
		}
		else if (block->m_pNext && block->m_pNext->m_bIsFree)
		{
			headBlock = block;
			prev = block->m_pPrev;
			prev = block->m_pNext->m_pNext;

			fullBlockSize += m_boundsCheck == 1 ? sizeof(MemoryChunk) + block->m_pNext->m_iDataSize + s_BoundsCheckSize * 2 : sizeof(MemoryChunk) + block->m_pNext->m_iDataSize;
		}

		unsigned char* freeBlockStart = (unsigned char*)headBlock;
		if (m_trashOnFree)
		{
			memset(m_boundsCheck == 1 ? freeBlockStart - s_BoundsCheckSize : freeBlockStart, s_TrashOnFreeSignature, fullBlockSize);
		}

		unsigned int freeUserDataSize = fullBlockSize - sizeof(MemoryChunk);
		freeUserDataSize = (m_boundsCheck == 1) ? freeUserDataSize - 2 * s_BoundsCheckSize : freeUserDataSize;
		MemoryChunk freeBlock(freeUserDataSize);
		freeBlock.m_pPrev = prev;
		freeBlock.m_pNext = next;
		freeBlock.Write(freeBlockStart);

		if (m_boundsCheck)
		{
			memcpy(freeBlockStart - s_BoundsCheckSize, s_StartBound, s_BoundsCheckSize);
			memcpy(freeBlockStart + sizeof(MemoryChunk) + freeUserDataSize, s_EndBound, s_BoundsCheckSize);
		}
	}
}
