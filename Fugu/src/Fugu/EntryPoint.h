#pragma once

#ifdef FG_PLATFORM_WINDOWS

extern Fugu::Application* Fugu::CreateApplication();

int main(int argc, char** argv) {
	Fugu::Application* app = Fugu::CreateApplication();
	app->Run();
	delete app;
}


#endif
