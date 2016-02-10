#pragma once
#include "Engine.h"
#include "SignalHandler.h"
#include "DebugSignal.h"
#include "Shader.h"
#include "Model.h"
#include "DrawSignal.h"

namespace SmashEngine
{
	class Graphics:public Engine,
		public SignalHandler<DebugSignal>,
		public SignalHandler<DrawSignal>
	{
	public:
		Graphics();
		void Update(float dt)override;
		void Init()override;
		void OnSignal(DebugSignal signal)override;
		void OnSignal(DrawSignal signal)override;
		EngineType GetType()const override;
		~Graphics();
	private:
		Model* contactSphere;
		void DrawLines();
		void DrawPoints();
		void debugDrawLine(glm::vec3 startPoint, glm::vec3 endPoint, glm::vec3 color);
		std::vector<const glm::vec3> points;
		std::vector<const std::pair<glm::vec3,glm::vec3>> lines;
		GLuint line_Buffer;
		const EngineType type;
		Shader* debugShader;
		bool debugDraw;
	};
}
