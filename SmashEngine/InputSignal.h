#pragma once
#include "InputType.h"
namespace SmashEngine
{
	class InputSignal
	{
	public:
		explicit InputSignal(InputType type,const glm::vec3& param);
		InputType GetType()const;
		const glm::vec3& GetParam()const;
	private:
		const InputType type;
		const glm::vec3 param;
	};
}
