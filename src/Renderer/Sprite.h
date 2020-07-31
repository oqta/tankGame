#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <string>

#include<memory>

namespace Renderer {

	class Texture2D;
	class ShaderProgram;

	class Sprite
	{
	public:
		Sprite(const std::shared_ptr<Texture2D> pTexture, 
			   const std::shared_ptr<ShaderProgram> pShaderProgram, 
			   const glm::vec2& position = glm::vec2(0.f), 
			   const glm::vec2& size = glm::vec2(1.f),
			   const float rotation = 0.f);

		~Sprite();
        
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;
		Sprite& operator=(Sprite&& shaderProgram) ;
		Sprite(Sprite&& shaderProgram);

		void render() const;
		void setPosition(const glm::vec2& position);
		void setSize(glm::vec2& size);
		void setRotation(const float rotation);

	private:
		std::shared_ptr<Texture2D> mPTexture;
		std::shared_ptr<ShaderProgram> mPShaderProgram;
		glm::vec2 mPosition;
		glm::vec2 mSize;
		float mRotation;
		GLuint mVAO;
		GLuint mVertexCoordsVBO;
		GLuint mTextureCoordsVBO;
	};
}