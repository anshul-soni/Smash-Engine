#pragma once
#include "stdafx.h"
#include "Shader.h"
namespace SmashEngine
{
	class Drawable
	{
	public:
		Drawable(){};
		virtual bool LoadModel()=0;
		virtual void Render() = 0;
		virtual void BindVAO()const = 0;
		virtual Shader& GetShader() = 0;
		virtual void SetShader(const std::string&) = 0;
		virtual ~Drawable(){};
	private:
	};
}
