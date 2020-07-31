#include "Texture2D.h"

namespace Renderer {
	Texture2D::Texture2D(const GLuint width, const GLuint height,
		unsigned char* data,
		const unsigned int channels,
		const GLenum filter,
		const GLenum wrapMode)
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
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mWidth, 0, mMode, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D& Texture2D::operator=(Texture2D&& texture2d)
	{
		glDeleteTextures(1, &mID);
		mID = texture2d.mID;
		texture2d.mID = 0;
		mMode = texture2d.mMode;
		mWidth = texture2d.mWidth;
		mHeight = texture2d.mHeight;
		return *this;
	}

	Texture2D::Texture2D(Texture2D&& texture2d)
	{
		mID = texture2d.mID;
		texture2d.mID = 0;
		mMode = texture2d.mMode;
		mWidth = texture2d.mWidth;
		mHeight = texture2d.mHeight;
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &mID);
	}

	void Texture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, mID);
	}
}