#include "stdafx.h"
#include "ResourcePath.h"

namespace SmashEngine
{
	ResourcePath& ResourcePath::GetInstance()
	{
		static ResourcePath instance;
		return instance;
	}

	std::string ResourcePath::GetPath(ResourceType type, const std::string& key) const
	{
		std::string resourcePath = "resources/";
		switch(type)
		{
		case RESOURCE_Model:
			resourcePath += "models/";
			resourcePath += key;
			//resourcePath += ".model";
			break;
		case RESOURCE_Object:
			resourcePath += "objects/";
			resourcePath += key;
			resourcePath += ".xml";
			break;
		case RESOURCE_FragmentShader:
			resourcePath += "shaders/";	
			resourcePath += key;
			resourcePath += ".frag";
			break;
		case RESOURCE_VertexShader:
			resourcePath += "shaders/";
			resourcePath += key;
			resourcePath += ".vert";
			break;
		case RESOURCE_Texture:
			resourcePath += "model/";
			resourcePath += key;
			break;
		default:
			resourcePath += key;
			break;
		}
		return resourcePath;
	}

	ResourcePath::ResourcePath()
	{
	}
}
