#include "fgpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Fugu/Platforms/OpenGL/OpenGLBuffer.h"

namespace Fugu {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) 
		{
		case RendererAPI::API::None:			FG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLVertexBuffer(vertices, size);
		}
		
		FG_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:			FG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLIndexBuffer(indices, count);
		}
		
		FG_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}