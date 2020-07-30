#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer {
	class Texture2D
	{
	public:
		Texture2D(const GLuint width, const GLuint height,
			unsigned char* data,
			const unsigned int channels = 4,
			const GLenum filter = GL_LINEAR,
			const GLenum wrapMode = GL_CLAMP_TO_EDGE);
		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&& texture2d) = delete;
		Texture2D(Texture2D&& texture2d) = delete;
		Texture2D();

		void bind() const;
	private:
		GLuint mID;
		GLenum mMode;
		unsigned int mWidth;
		unsigned int mHeight;
	};
}