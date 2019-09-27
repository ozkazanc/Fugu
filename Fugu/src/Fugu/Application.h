#pragma once

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace Fugu {

	class FUGU_API Application {
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);

	public:
		Application();
		virtual ~Application();

		virtual void OnEvent(Event& e);
		void Run();
	};


	// To be defined by Client
	Application* CreateApplication();

}
