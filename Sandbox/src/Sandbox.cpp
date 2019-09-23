#include "Fugu.h"

class SandboxApp : public Fugu::Application {
public:
	SandboxApp() {}
	~SandboxApp() {}
};


Fugu::Application* Fugu::CreateApplication() {
	return new SandboxApp();
}
