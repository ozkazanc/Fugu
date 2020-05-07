#include "ExampleLayer.h"
#include "../../Fugu/vendor/imgui/imgui.h"

ExampleLayer::ExampleLayer()
	:Layer("ExampleLayer")
{}

void ExampleLayer::OnAttach() {}
void ExampleLayer::OnDetach() {}

void ExampleLayer::OnUpdate() {
	if (Fugu::Input::IsKeyPressed(FG_KEY_TAB))
		FG_INFO("Tab key is pressed (poll)!");
}

void ExampleLayer::OnImGuiRender() {
	static bool show = true;
	ImGui::ShowDemoWindow(&show);
}

void ExampleLayer::OnEvent(Fugu::Event& event) {
	if (event.GetEventType() == Fugu::EventType::KeyPressed) {
		Fugu::KeyPressedEvent& e = (Fugu::KeyPressedEvent&)event;

		if (e.GetKeyCode() == FG_KEY_TAB)
			FG_INFO("Tab key is pressed(event)!");

		FG_TRACE("{0}", (char)e.GetKeyCode());
	}
}