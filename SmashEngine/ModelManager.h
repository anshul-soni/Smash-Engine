#pragma once
#include "Model.h"

namespace SmashEngine
{
	class ModelManager
	{
	public:
		static ModelManager& GetInstance()
		{
			static ModelManager instance;
			return instance;
		}
		ModelManager();
		Model* GetModel(const std::string& key);
		~ModelManager();
	private:
		void AddModel(const std::string& key);
		std::unordered_map<std::string, Model*> models;
	};
}