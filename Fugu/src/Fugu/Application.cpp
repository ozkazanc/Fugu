#include "fgpch.h"
#include "Application.h"

#include "Fugu/Log.h"
#include "Fugu/Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>


namespace Fugu {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() {
		while (m_Running) {
			glClearColor(0, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}