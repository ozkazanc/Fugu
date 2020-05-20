#include "Test.h"
#include "ClearColor.h"
#include "Texture2DTest.h"
#include "ControlColorWithKeyboard.h"
#include "Texture3DTest.h"

void TestMenu::OnAttach() {
	RegisterTest<ClearColorTest>("Clear Color");
	RegisterTest<Texture2DTest>("Texture 2D");
	RegisterTest<ControlColorWithKeyboardTest>("Control color with keyboard");
	RegisterTest<Texture3DTest>("Texture 3D");
}

void TestMenu::OnImGuiRender() {
	//ImGui::SetWindowPos(ImVec2(g_WindowWidth - 170.0f, 0.0f));
	//ImGui::SetWindowSize(ImVec2(170.0f, 210.0f));
	if (m_CurrentTest) {
		m_CurrentTest->OnImGuiRender();
	}
	else {
		ImGui::Begin("Test Menu");
		for (const auto& it : m_Tests) {
			if (ImGui::Button(it.first.c_str())) {
				m_CurrentTest = it.second();
			}
		}
		ImGui::End();
	}
}

void TestMenu::OnEvent(Fugu::Event& event) {
	if (event.GetEventType() == Fugu::EventType::KeyPressed) {
		Fugu::KeyPressedEvent& e = (Fugu::KeyPressedEvent&)event;

		if (e.GetKeyCode() == FG_KEY_TAB || e.GetKeyCode() == FG_KEY_ESCAPE) {

			delete m_CurrentTest;
			m_CurrentTest = nullptr;
		}
	}

	if (m_CurrentTest) {
		m_CurrentTest->OnEvent(event);
	}
	else {
		if (event.GetEventType() == Fugu::EventType::KeyPressed) {
			Fugu::KeyPressedEvent& e = (Fugu::KeyPressedEvent&)event;

			if (e.GetKeyCode() == FG_KEY_ESCAPE) {
				Fugu::WindowCloseEvent e;
				Fugu::Application::GetInstance().OnEvent(e);
			}

			FG_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
}

void TestMenu::OnUpdate(Fugu::Timestep ts) {
	if (m_CurrentTest) {
		m_CurrentTest->OnUpdate(ts);
	}
	else {
		Fugu::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Fugu::RenderCommand::Clear();

		if (Fugu::Input::IsKeyPressed(FG_KEY_TAB))
			FG_INFO("Tab key is pressed (poll)!");
	}
}