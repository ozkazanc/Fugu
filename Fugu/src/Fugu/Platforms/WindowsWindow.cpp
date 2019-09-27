#include "fgpch.h"
#include "WindowsWindow.h"
#include "Fugu/Events/KeyEvent.h"
#include "Fugu/Events/MouseEvent.h"
#include "Fugu/Events/ApplicationEvent.h"

namespace Fugu{

	static bool s_GLFWInitialized = false;
	
	static void GLFWErrorCallback(int error, const char* msg) {
		FG_CORE_ERROR("[GLFW Error: {0}]: {1}", error, msg);
	}

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
			glfwSetErrorCallback(GLFWErrorCallback);
		}

			m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
			FG_CORE_ASSERT(m_Window, "Window could not be created!");
			
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, &m_Data);
			SetVsync(true);

			glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {

				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
				switch (action) {
					case GLFW_PRESS: 
					{
						KeyPressedEvent event(key, 0);
						data->EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data->EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data->EventCallback(event);
						break;
					}
				}			
			});
			
			glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data->EventCallback(event);
			});

			glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
				data->Width = width;
				data->Height = height;

				WindowResizeEvent event((unsigned int)width, (unsigned int)height);
				data->EventCallback(event);
			});

			glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
				switch (action) {
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data->EventCallback(event);
						break;
					}
					case GLFW_RELEASE: 
					{
						MouseButtonReleasedEvent event(button);
						data->EventCallback(event);
						break;
					}
				}
			});

			glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data->EventCallback(event);
			});

			glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xoffset, (float)yoffset);
				data->EventCallback(event);	
			});

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