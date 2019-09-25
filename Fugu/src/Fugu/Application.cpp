# include "Application.h"

#include "Fugu/Log.h"
#include "Fugu/Events/ApplicationEvent.h"


namespace Fugu {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		
		if(e.IsInCategory(EventCategoryApplication))
			FG_TRACE(e);
		if (e.IsInCategory(EventCategoryMouse))
			FG_WARN(e);

		while (true);
	}
}