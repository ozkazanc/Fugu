#include "Fugu.h"

class ExampleLayer : public Fugu::Layer {
public:
	ExampleLayer()
		:Layer("ExampleLayer")
	{}
	~ExampleLayer() {}

	void OnUpdate() override {
		FG_INFO("{0}::Update", m_DebugName);
	}

	void OnEvent(Fugu::Event& e) override {
		FG_TRACE("{0}", e);
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
