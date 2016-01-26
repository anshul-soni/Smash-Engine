#pragma once
#include "ResourceType.h"

namespace SmashEngine
{
	class ResourcePath
	{
	public:
		static ResourcePath& GetInstance();
		std::string GetPath(ResourceType type,const std::string& key) const;
	private:
		ResourcePath();
		ResourcePath(const ResourcePath&) = delete;
		ResourcePath& operator=(const ResourcePath&) = delete;
	};
}