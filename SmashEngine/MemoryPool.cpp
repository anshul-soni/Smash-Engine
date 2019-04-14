#include "stdafx.h"
#include "MemoryPool.h"

namespace SmashEngine
{
	const unsigned char  MemoryPool::s_StartBound[16] = { '[','B','l','o','c','k','.','.','.','.','S','t','a','r','t',']' };
	const unsigned char  MemoryPool::s_EndBound[16] = { '[','B','l','o','c','k','.','.','.','.','.','.','E','n','d',']' };
}