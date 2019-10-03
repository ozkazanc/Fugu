#include "fgpch.h"
#include "OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

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
	}

	void OpenGLContext::SwapBuffers() {
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glEnd();

		glfwSwapBuffers(m_WindowHandle);
	}
}