#pragma once

namespace SmashEngine
{
	class DrawSignal
	{
	public:
		DrawSignal(const glm::vec3& point);
		DrawSignal(const glm::vec3& point1, const glm::vec3& point2);
		bool IsPoint()const;
		const glm::vec3& GetPoint()const;
		const std::pair<glm::vec3, glm::vec3> GetLine()const;
	private:
		bool isPoint;
		const glm::vec3 point;
		const glm::vec3 point2;

	};
}