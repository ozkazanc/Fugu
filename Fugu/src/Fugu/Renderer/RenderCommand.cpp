#include "fgpch.h"
#include "RenderCommand.h"

#include "../Platforms/OpenGL/OpenGLRendererAPI.h"

namespace Fugu {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}