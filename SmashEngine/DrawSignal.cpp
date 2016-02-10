#include "stdafx.h"
#include "DrawSignal.h"

namespace SmashEngine
{
	DrawSignal::DrawSignal(const glm::vec3& point) :
		isPoint(true),
		point(point),
		point2(glm::vec3(0))
	{
	}
	DrawSignal::DrawSignal(const glm::vec3& point1,const glm::vec3& point2) :
		isPoint(false),
		point(point1),
		point2(point2)
	{
	}
	bool DrawSignal::IsPoint() const
	{
		return isPoint;
	}
	const glm::vec3 & DrawSignal::GetPoint()const
	{
		return point;
	}
	const std::pair<glm::vec3, glm::vec3> DrawSignal::GetLine()const
	{
		auto pair = std::pair<glm::vec3, glm::vec3>(point, point2);
		return pair;
	}
}