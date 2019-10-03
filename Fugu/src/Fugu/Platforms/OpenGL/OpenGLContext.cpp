#include "fgpch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Fugu {

	OpenGLContext::OpenGLContext(GLFWwindow* window) 
		:m_WindowHandle(window)
	{
		FG_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);

		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FG_CORE_ASSERT(success, "Failed to initialize Glad!");

		FG_CORE_INFO("OpenGL Info:");
		FG_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		FG_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		FG_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}