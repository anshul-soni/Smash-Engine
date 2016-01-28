#pragma once
#include "stdafx.h"
#include "InputSignal.h"

namespace SmashEngine
{
	InputSignal::InputSignal(InputType type, const glm::vec3& param)
		:type(type),
		param(param)
	{
	}

	InputType InputSignal::GetType() const
	{
		return type;
	}

	const glm::vec3& InputSignal::GetParam() const
	{
		return param;
	}
}
