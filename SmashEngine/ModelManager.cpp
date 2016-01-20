#include "stdafx.h"
#include "ModelManager.h"

namespace SmashEngine
{
	ModelManager::ModelManager()
	{
	}

	Model* ModelManager::GetModel(const std::string& key)
	{
		if (models.find(key)==models.end())
		{
			AddModel(key);
		}
		return models[key];
	}

	ModelManager::~ModelManager()
	{
	}

	void ModelManager::AddModel(const std::string& key)
	{
		models[key] = new Model(key.c_str());
	}
}
