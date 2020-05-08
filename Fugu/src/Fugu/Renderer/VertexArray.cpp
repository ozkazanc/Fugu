#include "fgpch.h"
#include "VertexArray.h"

#include "Fugu/Renderer/Renderer.h"
#include "Fugu/Platforms/OpenGL/OpenGLVertexArray.h"

namespace Fugu {

	VertexArray* VertexArray::Create() {

		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:		FG_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLVertexArray();
		}

		FG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}