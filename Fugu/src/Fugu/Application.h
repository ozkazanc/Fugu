#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Fugu {

	class FUGU_API Application {
	
	public:
		Application();
		virtual ~Application();

		void Run();
	};


	// To be defined by Client
	Application* CreateApplication();

}
