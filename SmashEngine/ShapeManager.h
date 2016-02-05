#pragma once
#include "Shape.h"

namespace SmashEngine
{
	class ShapeManager
	{
	public:
		static ShapeManager& GetInstance()
		{
			static ShapeManager instance;
			return instance;
		}
		ShapeManager();
		Shape* GetShape(const std::string& key);
		~ShapeManager();
	private:
		void AddShape(const std::string& key);
		std::unordered_map<std::string, Shape*> Shapes;
	};
}