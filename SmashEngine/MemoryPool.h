#pragma once
#include <string>

#ifdef _DEBUG
#define TRASH_POOLS 1
#else
#define TRASH_POOLS 0
#endif

namespace SmashEngine
{
	class MemoryPool
	{
	public:
		virtual void*	allocate(unsigned int size) = 0;
		virtual void	free(void* ptr) = 0;
		virtual bool	integrityCheck() const = 0;
		virtual void	dumpToFile(const std::string& fileName, const unsigned int itemsPerLine)const = 0;

		unsigned int	GetFreePoolSize()const { return m_iFreePoolSize; }
		unsigned int	GetTotalPoolSize()const {return m_iTotalPoolSize; }
		bool			HasBoundsCheckOn()const { return m_boundsCheck; }

		static const unsigned char s_TrashOnCreation		= 0xCC;
		static const unsigned char s_TrashOnAllocSignature	= 0xAB;
		static const unsigned char s_TrashOnFreeSignature	= 0xFE;
		static const unsigned char s_BoundsCheckSize		= 16;
		static const unsigned char s_StartBound[s_BoundsCheckSize];
		static const unsigned char s_EndBound[s_BoundsCheckSize];
	protected:
		MemoryPool()
			: m_iTotalPoolSize(0)
			, m_iFreePoolSize(0)
			, m_trashOnCreation(TRASH_POOLS)
			, m_trashOnAlloc(TRASH_POOLS)
			, m_trashOnFree(TRASH_POOLS)
			, m_boundsCheck(0)
		{};
		virtual ~MemoryPool() {};


		unsigned int m_iTotalPoolSize;
		unsigned int m_iFreePoolSize;

		unsigned    m_trashOnCreation : 1;
		unsigned    m_trashOnAlloc : 1;
		unsigned    m_trashOnFree : 1;
		unsigned    m_boundsCheck : 1;
	};

}