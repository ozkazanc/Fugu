#pragma once

#include "Fugu/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Fugu {

	class OpenGLContext : public RendererContext {
	private:
		GLFWwindow* m_WindowHandle;

	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	};
}