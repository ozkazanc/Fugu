#include "fgpch.h"
#include "WindowsWindow.h"

namespace Fugu{

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.m_Title;
		m_Data.Width = props.m_Width;
		m_Data.Height = props.m_Height;

		FG_CORE_TRACE("Creating window: \"{0}\" ({1},{2}))", props.m_Title, props.m_Width, props.m_Height);

		if (!s_GLFWInitialized) {

			int success = glfwInit();
			FG_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		//	glfwSetErrorCallback(GLFWErrorCallback);
		}

			m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
			FG_CORE_ASSERT(m_Window, "Window could not be created!");
			
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, &m_Data);
			SetVsync(true);
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}
	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	void WindowsWindow::SetVsync(bool enable) {
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.Vsync = enable;
	}
	bool WindowsWindow::IsVsync() const {
		return m_Data.Vsync;
	}
}