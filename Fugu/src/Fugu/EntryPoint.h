#pragma once

#ifdef FG_PLATFORM_WINDOWS

extern Fugu::Application* Fugu::CreateApplication();

int main(int argc, char** argv) {
	Fugu::Log::Init();
	FG_CORE_TRACE("App, test = {0}, line: {1}", 8, __LINE__);
	FG_INFO("info: file: {0}", __FILE__);
	FG_CORE_WARN("Fugu");
	FG_CORE_ERROR("Engine");
	FG_CORE_CRITICAL("Assert");


	Fugu::Application* app = Fugu::CreateApplication();
	app->Run();
	delete app;
}


#endif
