#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Fugu {

	class Shader {

	public:
		virtual ~Shader() = default;
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;

	};
}