#include "stdafx.h"
#include "ShapeManager.h"

namespace SmashEngine
{
	ShapeManager::ShapeManager()
	{
	}

	Shape* ShapeManager::GetShape(const std::string& key)
	{
		if (Shapes.find(key) == Shapes.end())
		{
			AddShape(key);
		}
		return Shapes[key];
	}

	void ShapeManager::AddShape(const std::string& key)
	{
		Shapes[key] = new Shape(key);
	}

	ShapeManager::~ShapeManager()
	{
	}
}
