#include "Test.h"
#include "ClearColor.h"

void TestMenu::OnAttach() {
	RegisterTest<ColorClearTest>("Clear Color");
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

void TestMenu::OnUpdate() {
	if (m_CurrentTest) {
		m_CurrentTest->OnUpdate();
	}
	else {
		if (Fugu::Input::IsKeyPressed(FG_KEY_TAB))
			FG_INFO("Tab key is pressed (poll)!");
	}
}