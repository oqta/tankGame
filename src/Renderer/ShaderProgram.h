#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer {

	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vectorShader, const std::string& fragmentShader);
		~ShaderProgram();
		bool isCompiled() const { return mIsCompiled; }
		void use() const;

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool mIsCompiled = false;
		GLuint mID = 0;
	};

}