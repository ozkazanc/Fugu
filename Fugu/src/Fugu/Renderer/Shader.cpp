#include "fgpch.h"
#include "Shader.h"

#include "Fugu/Renderer/Renderer.h"
#include "../Platforms/OpenGL/OpenGLShader.h"

namespace Fugu {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		FG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		FG_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}