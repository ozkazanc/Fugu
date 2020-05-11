#include "fgpch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>

namespace Fugu {
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
		:m_RendererID(0)
	{
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		const char* srcVertex = vertexSrc.c_str();
		glShaderSource(vertex, 1, &srcVertex, nullptr);
		glCompileShader(vertex);

		GLint success = 0;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);

			std::vector<GLchar> infoLog(length);
			glGetShaderInfoLog(vertex, length, &length, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertex);

			FG_CORE_ERROR("{0}", infoLog.data());
			FG_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
		const char* srcFragment = fragmentSrc.c_str();
		glShaderSource(fragment, 1, &srcFragment, nullptr);
		glCompileShader(fragment);

		success = 0;
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);

			std::vector<GLchar> infoLog(length);
			glGetShaderInfoLog(fragment, length, &length, &infoLog[0]);

			// We don't need the shaders anymore.
			glDeleteShader(vertex);
			glDeleteShader(fragment);

			FG_CORE_ERROR("{0}", infoLog.data());
			FG_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		GLuint program = glCreateProgram();
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);

		success = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (success == GL_FALSE) {
			GLint length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			std::vector<GLchar> infoLog(length);
			glGetProgramInfoLog(program, length, &length, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			// We don't need the shaders also.
			glDeleteShader(vertex);
			glDeleteShader(fragment);

			FG_CORE_ERROR("{0}", infoLog.data());
			FG_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Everything went well
		m_RendererID = program;

		// Always detach shaders after a successful link.
		glDetachShader(program, vertex);
		glDetachShader(program, fragment);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
}