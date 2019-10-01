#include "Fugu.h"

class ExampleLayer : public Fugu::Layer {
public:
	ExampleLayer()
		:Layer("ExampleLayer")
	{}
	~ExampleLayer() {}

	void OnUpdate() override {
		if (Fugu::Input::IsKeyPressed(FG_KEY_TAB))
			FG_INFO("Tab key is pressed (poll)!");
	}

	void OnEvent(Fugu::Event& event) override {
		if (event.GetEventType() == Fugu::EventType::KeyPressed) {
			Fugu::KeyPressedEvent& e = (Fugu::KeyPressedEvent&)event;
			
			if (e.GetKeyCode() == FG_KEY_TAB)
				FG_INFO("Tab key is pressed(event)!");
			
			FG_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class SandboxApp : public Fugu::Application {
public:
	SandboxApp() {
	
		PushLayer(new ExampleLayer());
	}
	~SandboxApp() {}
};


Fugu::Application* Fugu::CreateApplication() {
	return new SandboxApp();
}
