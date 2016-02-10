#pragma once

namespace SmashEngine
{
	class Texture {
	public:
		Texture();
		Texture(const std::string& path);
		void BindTexture() const;
		void Unbind() const;
		int GetWidth() const;
		int GetHeight() const;
		int GetTextureID() const;
		std::string& GetPath();
		~Texture();
	private:
		GLuint id;

		void LoadTexture2D();
		int width;
		int height;
		int channels;
		std::string path;
	};
}