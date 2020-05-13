#pragma once
#include "Fugu/Renderer/Shader.h"

namespace Fugu {
	class OpenGLShader : public Shader {
	private:
		uint32_t m_RendererID;

	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;
	};
}