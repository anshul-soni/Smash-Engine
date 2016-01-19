#pragma once
#include "Engine.h"

namespace SmashEngine
{
	class Graphics:public Engine
	{
	public:
		Graphics();
		void Update(float dt)override;
		void Init()override;
		~Graphics();
	private:
	};
}


//class Graphics : public System
//{
//public:
//	static Graphics& GetInstance()
//	{
//		static Graphics instance;
//		return instance;
//	}
//	virtual void Init();
//	virtual void Update(float dt);
//	virtual ~Graphics();
//private:
//	GLuint VAO;
//	Graphics(){}
//	Graphics(Graphics const&){}
//	Graphics& operator=(Graphics const&){}
//	Shader* ourShader;
//	Shader* pointShader;
//	GLuint matrixID;
//	GLuint modelMatrixID;
//	GLuint viewMatrixID;
//	GLuint textureID;
//	GLuint lightID;
//
//	GLuint VBO;
//	//matrices
//	glm::mat4 viewMatrix;
//	glm::mat4 projectionMatrix;
//
//};