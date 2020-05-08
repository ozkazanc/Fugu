#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Fugu {

	class Shader {
	private:
		uint32_t m_RendererID;

	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetFloat3(const std::string& name, const glm::vec3& value);
	};
}