#include "fgpch.h"
#include "Texture.h"

#include "Fugu/Core.h"
#include "Renderer.h"
#include "Fugu/Platforms/OpenGL/OpenGLTexture.h"

namespace Fugu {
	Texture2D* Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI()) \
		{
		case RendererAPI::API::None:	FG_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLTexture2D(path);
		}

		FG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}