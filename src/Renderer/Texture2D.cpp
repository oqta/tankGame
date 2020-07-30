#include "Texture2D.h"

namespace Renderer {
	Texture2D::Texture2D(const GLuint width, const GLuint height,
		unsigned char* data,
		const unsigned int channels = 4,
		const GLenum filter = GL_LINEAR,
		const GLenum wrapMode = GL_CLAMP_TO_EDGE)
		: mWidth(width)
		, mHeight(height)
	{
		switch (channels)
		{
		case 4:
			mMode = GL_RGBA;
			break;
		case 3:
			mMode = GL_RGB;
			break;
		default:
			mMode = GL_RGBA;
			break;
		}

		glGenTextures(1, &mID);
		glBindTexture(GL_TEXTURE_2D, mID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mWidth, 0, mMode, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	}
}