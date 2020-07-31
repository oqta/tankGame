#include "Sprite.h"

#include "ShaderProgram.h"
#include "Texture2D.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Renderer {
	Sprite::Sprite(const std::shared_ptr<Texture2D> pTexture,
		const std::shared_ptr<ShaderProgram> pShaderProgram,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation)
		: mPTexture(std::move(pTexture))
		, mPShaderProgram(std::move(pShaderProgram))
		, mPosition(position)
		, mSize(size)
		, mRotation(rotation)
	{
		const GLfloat vertexCoords[] = {
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,

			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f,
		};

		const GLfloat textureCoords[] = {
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,

			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f,
		};

		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);

		glGenBuffers(1, &mVertexCoordsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexCoordsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), &vertexCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		
		glGenBuffers(1, &mTextureCoordsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mTextureCoordsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), &textureCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}
	Sprite::~Sprite()
	{
		glDeleteBuffers(1, &mVertexCoordsVBO);
		glDeleteBuffers(1, &mTextureCoordsVBO);
		glDeleteVertexArrays(1, &mVAO);
	}

	void Sprite::render() const
	{
		mPShaderProgram->use();

		glm::mat4 model(1.f);

		model = glm::translate(model, glm::vec3(mPosition, 0.f));
		model = glm::translate(model, glm::vec3(0.5 * mSize.x, 0.5 * mSize.y, 0.f));
		model - glm::rotate(model, glm::radians(mRotation), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(-0.5 * mSize.x, -0.5 * mSize.y, 0.f));
		model = glm::scale(model, glm::vec3(mSize, 1.f));

		glBindVertexArray(mVAO);
		mPShaderProgram->setMatrix4("modelMat", model);

		glActiveTexture(GL_TEXTURE0);
		mPTexture->bind();

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void Sprite::setPosition(const glm::vec2& position)
	{
		mPosition = position;
	}

	void Sprite::setSize(glm::vec2& size)
	{
		mSize = size;
	}

	void Sprite::setRotation(const float rotation)
	{
		mRotation = rotation;
	}

}