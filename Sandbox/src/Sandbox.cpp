#include "Fugu.h"
//--------Entry Point --------------------------------------------
#include "Fugu/EntryPoint.h"
//----------------------------------------------------------------

#include "ExampleLayer.h"
#include "Tests/Test.h"

class SandboxApp : public Fugu::Application {
public:
	SandboxApp() {
	
		//PushLayer(new ExampleLayer());
		PushLayer(new TestMenu());
	}
	~SandboxApp() {}
};


Fugu::Application* Fugu::CreateApplication() {
	return new SandboxApp();
}
