#pragma once

namespace SmashEngine
{
	class Texture {
	public:
		Texture();
		void BindTexture() const;
		void Unbind() const;
		int GetWidth() const;
		int GetHeight() const;
		int GetTextureID() const;
		bool LoadTexture2D(const std::string& path);
		std::string& GetPath();
		~Texture();
	private:
		GLuint id;

		int width;
		int height;
		int channels;
		std::string path;
		Texture& operator=(const Texture&) = delete;
	};
}