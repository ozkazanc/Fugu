#pragma once

#include "Core.h"

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
