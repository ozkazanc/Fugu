#pragma once

#ifdef FG_PLATFORM_WINDOWS

extern Fugu::Application* Fugu::CreateApplication();

int main(int argc, char** argv) {
	Fugu::Log::Init();
	FG_INFO("Initialized Logger!");

	Fugu::Application* app = Fugu::CreateApplication();
	app->Run();
	delete app;
}


#endif
